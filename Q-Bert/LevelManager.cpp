#include "LevelManager.h"
#include <iostream>
#include "GameTime.h"
#include "LevelCube.h"

dae::LevelManager::LevelManager(GameObject* const pParent, LevelPyramid* pyramid, Qbert* pQbert, Coily* pCoily)
	:Component(pParent),
	 m_Pyramid{pyramid}
	, m_pQbert{pQbert}
	, m_AnimationTimer{0}
	, m_MaxAnimationTime{2.f}
	, m_FlashingTimer{0}
	, m_MaxFlashingTime{0.07f}
	, m_CurrentColor{1}
	,m_RoundWon{false}
	,m_Finished{false}


{
	m_Pyramid->GetSubject().AddObserver(this);
	m_pQbert->GetSubject().AddObserver(this);
	pCoily->GetSubject().AddObserver(this);
}

void dae::LevelManager::NotifyObserver(Subject* const, Event currentEvent)
{
	if (currentEvent == Event::PyramidCompleted)
	{
		m_RoundWon = true;
		
	}
	else if (currentEvent == Event::QbertDied)
	{
		std::cout << "QBERT DIED" << "\n";
	}
	else if (currentEvent == Event::RoundWon)
	{
		m_RoundWon = false;
		m_AnimationTimer = 0;
		m_FlashingTimer = 0;
		m_CurrentColor = 1;

		m_Pyramid->NextRound();
		m_pQbert->Reset();

		for (auto& cube : m_Pyramid->GetCubes())
		{

			cube->GetComponent<LevelCube>()->ChangeToFirstColor();
		}

	}
}

void dae::LevelManager::Update()
{
	if (m_RoundWon == true)
	{
		m_AnimationTimer += GameTime::GetInstance().GetDeltaTime();
		m_FlashingTimer += GameTime::GetInstance().GetDeltaTime();

		if (m_AnimationTimer < m_MaxAnimationTime)
		{
			if (m_FlashingTimer >= m_MaxFlashingTime)
			{
				if (m_CurrentColor == 1)
				{
					for (auto& cube : m_Pyramid->GetCubes())
					{
						cube->GetComponent<LevelCube>()->ChangeToSecondColor();
					}

					m_CurrentColor = 2;

				}
				else if (m_CurrentColor == 2)
				{
					for (auto& cube : m_Pyramid->GetCubes())
					{
						cube->GetComponent<LevelCube>()->ChangeToThirdColor();
					}
					m_CurrentColor = 3;

				}
				else
				{
					for (auto& cube : m_Pyramid->GetCubes())
					{
						cube->GetComponent<LevelCube>()->ChangeToFirstColor();
					}
					m_CurrentColor = 1;

				}
				m_FlashingTimer = 0.f;
			}
		}
		else
		{
			
			m_Pyramid->GetSubject().Notify(Event::RoundWon);
		}
	
	}

}
