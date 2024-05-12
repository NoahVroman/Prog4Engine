#include "Coily.h"
#include "LevelCube.h"
#include "GameTime.h"
#include "TransfomComponent.h"
#include <iostream>
#include "EggState.h"
#include "SnakeState.h"

dae::Coily::Coily(GameObject* const pParent, Qbert* pQbert, LevelPyramid* pyramid, int StartingIndex, int StartRow, float jumpInterval)
	:Component(pParent)
	, m_pQbert(pQbert)
	, m_pPyramid(pyramid)
	, m_CurrentIndex(StartingIndex)
	, m_CurrentRow(StartRow)
	, m_JumpInterval(jumpInterval)
	, m_ControlPoint(0, 0)
	, m_IsJumping(false)
	, m_JumpTimer(0.0f)
	, m_JumpDuration(0.4f)
	, m_pParent(pParent)
	

{

	InitializeSpriteInfo();

	m_CurrentPos = glm::vec2(  m_pPyramid->GetStartPos(m_CurrentIndex).x,m_pPyramid->GetStartPos(m_CurrentIndex).y - spriteInfo.height/2.f);
	m_TargetPos = m_CurrentPos;


	m_pParent->GetTransform()->SetLocalPosition(m_CurrentPos);
	m_pTextureComponent = m_pParent->AddComponent<TextureComponent>("Coily.png", spriteInfo);

	m_pCoilyState[CoilyState::CoilyStateEnum::Egg] = std::make_unique<EggState>();
	m_pCoilyState[CoilyState::CoilyStateEnum::Snake] = std::make_unique<SnakeState>();

	m_CurrentState = m_pCoilyState[CoilyState::CoilyStateEnum::Egg].get();


}

void dae::Coily::Update()
{



	if (m_IsJumping)
	{
		UpdateJumping();
	}
	else
	{
		UpdateStanding();
	}
}

void dae::Coily::MoveUpRight()
{
	m_CurrentDirection = MovingDirection::UpRight;

	if (not IsOnLastCubeInRow())
	{
		if (not m_IsJumping)
		{
			m_CurrentIndex -= m_CurrentRow;
			m_CurrentRow -= 1;

			m_TargetPos.x = m_CurrentPos.x + cubeSizeX * 0.5f;
			m_TargetPos.y = m_CurrentPos.y - threeQuartersCubeSizeY;

			m_ControlPoint.x = m_CurrentPos.x + cubeSizeX * 0.5f;
			m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 2.f;



			if (m_CurrentState->GetState() == CoilyState::CoilyStateEnum::Egg)
			{
				m_pTextureComponent->SetSourceInfo(16, 0, 16, 32);
			}
			else if (m_CurrentState->GetState() == CoilyState::CoilyStateEnum::Snake)
			{
				m_pTextureComponent->SetSourceInfo(3 * 16, 0, 16, 32);
			}


			Jump(m_TargetPos, m_ControlPoint, m_JumpDuration);

		}

	}


}

void dae::Coily::MoveUpLeft()
{
	m_CurrentDirection = MovingDirection::UpLeft;

	if (not IsOnFirstCubeInRow())
	{
		if (not m_IsJumping)
		{
			m_CurrentIndex -= m_CurrentRow + 1;
			m_CurrentRow -= 1;

			m_TargetPos.x = m_CurrentPos.x - cubeSizeX * 0.5f;
			m_TargetPos.y = m_CurrentPos.y - threeQuartersCubeSizeY;

			m_ControlPoint.x = m_CurrentPos.x - cubeSizeX * 0.25f;
			m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 2.f;


			if (m_CurrentState->GetState() == CoilyState::CoilyStateEnum::Egg)
			{
				m_pTextureComponent->SetSourceInfo(16, 0, 16, 32);
			}
			else if (m_CurrentState->GetState() == CoilyState::CoilyStateEnum::Snake)
			{
				m_pTextureComponent->SetSourceInfo(5 * 16, 0, 16, 32);
			}


			Jump(m_TargetPos, m_ControlPoint, m_JumpDuration);
		}

	}
}

void dae::Coily::MoveDownRight()
{
	m_CurrentDirection = MovingDirection::DownRight;

	if (m_CurrentRow < m_pPyramid->GetRows() - 1)
	{
		if (not m_IsJumping)
		{
			m_CurrentIndex += m_CurrentRow + 2;
			m_CurrentRow += 1;

			m_TargetPos.x = m_CurrentPos.x + cubeSizeX * 0.5f;
			m_TargetPos.y = m_CurrentPos.y + threeQuartersCubeSizeY;

			m_ControlPoint.x = m_CurrentPos.x + cubeSizeX * 0.5f;
			m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 1.5f;


			if (m_CurrentState->GetState() == CoilyState::CoilyStateEnum::Egg)
			{
				m_pTextureComponent->SetSourceInfo(16, 0, 16, 32);
			}
			else if (m_CurrentState->GetState() == CoilyState::CoilyStateEnum::Snake)
			{
				m_pTextureComponent->SetSourceInfo(7 * 16, 0, 16, 32);
			}

			Jump(m_TargetPos, m_ControlPoint, m_JumpDuration);


		}
	}
}

void dae::Coily::MoveDownLeft()
{
	m_CurrentDirection = MovingDirection::DownLeft;

	if (m_CurrentRow < m_pPyramid->GetRows() - 1)
	{
		if (not m_IsJumping)
		{
			m_CurrentIndex += m_CurrentRow + 1;
			m_CurrentRow += 1;

			m_TargetPos.x = m_CurrentPos.x - cubeSizeX * 0.5f;
			m_TargetPos.y = m_CurrentPos.y + threeQuartersCubeSizeY;

			m_ControlPoint.x = m_CurrentPos.x - cubeSizeX * 0.25f;
			m_ControlPoint.y = m_CurrentPos.y - threeQuartersCubeSizeY * 1.5f;


			if (m_CurrentState->GetState() == CoilyState::CoilyStateEnum::Egg)
			{
				m_pTextureComponent->SetSourceInfo(16, 0, 16, 32);
			}
			else if (m_CurrentState->GetState() == CoilyState::CoilyStateEnum::Snake)
			{
				m_pTextureComponent->SetSourceInfo(9 * 16, 0, 16, 32);
			}

			Jump(m_TargetPos, m_ControlPoint, m_JumpDuration);
		}
	}
}

void dae::Coily::InitializeSpriteInfo()
{
	spriteInfo.width = 32;
	spriteInfo.height = 64;
	spriteInfo.SrcX = 0;
	spriteInfo.SrcY = 0;
	spriteInfo.SrcWidth = 16;
	spriteInfo.SrcHeight = 32;

}



void dae::Coily::UpdateJumping()
{
	float t = m_JumpTimer / m_JumpDuration;

	glm::vec2 newPos = m_CurrentPos * (1 - t) * (1 - t) * (1 - t) +
		m_ControlPoint * 3.f * t * (1 - t) * (1 - t) +
		m_TargetPos * 3.f * t * t * (1 - t) +
		m_TargetPos * t * t * t;

	m_pParent->GetTransform()->SetLocalPosition(newPos);

	m_JumpTimer += GameTime::GetInstance().GetDeltaTime();

	if (m_JumpTimer >= m_JumpDuration)
	{
		HandleJumpEnd();
	}
}

void dae::Coily::UpdateStanding()
{
	UpdateTextureBasedOnState();
	m_JumpTimer += GameTime::GetInstance().GetDeltaTime();

	if (m_JumpTimer >= m_JumpInterval)
	{
		m_JumpTimer = 0.0f;

		CoilyState::CoilyStateEnum nextState = m_CurrentState->GetNextState(this);
		if ( nextState == m_CurrentState->GetState())
		{
			m_CurrentState->Update(this);
		}
		else
		{
			m_CurrentState = m_pCoilyState[nextState].get();
		}


	}
}

void dae::Coily::UpdateTextureBasedOnState()
{

	if (m_CurrentState->GetState() == CoilyState::CoilyStateEnum::Egg)
	{
		m_pTextureComponent->SetSourceInfo(0, 0, 16, 32);
	}
	else if (m_CurrentState->GetState() == CoilyState::CoilyStateEnum::Snake)
	{
		switch (m_CurrentDirection)
		{
		case dae::Coily::MovingDirection::UpRight:
			m_pTextureComponent->SetSourceInfo(2 * 16, 0, 16, 32);


			break;
		case dae::Coily::MovingDirection::UpLeft:
			m_pTextureComponent->SetSourceInfo(4 * 16, 0, 16, 32);
			break;
		case dae::Coily::MovingDirection::DownRight:
			m_pTextureComponent->SetSourceInfo(6 * 16, 0, 16, 32);
			break;
		case dae::Coily::MovingDirection::DownLeft:
			m_pTextureComponent->SetSourceInfo(8 * 16, 0, 16, 32);
			break;
		}

	}
}

void dae::Coily::HandleJumpEnd()
{
	if (m_pQbert->GetCurrentIndex() == m_CurrentIndex)
	{
		m_Subject.Notify(Event::QbertDied);
	}
	m_IsJumping = false;
	m_JumpTimer = 0.0f;
	m_CurrentPos = m_TargetPos;
	m_pParent->GetTransform()->SetLocalPosition(m_TargetPos);
}

void dae::Coily::Jump(const glm::vec2& target, glm::vec2& controlPoint, float duration)
{
	m_IsJumping = true;
	m_TargetPos = target;
	m_ControlPoint = controlPoint;
	m_JumpDuration = duration;
}
