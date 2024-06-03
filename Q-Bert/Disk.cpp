#include "Disk.h"
#include "GameTime.h"
#include <glm/glm.hpp>

dae::Disk::Disk(GameObject* const pParent, GameObject* qbert, LevelPyramid* levelPyramid, int startRow, bool isLeft, int colorIndex)
    : Component(pParent)
    , m_pParent{ pParent }
    , m_QbertObj{ qbert }
    , m_StartRow{ startRow }
    , m_IsLeft{ isLeft }
    , m_ColorIndex{ colorIndex }
    , m_FloatTime{ 0.0f }
    , QbertFallSpeed{ 1.f }
    , m_Activated{ false }
    , m_pQbert{ nullptr }
    , m_pTextureComponent{ nullptr }
    , m_pLevelPyramid{ levelPyramid }
    , m_TargetPos{ levelPyramid->GetStartPos(0) + glm::vec2{0,-25} }
    , m_TimeSinceLastFrameIdle{ 0.0f }
    , m_FPSIdle{ 9 }
    , m_CurrentFrame{ 0 }
    , m_MaxFramesIdle{ 4 }
    , m_PreviousRow{ -1 }
    , m_PreviousIndex{ -1 }
    , m_FinalPositionReached{ false }
    , m_FlightTime{ 2.0f }
    , m_MaxFallTime{ 1.f }
    , m_FallTime{ 0.0f }
{
    m_pQbert = m_QbertObj->GetComponent<Qbert>();

    glm::vec2 offset = (isLeft) ?
        glm::vec2{ -m_pLevelPyramid->GetQuarterCubeWidth(), -m_pLevelPyramid->GetHalfCubeHeight() } :
        glm::vec2{ m_pLevelPyramid->GetThreeQuartersCubeWidth(), -m_pLevelPyramid->GetHalfCubeHeight() };

    m_CurrentPos = (isLeft) ?
        m_pLevelPyramid->GetPosFirstCubeInRow(m_StartRow) + offset :
        m_pLevelPyramid->GetPosLastCubeInRow(m_StartRow) + offset;

    m_SpriteInfo = { 32, 32, 0, 0, 16, 10 };
    m_pTextureComponent = m_pParent->AddComponent<TextureComponent>("Disk.png", m_SpriteInfo);

    m_pParent->GetTransform()->SetLocalPosition(m_CurrentPos);
}

dae::Disk::~Disk() = default;

void dae::Disk::Update()
{
    UpdateAnimation();
    CheckQbertActivation();

    if (m_Activated)
    {
        UpdateFlight();
    }
}

void dae::Disk::UpdateAnimation()
{
    m_TimeSinceLastFrameIdle += GameTime::GetInstance().GetDeltaTime();

    if (m_TimeSinceLastFrameIdle >= 1.f / static_cast<float>(m_FPSIdle))
    {
        m_TimeSinceLastFrameIdle -= 1.f / static_cast<float>(m_FPSIdle);

        m_pTextureComponent->SetSourceInfo(static_cast<float>(m_ColorIndex * 5) * m_SpriteInfo.SrcWidth + m_CurrentFrame * m_SpriteInfo.SrcWidth, 0, m_SpriteInfo.SrcWidth, m_SpriteInfo.SrcHeight);
        m_CurrentFrame = (m_CurrentFrame + 1) % m_MaxFramesIdle;
    }
}

void dae::Disk::CheckQbertActivation()
{
    int currentRow = m_pQbert->GetCurrentRow();
    int currentIndex = m_pQbert->GetCurrentIndex();

    if ((currentRow == m_StartRow) && (currentIndex == -1))
    {
        if ((m_IsLeft && (m_PreviousRow == m_StartRow) && (m_PreviousIndex == m_pLevelPyramid->GetFirstCubeInRow(m_StartRow))) ||
            (!m_IsLeft && (m_PreviousRow == m_StartRow) && (m_PreviousIndex == m_pLevelPyramid->GetLastCubeInRow(m_StartRow))))
        {
            m_Activated = true;
        }
    }

    m_PreviousRow = currentRow;
    m_PreviousIndex = currentIndex;
}

void dae::Disk::UpdateFlight()
{
    if (!m_FinalPositionReached)
    {
        m_pQbert->SetFrozen(true);

        m_FloatTime += GameTime::GetInstance().GetDeltaTime();
        float progress = m_FloatTime / m_FlightTime;

        glm::vec2 newPosition = glm::mix(m_CurrentPos, m_TargetPos, progress);
        m_pParent->GetTransform()->SetLocalPosition(newPosition);
        m_QbertObj->GetTransform()->SetLocalPosition({ newPosition.x, newPosition.y - 27 });

        if (progress >= 1.0f)
        {
            m_FinalPositionReached = true;
            m_pParent->GetTransform()->SetLocalPosition(m_TargetPos - glm::vec2{ 0.f,1000.f });

            m_FallTime = 0.0f; 
        }
    }
    else
    {
        m_FallTime += GameTime::GetInstance().GetDeltaTime();
        float fallProgress = m_FallTime / m_MaxFallTime;

        glm::vec2 fallPosition = glm::mix(m_TargetPos, m_pQbert->GetCurrentPos(), fallProgress);
        m_QbertObj->GetTransform()->SetLocalPosition(fallPosition);

        if (fallProgress >= 1.0f)
        {
            m_pParent->Destroy();
            m_pQbert->Reset();
        }
    }
}
