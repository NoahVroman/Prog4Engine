#include "Coily.h"
#include "LevelCube.h"
#include "GameTime.h"
#include "TransfomComponent.h"
#include <iostream>
#include "EggState.h"
#include "SnakeState.h"
#include "ServiceLocator.h"

dae::Coily::Coily(GameObject* const pParent, Qbert* pQbert, LevelPyramid* pyramid, int StartingIndex, int StartRow)
	:Component(pParent)
	, m_pQbert(pQbert)
	, m_pPyramid(pyramid)
	, m_StartingIndex(StartingIndex)
	, m_StartRow(StartRow)
	, m_pParent(pParent)
	

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
	m_pCoilyState[CoilyState::CoilyStateEnum::Snake] = std::make_unique<SnakeState>(m_pParent);
	m_CurrentState = m_pCoilyState[CoilyState::CoilyStateEnum::Egg].get();
}

void dae::Coily::Update()
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




