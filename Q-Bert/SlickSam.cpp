#include "SlickSam.h"
#include "GameTime.h"
#include "LevelCube.h"

dae::SlickSam::SlickSam(GameObject* const pParent, LevelPyramid* pyramid, Qbert* pQbert, int StartRow, int StartingIndex)
	: Component(pParent)
	, m_pParent{ pParent }
	, m_pPyramid{ pyramid }
	, m_StartRow{ StartRow }
	, m_ElapsedTime{0}
	, m_Delay{ 3.f }
	, m_CurrentPos{}
	, m_pPyramidMovementComponent{}
	, m_pTextureComponent{}
	, m_Subject{}
	, m_StartingIndex{ StartingIndex }
	, m_pQbert{ pQbert }
{

	spriteInfo.width = 32;
	spriteInfo.height = 32;
	spriteInfo.SrcX = 0;
	spriteInfo.SrcY = 0;
	spriteInfo.SrcWidth = 11;
	spriteInfo.SrcHeight = 16;

	m_CurrentPos = glm::vec2(m_pPyramid->GetStartPos(StartingIndex).x, m_pPyramid->GetStartPos(StartingIndex).y );

	m_pPyramidMovementComponent = m_pParent->AddComponent<PyramidMovementComponent>(pyramid, m_CurrentPos, 0.4f, StartingIndex, m_StartRow);

	m_pTextureComponent = pParent->AddComponent<TextureComponent>("SlickSam.png", spriteInfo);
}

void dae::SlickSam::Update()
{
	float deltaTime = GameTime::GetInstance().GetDeltaTime();
	m_ElapsedTime += deltaTime;

	if (m_pQbert->GetCurrentIndex() == m_pPyramidMovementComponent->GetCurrentIndex())
	{
		m_Subject.Notify(Event::SlickSamDied);
	}

	if (m_ElapsedTime >= m_Delay)
	{
		m_ElapsedTime -= m_Delay;
		int random = rand() % 2;
		if (random == 0)
		{
			m_pPyramidMovementComponent->MoveDownRight();
		}
		else
		{
			m_pPyramidMovementComponent->MoveDownLeft();
		}
	}
	if (not m_pPyramidMovementComponent->IsMoving())
	{

		if (m_pPyramidMovementComponent->GetCurrentRow() <= m_pPyramid->GetRows() - 1)
		{
			m_pPyramid->GetCubes()[m_pPyramidMovementComponent->GetCurrentIndex()]->GetComponent<dae::LevelCube>()->RevertColor();
		}


	}



}
