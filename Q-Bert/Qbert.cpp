#include "Qbert.h"
#include <iostream>
#include "GameTime.h"
#include "ScoreAndLivesManager.h"


dae::Qbert::Qbert(GameObject* pParent, LevelPyramid* pyramid, int startingIndex, int StartingRow, bool isPlayer2)
	: Component(pParent)
	,m_pPyramid(pyramid)
    ,m_CurrentCubeIndex(startingIndex)
	,m_IsMoving(false)
    ,Parent(pParent)
    ,m_CurrentRow(StartingRow)
    ,m_MovingDuration(0.4f)
    ,m_MoveTimer(0.0f)
    ,m_ControlPoint(0.0f, 0.0f)
    ,m_HasJustJumped(false)
    ,m_DeathDuration(1.f)
    ,m_DeathTimer(0.0f)
    ,m_PreviousCubeIndex(m_CurrentCubeIndex)
    ,m_StartIndex(startingIndex)
    ,m_StartRow(StartingRow)

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
    if (!isPlayer2)
    {
        m_pQbertTexture = Parent->AddComponent<TextureComponent>("QbertP1.png", spriteInfo);

    }
    else
    {
		m_pQbertTexture = Parent->AddComponent<TextureComponent>("QbertP2.png", spriteInfo);
	}


    TextureComponent::SpriteInfo curseSpriteInfo;
    curseSpriteInfo.width = 48;
    curseSpriteInfo.height = 25;
    curseSpriteInfo.SrcX = 0;
    curseSpriteInfo.SrcY = 0;
    curseSpriteInfo.SrcWidth = 48;
    curseSpriteInfo.SrcHeight = 25;

    m_pCurseTexture = Parent->AddComponent<TextureComponent>("Curses.png", curseSpriteInfo);
    m_pCurseTexture->SetHidden(true);

}

dae::Qbert::~Qbert()
{
    

}

void dae::Qbert::Update()
{

    if (m_IsDead)
    {
        Die();
        return;
    }


    if (m_IsMoving)
    {
        float t = m_MoveTimer / m_MovingDuration;

        glm::vec2 newPos = glm::mix(glm::mix(m_CurrentPos, m_ControlPoint, t), glm::mix(m_ControlPoint, m_TargetPos, t), t);

        Parent->GetTransform()->SetLocalPosition(newPos);
        m_MoveTimer += GameTime::GetInstance().GetDeltaTime();
        if (m_MoveTimer >= m_MovingDuration)
        {
            m_Subject.Notify(Event::QbertJumped, Parent);

		    m_IsMoving = false;
            m_HasJustJumped = true;
		    m_MoveTimer = 0.0f;
		    m_CurrentPos = m_TargetPos;
            Parent->GetTransform()->SetLocalPosition(m_TargetPos);

            if (m_JumpedOff == false)
            {
                m_pPyramid->GetCubes()[m_CurrentCubeIndex]->GetComponent<dae::LevelCube>()->ChangeColor();

            }
            else if (!m_isOnDisk)
            {
                m_Subject.Notify(Event::QbertDied,Parent);
            }
		}
    }
}


void dae::Qbert::MoveUpRight()
{
   

    if (!m_Frozen && !m_IsDead)
    {

        if (not IsOnLastCubeInRow())
        {
            if (not m_IsMoving)
            {

                GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(0, 0, 16, 16);

                m_CurrentCubeIndex -= m_CurrentRow;
                m_PreviousCubeIndex = m_CurrentCubeIndex;
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
                m_CurrentCubeIndex = -1;

            }

        }

    }


}

void dae::Qbert::MoveUpLeft()
{
    if (!m_Frozen && !m_IsDead)
    {

        if (not IsOnFirstCubeInRow())
        {
            if (not m_IsMoving)
            {


                GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(17, 0, 16, 16);

                m_CurrentCubeIndex -= m_CurrentRow + 1;
                m_PreviousCubeIndex = m_CurrentCubeIndex;
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
                m_CurrentCubeIndex = -1;


            }

        }


    }

}

void dae::Qbert::MoveDownRight()
{

    if (!m_Frozen && !m_IsDead)
    {

        if (m_CurrentRow < m_pPyramid->GetRows() - 1)
        {
            if (not m_IsMoving)
            {

                GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(17 * 2, 0, 16, 16);

                m_CurrentCubeIndex += m_CurrentRow + 2;
                m_PreviousCubeIndex = m_CurrentCubeIndex;
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
                m_CurrentCubeIndex = -1;

            }
        }


    }


}

void dae::Qbert::MoveDownLeft()
{
    if (!m_Frozen && !m_IsDead)
    {

        if (m_CurrentRow < m_pPyramid->GetRows() - 1)
        {
            if (not m_IsMoving)
            {

                GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(17 * 3, 0, 16, 16);

                m_CurrentCubeIndex += m_CurrentRow + 1;
                m_PreviousCubeIndex = m_CurrentCubeIndex;
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
                m_CurrentCubeIndex = -1;

            }

        }


    }

}

void dae::Qbert::Reset()
{
    // Initialize to starting index and row
    InitializePosition(m_StartIndex, m_StartRow);

    m_IsDead = false;
    m_isOnDisk = false;
    m_JumpedOff = false;
    m_Frozen = false;
    m_MoveTimer = 0.0f;
    m_HasJustJumped = false;

    m_pCurseTexture->SetHidden(true);
    m_pQbertTexture->SetSourceInfo(0, 0, 16, 16);
}

void dae::Qbert::SetToTopCube()
{
    // Initialize to the top cube position
    InitializePosition(0, 0);

    m_IsDead = false;
    m_isOnDisk = false;
    m_JumpedOff = false;
    m_Frozen = false;
    m_MoveTimer = 0.0f;
    m_HasJustJumped = false;

    m_pCurseTexture->SetHidden(true);
    m_pQbertTexture->SetSourceInfo(0, 0, 16, 16);
}
void dae::Qbert::Die()
{
    m_DeathTimer += GameTime::GetInstance().GetDeltaTime();
    m_Frozen = true;
        m_pCurseTexture->SetHidden(false);


    if (m_DeathTimer >= m_DeathDuration)
    {
		m_IsDead = false;
        Reset();
        m_Frozen = false;
        m_DeathTimer = 0.0f;
	}
}

void dae::Qbert::InitializePosition(int cubeIndex, int row)
{
    m_PreviousCubeIndex = cubeIndex;
    m_CurrentCubeIndex = cubeIndex;
    m_CurrentRow = row;

    // Get the initial position from the pyramid
    m_CurrentPos = m_pPyramid->GetStartPos(cubeIndex);
    m_TargetPos = m_pPyramid->GetStartPos(cubeIndex);

    // Reset the control point and movement state
    m_ControlPoint = glm::vec2(0.0f, 0.0f);
    m_IsMoving = false;

    // Set the local position of the parent to the current position
    if (Parent) {
        Parent->GetTransform()->SetLocalPosition(m_CurrentPos);
    }
}

void dae::Qbert::Move(const glm::vec2& target, glm::vec2& controlPoint, float duration)
{

	m_IsMoving = true;
    m_Frozen = false;
    m_HasJustJumped = false;
	m_TargetPos = target;
	m_ControlPoint = controlPoint;
	m_MovingDuration = duration;
}


