#include "Coily.h"
#include "LevelCube.h"
#include "GameTime.h"
#include "TransfomComponent.h"
#include <iostream>
#include "EggState.h"
#include "SnakeState.h"
#include "ServiceLocator.h"

dae::Coily::Coily(GameObject* const pParent, std::vector<std::shared_ptr<GameObject>> qberts, LevelPyramid* pyramid, int StartingIndex, int StartRow, bool isPlayer)
	:Component(pParent)
	, m_pQbert(qberts)
	, m_pPyramid(pyramid)
	, m_StartingIndex(StartingIndex)
	, m_StartRow(StartRow)
	, m_pParent(pParent)
	, m_Freeze(false)
	

{

	spriteInfo.width = 32;
	spriteInfo.height = 64;
	spriteInfo.SrcX = 0;
	spriteInfo.SrcY = 0;
	spriteInfo.SrcWidth = 16;
	spriteInfo.SrcHeight = 32;


	m_CurrentPos = glm::vec2(  m_pPyramid->GetStartPos(m_StartingIndex).x,m_pPyramid->GetStartPos(m_StartingIndex).y - spriteInfo.height/2.f);
	m_TargetPos = m_CurrentPos;

	m_pPyramidMovementComponent = m_pParent->AddComponent<PyramidMovementComponent>(m_pPyramid, m_CurrentPos,0.4f, m_StartingIndex, m_StartRow);
	m_pTextureComponent = m_pParent->AddComponent<TextureComponent>("Coily.png", spriteInfo);



	m_pCoilyState[CoilyState::CoilyStateEnum::Egg] = std::make_unique<EggState>(m_pParent);
	m_pCoilyState[CoilyState::CoilyStateEnum::Snake] = std::make_unique<SnakeState>(m_pParent,isPlayer);
	m_CurrentState = m_pCoilyState[CoilyState::CoilyStateEnum::Egg].get();
}

void dae::Coily::Update()
{
	if (!m_Freeze)
	{
		CoilyState::CoilyStateEnum nextState = m_CurrentState->GetNextState(this);
		if (nextState == m_CurrentState->GetState())
		{
			m_CurrentState->Update(this);
		}
		else
		{
			m_CurrentState = m_pCoilyState[nextState].get();
		}

	}




}

void dae::Coily::Reset()
{
	m_CurrentPos = glm::vec2(m_pPyramid->GetStartPos(m_StartingIndex).x, m_pPyramid->GetStartPos(m_StartingIndex).y - spriteInfo.height / 2.f);
	m_TargetPos = m_CurrentPos;
	m_pPyramidMovementComponent->SetCurrentIndex(m_StartingIndex);
	m_pPyramidMovementComponent->SetCurrentRow(m_StartRow);
	m_pPyramidMovementComponent->SetCurrentPos(m_CurrentPos);
	m_pTextureComponent->SetSourceInfo(0,0,16,32);
	m_CurrentState = m_pCoilyState[CoilyState::CoilyStateEnum::Egg].get();

	

}



dae::PyramidMovementComponent* dae::Coily::GetPyramidMovementComponent() const
{
	if (m_CurrentState && m_CurrentState->GetState() == CoilyState::CoilyStateEnum::Snake)
	{
		return m_pPyramidMovementComponent;
	}
	else
	{
		return nullptr; // Return nullptr if not in Snake state
	}
}

dae::Qbert* dae::Coily::GetQbert() const
{
	Qbert* closestQbert = nullptr;
	float closestDistance = std::numeric_limits<float>::max(); // Initialize with a large value

	for (auto& qbert : m_pQbert)
	{
		auto qbertComponent = qbert->GetComponent<Qbert>();
		if (qbertComponent != nullptr)
		{
			// Calculate distance between Coily and current Qbert
			glm::vec2 coilyPos = m_pPyramidMovementComponent->GetCurrentPos();
			glm::vec2 qbertPos = qbertComponent->GetCurrentPos();
			float distance = std::abs(qbertPos.x - coilyPos.x) + std::abs(qbertPos.y - coilyPos.y);

			// Update closest Qbert if this Qbert is closer
			if (distance < closestDistance)
			{
				closestQbert = qbertComponent;
				closestDistance = distance;
			}
		}
	}

	return closestQbert;
}




