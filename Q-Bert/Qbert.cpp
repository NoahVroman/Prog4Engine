#include "Qbert.h"
#include <iostream>
#include "GameTime.h"

dae::Qbert::Qbert(GameObject* pParent, LevelPyramid* pyramid)
	: Component(pParent)
	,m_pPyramid(pyramid)
    ,m_CurrentCubeIndex(0)
	,m_IsMoving(false)
    ,Parent(pParent)
    ,m_CurrentRow(0)
    ,m_MovingDuration(0.3f)
    ,m_MoveTimer(0.0f)
    ,m_ControlPoint(0.0f, 0.0f)

{
    m_CurrentPos = m_pPyramid->GetStartPos(m_CurrentCubeIndex);
    m_TargetPos  = m_pPyramid->GetStartPos(m_CurrentCubeIndex);

    
	spriteInfo.width = 32;
	spriteInfo.height = 32;
	spriteInfo.SrcX = 0;
	spriteInfo.SrcY = 0;
	spriteInfo.SrcWidth = 16;
	spriteInfo.SrcHeight = 32;

    Parent->GetTransform()->SetLocalPosition(m_CurrentPos);
	m_pTextureComponent = Parent->AddComponent<TextureComponent>("QbertP1.png", spriteInfo);
}

dae::Qbert::~Qbert()
{
    

}

void dae::Qbert::Update()
{

    if (m_IsMoving)
    {
        float t = m_MoveTimer / m_MovingDuration;

        glm::vec2 newPos = m_CurrentPos * (1 - t) * (1 - t) * (1 - t) +
            m_ControlPoint * 3.f * t * (1 - t) * (1 - t) +
            m_TargetPos * 3.f * t * t * (1 - t) +
            m_TargetPos * t * t * t;

        Parent->GetTransform()->SetLocalPosition(newPos);
        m_MoveTimer += GameTime::GetInstance().GetDeltaTime();
        if (m_MoveTimer >= m_MovingDuration)
        {
		    m_IsMoving = false;
		    m_MoveTimer = 0.0f;
		    m_CurrentPos = m_TargetPos;
            Parent->GetTransform()->SetLocalPosition(m_TargetPos);

            if (m_JumpedOff == false)
            {
                m_pPyramid->GetCubes()[m_CurrentCubeIndex]->GetComponent<dae::LevelCube>()->ChangeColor();
            }
            else
            {
                m_Subject.Notify(Event::QbertDied);
            }
		}
    }
}


void dae::Qbert::MoveUpRight()
{
    if (not IsOnLastCubeInRow())
    {
        if (not m_IsMoving)
        {
            GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(0, 0, 16, 16);

            m_CurrentCubeIndex -= m_CurrentRow;
            m_CurrentRow -= 1;

            m_TargetPos.x = m_CurrentPos.x + cubeSizeX * 0.5f;
            m_TargetPos.y = m_CurrentPos.y - threeQuartersCubeSizeY;

            m_ControlPoint.x = m_CurrentPos.x + cubeSizeX * 0.5f;
            m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 2.f;
            Move(m_TargetPos, m_ControlPoint, m_MovingDuration);
        }
    }
    else
    {
        if (not m_IsMoving)
        {
            GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(0, 0, 16, 16);

            m_TargetPos.x = m_CurrentPos.x + cubeSizeX * 0.5f;
            m_TargetPos.y = m_CurrentPos.y - threeQuartersCubeSizeY;

            m_ControlPoint.x = m_CurrentPos.x + cubeSizeX * 0.5f;
            m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 2.f;

            Move(m_TargetPos, m_ControlPoint, m_MovingDuration);
            m_JumpedOff = true;
        }

    }

}

void dae::Qbert::MoveUpLeft()
{
    if (not IsOnFirstCubeInRow())
    {
        if (not m_IsMoving)
        {

            GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(17, 0, 16, 16);

            m_CurrentCubeIndex -= m_CurrentRow + 1;
            m_CurrentRow -= 1;

            m_TargetPos.x = m_CurrentPos.x - cubeSizeX * 0.5f;
            m_TargetPos.y = m_CurrentPos.y - threeQuartersCubeSizeY;

            m_ControlPoint.x = m_CurrentPos.x - cubeSizeX * 0.25f;
            m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 2.f;

            Move(m_TargetPos, m_ControlPoint, m_MovingDuration);
        }

    }
	else
	{
        if (not m_IsMoving)
        {
            GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(17, 0, 16, 16);

            m_TargetPos.x = m_CurrentPos.x - cubeSizeX * 0.5f;
            m_TargetPos.y = m_CurrentPos.y - threeQuartersCubeSizeY;

            m_ControlPoint.x = m_CurrentPos.x - cubeSizeX * 0.25f;
            m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 2.f;

            Move(m_TargetPos, m_ControlPoint, m_MovingDuration);
            m_JumpedOff = true;

        }

    }
}

void dae::Qbert::MoveDownRight()
{

    if (m_CurrentRow < m_pPyramid->GetRows() - 1)
    {
        if (not m_IsMoving)
        {

            GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(17 * 2, 0, 16, 16);

            m_CurrentCubeIndex += m_CurrentRow + 2;
            m_CurrentRow += 1;

            m_TargetPos.x = m_CurrentPos.x + cubeSizeX * 0.5f;
            m_TargetPos.y = m_CurrentPos.y + threeQuartersCubeSizeY;

            m_ControlPoint.x = m_CurrentPos.x + cubeSizeX * 0.5f;
            m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 1.5f;

            Move(m_TargetPos, m_ControlPoint, m_MovingDuration);


        }
    }
    else
    {
        if (not m_IsMoving)
        {
            GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(17 * 2, 0, 16, 16);

            m_TargetPos.x = m_CurrentPos.x + cubeSizeX * 0.5f;
            m_TargetPos.y = m_CurrentPos.y + threeQuartersCubeSizeY;

            m_ControlPoint.x = m_CurrentPos.x + cubeSizeX * 0.5f;
            m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 1.5f;

            Move(m_TargetPos, m_ControlPoint, m_MovingDuration);
            m_JumpedOff = true;

        }
    }

}

void dae::Qbert::MoveDownLeft()
{
    if (m_CurrentRow < m_pPyramid->GetRows() - 1)
    {
        if (not m_IsMoving)
        {

            GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(17 * 3, 0, 16, 16);

            m_CurrentCubeIndex += m_CurrentRow + 1;
            m_CurrentRow += 1;

            m_TargetPos.x = m_CurrentPos.x - cubeSizeX * 0.5f;
            m_TargetPos.y = m_CurrentPos.y + threeQuartersCubeSizeY;

            m_ControlPoint.x = m_CurrentPos.x - cubeSizeX * 0.5f;
            m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 1.5f;

            Move(m_TargetPos, m_ControlPoint, m_MovingDuration);


        }

    }
    else
	{
        if (not m_IsMoving)
        {
            GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(17 * 3, 0, 16, 16);

            m_TargetPos.x = m_CurrentPos.x - cubeSizeX * 0.5f;
            m_TargetPos.y = m_CurrentPos.y + threeQuartersCubeSizeY;

            m_ControlPoint.x = m_CurrentPos.x - cubeSizeX * 0.5f;
            m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 1.5f;

            Move(m_TargetPos, m_ControlPoint, m_MovingDuration);
            m_JumpedOff = true;

        }

    }
}

void dae::Qbert::Reset()
{

    m_CurrentCubeIndex = 0;
	m_CurrentRow = 0;
	m_CurrentPos = m_pPyramid->GetStartPos(m_CurrentCubeIndex);
	m_TargetPos = m_pPyramid->GetStartPos(m_CurrentCubeIndex);
	m_ControlPoint = glm::vec2(0.0f, 0.0f);
	m_IsMoving = false;
    m_JumpedOff = false;
	m_MoveTimer = 0.0f;
	Parent->GetTransform()->SetLocalPosition(m_CurrentPos);
	m_pTextureComponent->SetSourceInfo(0, 0, 16, 16);


}

void dae::Qbert::Move(const glm::vec2& target, glm::vec2& controlPoint, float duration)
{
	m_IsMoving = true;
	m_TargetPos = target;
	m_ControlPoint = controlPoint;
	m_MovingDuration = duration;
}


