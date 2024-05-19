#include "UggWrongWay.h"
#include "GameTime.h"

dae::UggWrongWay::UggWrongWay(GameObject* const pParent, LevelPyramid* pyramid, int StartRow,bool isStartingLeft)
	:Component(pParent)
	, m_StartRow(StartRow)
	, m_pParent(pParent)
	, m_pPyramid(pyramid)
	, m_IsStartingLeft(isStartingLeft)
	, m_ElapsedTime(0)
	, m_Delay(0.5f)
{

	

	int startingIndex{};

	if (m_IsStartingLeft)
	{
		startingIndex = 21;

		spriteInfo.width = 32;
		spriteInfo.height = 32;
		spriteInfo.SrcX = 0;
		spriteInfo.SrcY = 0;
		spriteInfo.SrcWidth = 16;
		spriteInfo.SrcHeight = 16;
	}
	else
	{
		startingIndex = 27;

		spriteInfo.width = 32;
		spriteInfo.height = 32;
		spriteInfo.SrcX = 0;
		spriteInfo.SrcY = 0;
		spriteInfo.SrcWidth = 16;
		spriteInfo.SrcHeight = 16;
	}

	m_CurrentPos = glm::vec2(m_pPyramid->GetStartPos(startingIndex).x, m_pPyramid->GetStartPos(startingIndex).y - spriteInfo.height *0.25f);

	m_pPyramidMovementComponent = m_pParent->AddComponent<PyramidMovementComponent>(pyramid, m_CurrentPos, 0.4f, startingIndex, m_StartRow);

	m_pTextureComponent = m_pParent->AddComponent<TextureComponent>("UggWrongway.png", spriteInfo);

}

void dae::UggWrongWay::Update()
{

	
	float deltaTime = GameTime::GetInstance().GetDeltaTime();
	m_ElapsedTime += deltaTime;

	if (m_ElapsedTime >= m_Delay)
	{
		m_ElapsedTime -= m_Delay;

		int random = rand() % 2;

		if (m_pPyramidMovementComponent->IsOnFirstCubeInRow())
		{
			m_pPyramidMovementComponent->MoveUpRIghtUgg();
		}
		else if (m_pPyramidMovementComponent->IsOnLastCubeInRow())
		{
			m_pPyramidMovementComponent->MoveUpLeftUgg();
		}
		else
		{
			if (random == 0)
			{
				if (m_IsStartingLeft)
				{
					m_pPyramidMovementComponent->MoveUpRIghtUgg();
				}
				else
				{
					m_pPyramidMovementComponent->MoveUpLeftUgg();
				}
			}
			else
			{
				if (m_IsStartingLeft)
				{
					m_pPyramidMovementComponent->MoveUpLeftUgg();
				}
				else
				{
					m_pPyramidMovementComponent->MoveUpRIghtUgg();
				}
			}

		}

	}
}
