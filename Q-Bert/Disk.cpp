#include "Disk.h"
#include "GameTime.h"
#include <glm/glm.hpp>

dae::Disk::Disk(GameObject* const pParent, GameObject* qbert, LevelPyramid* levelPyramid, int startRow, bool isLeft, int colorindex)
	:Component(pParent)
	,m_pParent{pParent}
	,m_QbertObj{ qbert }
	,m_StartRow{startRow}
	,m_IsLeft{isLeft}
	,m_ColorIndex{colorindex}
	,m_FloatTime{0.0f}
	,QbertFallSpeed{0.0f}
	,m_Activated{false}
	,m_pQbert{nullptr}
	,m_pTextureComponent{nullptr}
	,m_pLevelPyramid{levelPyramid}
	,m_TargetPos{ levelPyramid->GetStartPos(0)}
	,m_TimeSinceLastFrameIdle{0.0f}
	,m_FPSIdle{9}
	,m_CurrentFrame{0}
	,m_MaxFramesIdle{4}
	,m_PreviousRow{-1}
	,m_PreviousIndex{-1}
	,m_FinalPositionReached{false}
	,m_FlightTime{2.f}


{
	m_pQbert = m_QbertObj->GetComponent<Qbert>();

	glm::vec2 offset;
	if (isLeft)
	{
		offset = { -m_pLevelPyramid->GetQuarterCubeWidth(), -m_pLevelPyramid->GetHalfCubeHeight() };
		m_CurrentPos = m_pLevelPyramid->GetPosFirstCubeInRow(m_StartRow)  + offset;
	}
	else
	{
		offset = { m_pLevelPyramid->GetThreeQuartersCubeWidth(), -m_pLevelPyramid->GetHalfCubeHeight() };
		m_CurrentPos = m_pLevelPyramid->GetPosLastCubeInRow(m_StartRow) + offset;
	}


	spriteInfo.height = 32;
	spriteInfo.width = 32;
	spriteInfo.SrcX = 0;
	spriteInfo.SrcY = 0;
	spriteInfo.SrcWidth = 16;
	spriteInfo.SrcHeight = 10;

	m_pTextureComponent = m_pParent->AddComponent<TextureComponent>("Disk.png",spriteInfo);

	m_pParent->GetTransform()->SetLocalPosition(m_CurrentPos);

}

dae::Disk::~Disk()
{

}

void dae::Disk::Update()
{
	m_TimeSinceLastFrameIdle += GameTime::GetInstance().GetDeltaTime();

	if (m_TimeSinceLastFrameIdle >= 1.f / float(m_FPSIdle))
	{
		m_TimeSinceLastFrameIdle -= 1.f / float(m_FPSIdle);

		m_pTextureComponent->SetSourceInfo(float(m_ColorIndex * 5) * spriteInfo.SrcWidth + m_CurrentFrame * spriteInfo.SrcWidth, 0, spriteInfo.SrcWidth, spriteInfo.SrcHeight);
		m_CurrentFrame++;

		if (m_CurrentFrame >= m_MaxFramesIdle)
			m_CurrentFrame = 0;
	}

	if ((m_pQbert->GetCurrentRow() == m_StartRow) && m_pQbert->GetCurrentIndex() == -1 && m_IsLeft)
	{
		if (m_PreviousRow == m_StartRow && m_PreviousIndex == m_pLevelPyramid->GetFirstCubeInRow(m_StartRow))
		{
			m_Activated = true;
		}
	}
	else if ((m_pQbert->GetCurrentRow() == m_StartRow) && m_pQbert->GetCurrentIndex() == -1 && !m_IsLeft)
	{
		if (m_PreviousRow == m_StartRow && m_PreviousIndex == m_pLevelPyramid->GetLastCubeInRow(m_StartRow))
		{
			m_Activated = true;
		}
	}
	m_PreviousRow = m_pQbert->GetCurrentRow();
	m_PreviousIndex = m_pQbert->GetCurrentIndex();

	if (m_Activated)
	{
		m_FloatTime += GameTime::GetInstance().GetDeltaTime();

		if (!m_FinalPositionReached)
		{

			
			float progress = m_FloatTime / m_FlightTime;
			glm::vec2 newPosition = glm::mix(m_CurrentPos, m_TargetPos, progress);
			m_pParent->GetTransform()->SetLocalPosition(newPosition);


			m_QbertObj->GetTransform()->SetLocalPosition({newPosition.x,newPosition.y - 27});

			if (progress >= 1.0f)
			{
				m_FinalPositionReached = true;
				m_pParent->Destroy();
			}
		}
	}
}
