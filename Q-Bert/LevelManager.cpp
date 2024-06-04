#include "LevelManager.h"
#include <iostream>
#include "GameTime.h"
#include "LevelCube.h"

dae::LevelManager::LevelManager(GameObject* const pParent, LevelPyramid* pyramid, GameObject* pQbert, GameObject* pCoily, GameObject* pUggWrongWay, GameObject* pSlickSam)
	:Component(pParent),
	 m_Pyramid{pyramid}
	, m_pQbert{pQbert}
	, m_pCoily{pCoily}
	, m_AnimationTimer{0}
	, m_MaxAnimationTime{2.f}
	, m_FlashingTimer{0}
	, m_MaxFlashingTime{0.07f}
	, m_CurrentColor{1}
	,m_RoundWon{false}
	,m_Finished{false}
	,m_pUggWrongWay{pUggWrongWay}
	,m_pSlickSam{pSlickSam}


{
	m_Pyramid->GetSubject().AddObserver(this);
	m_pQbert->GetComponent<Qbert>()->GetSubject().AddObserver(this);
	m_pCoily->GetComponent<Coily>()->GetSubject().AddObserver(this);
	m_pUggWrongWay->GetComponent<UggWrongWay>()->GetSubject().AddObserver(this);
	m_pSlickSam->GetComponent<SlickSam>()->GetSubject().AddObserver(this);

}

void dae::LevelManager::NotifyObserver(Subject* const, Event currentEvent)
{

	switch (currentEvent)
	{
	case dae::Event::CubeChanged:

		break;
	case dae::Event::PyramidCompleted:
		m_RoundWon = true;
		m_pCoily->Destroy();
		m_pQbert->GetComponent<Qbert>()->SetFrozen(true);
		break;
	case dae::Event::RoundWon:
		m_RoundWon = false;
		m_AnimationTimer = 0;
		m_FlashingTimer = 0;
		m_CurrentColor = 1;

		m_Pyramid->NextRound();
		m_pQbert->GetComponent<Qbert>()->Reset();
		m_pQbert->GetComponent<Qbert>()->SetFrozen(false);

		for (auto& cube : m_Pyramid->GetCubes())
		{
			cube->GetComponent<LevelCube>()->SetTurned(false);
			cube->GetComponent<LevelCube>()->SetHalfTurned(false);
			cube->GetComponent<LevelCube>()->ChangeToFirstColor();
		}
		break;
	case dae::Event::LevelCompleted:
		break;
	case dae::Event::QbertDied:
		m_pQbert->GetComponent<Qbert>()->SetDeath(true);

		break;
	case dae::Event::UggWrongWayDied:
		m_pUggWrongWay->Destroy();
		break;
	case dae::Event::CoilyDied:
		m_pCoily->Destroy();
		break;
	case dae::Event::ScoreUpdated:
		break;
	case dae::Event::LivesChanged:
		break;
		case dae::Event::SlickSamDied:
			m_pSlickSam->Destroy();
			break;
	default:
		break;
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
