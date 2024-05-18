#include "PyramidMovementComponent.h"
#include "TransfomComponent.h"
#include "GameTime.h"
dae::PyramidMovementComponent::PyramidMovementComponent(GameObject* const pParrent, LevelPyramid* pPyramid, const glm::vec2& startPos, float movingDuration, int startIndex, int startRow)
	: Component(pParrent)
	, m_pPyramid(pPyramid)
	, m_CurrentPos(startPos)
	, m_TargetPos(startPos)
	, m_ControlPoint(0.0f, 0.0f)
	, m_MovingDuration(movingDuration)
	, m_MoveTimer(0.0f)
	, m_IsMoving(false)
	, m_pParent(pParrent)
	, cubeSizeX(pPyramid->GetCubeSize().x)
	, cubeSizeY(pPyramid->GetCubeSize().y)
	, threeQuartersCubeSizeY(cubeSizeY * 0.75f)
	, m_CurrentRow(startRow)
	, m_CurrentIndex(startIndex)


{

	m_pParent->GetTransform()->SetLocalPosition(m_CurrentPos);
}

dae::PyramidMovementComponent::~PyramidMovementComponent()
{
}

void dae::PyramidMovementComponent::MoveDownRight()
{
	if (not m_IsMoving)
	{
		m_CurrentIndex += m_CurrentRow + 2;
		m_CurrentRow += 1;

		m_TargetPos.x = m_CurrentPos.x + cubeSizeX * 0.5f;
		m_TargetPos.y = m_CurrentPos.y + threeQuartersCubeSizeY;

		m_ControlPoint.x = m_CurrentPos.x + cubeSizeX * 0.5f;
		m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 1.5f;

		Jump(m_TargetPos, m_ControlPoint, m_MovingDuration);
	}


}

void dae::PyramidMovementComponent::MoveDownLeft()
{

	if (not m_IsMoving)
	{
		m_CurrentIndex += m_CurrentRow + 1;
		m_CurrentRow += 1;

		m_TargetPos.x = m_CurrentPos.x - cubeSizeX * 0.5f;
		m_TargetPos.y = m_CurrentPos.y + threeQuartersCubeSizeY;

		m_ControlPoint.x = m_CurrentPos.x - cubeSizeX * 0.25f;
		m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 1.5f;

		Jump(m_TargetPos, m_ControlPoint, m_MovingDuration);
	}
}

void dae::PyramidMovementComponent::MoveUpRight()
{
	if (not m_IsMoving)
	{
		m_CurrentIndex -= m_CurrentRow;
		m_CurrentRow -= 1;

		m_TargetPos.x = m_CurrentPos.x + cubeSizeX * 0.5f;
		m_TargetPos.y = m_CurrentPos.y - threeQuartersCubeSizeY;

		m_ControlPoint.x = m_CurrentPos.x + cubeSizeX * 0.5f;
		m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 2.f;

		Jump(m_TargetPos, m_ControlPoint, m_MovingDuration);
	}
}

void dae::PyramidMovementComponent::MoveUpLeft()
{
	if (not m_IsMoving)
	{
		m_CurrentIndex -= m_CurrentRow + 1;
		m_CurrentRow -= 1;

		m_TargetPos.x = m_CurrentPos.x - cubeSizeX * 0.5f;
		m_TargetPos.y = m_CurrentPos.y - threeQuartersCubeSizeY;

		m_ControlPoint.x = m_CurrentPos.x - cubeSizeX * 0.25f;
		m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 2.f;

		Jump(m_TargetPos, m_ControlPoint, m_MovingDuration);
	}
}

void dae::PyramidMovementComponent::Update()
{


	if (m_IsMoving)
	{
		float t = m_MoveTimer / m_MovingDuration;

		glm::vec2 newPos = m_CurrentPos * (1 - t) * (1 - t) * (1 - t) +
			m_ControlPoint * 3.f * t * (1 - t) * (1 - t) +
			m_TargetPos * 3.f * t * t * (1 - t) +
			m_TargetPos * t * t * t;

		m_pParent->GetTransform()->SetLocalPosition(newPos);

		m_MoveTimer += GameTime::GetInstance().GetDeltaTime();

		if (m_MoveTimer >= m_MovingDuration)
		{
			HandleEndOfJump();
		}

	}


}

void dae::PyramidMovementComponent::Jump(const glm::vec2& targetPos, const glm::vec2& controlPoint, float duration)
{
	m_IsMoving = true;
	m_TargetPos = targetPos;
	m_ControlPoint = controlPoint;
	m_MovingDuration = duration;

}

void dae::PyramidMovementComponent::HandleEndOfJump()
{
	m_IsMoving = false;
	m_MoveTimer = 0.0f;
	m_CurrentPos = m_TargetPos;
	m_pParent->GetTransform()->SetLocalPosition(m_TargetPos);
}

