#include "SnakeState.h"
#include "GameTime.h"
dae::SnakeState::SnakeState(GameObject* const pParent)
	: CoilyState(CoilyStateEnum::Snake,pParent)
    , m_JumpInterval{ 1.f }
    , m_JumpTimer{ 0.0f }
    , m_Direction{ dae::SnakeState::Direction::UpRight }
{

}

dae::SnakeState::~SnakeState()
{

}

void dae::SnakeState::Update(Coily* coily)
{
    glm::vec2 qbertPos = coily->GetQbert()->GetCurrentPos() - GetPyramidMovementComponent()->GetCurrentPos();



    if (coily->GetQbert()->GetCurrentIndex() == GetPyramidMovementComponent()->GetCurrentIndex())
    {
        coily->GetSubject().Notify(Event::QbertDied);
    }


    m_JumpTimer += GameTime::GetInstance().GetDeltaTime();

    if (m_JumpTimer >= m_JumpInterval)
    {
        
        HandleMovement(coily);
        m_JumpTimer = 0.0f;
    }

    UpdateTexture();


}

void dae::SnakeState::HandleMovement(Coily* coily)
{
    glm::vec2 qbertPos = coily->GetQbert()->GetCurrentPos() - GetPyramidMovementComponent()->GetCurrentPos();
    bool isOnSameRow = coily->GetQbert()->GetCurrentRow() == GetPyramidMovementComponent()->GetCurrentRow();
    qbertPos.y = -qbertPos.y;


    if (qbertPos.x >= 0 && (qbertPos.y > 0 || isOnSameRow))
    {
        if (!IsOnLastCubeInRow())
        {
            m_Direction = Direction::UpRight;
            GetPyramidMovementComponent()->MoveUpRight();
        }

    }
    else if (qbertPos.x < 0 && (qbertPos.y > 0 || isOnSameRow))
    {
        if (!IsOnFirstCubeInRow())
        {
            m_Direction = Direction::UpLeft;
            GetPyramidMovementComponent()->MoveUpLeft();
        }
    }
    else if (qbertPos.x > 0 && qbertPos.y <= 0)
    {
        if (GetPyramidMovementComponent()->GetCurrentRow() < GetPyramidMovementComponent()->GetRows() - 1)
        {
            m_Direction = Direction::DownRight;
            GetPyramidMovementComponent()->MoveDownRight();
        }
    }
    else if (qbertPos.x < 0 && qbertPos.y < 0)
    {
        if (GetPyramidMovementComponent()->GetCurrentRow() < GetPyramidMovementComponent()->GetRows() - 1)
        {
            m_Direction = Direction::DownLeft;
            GetPyramidMovementComponent()->MoveDownLeft();
        }
    }


}

void dae::SnakeState::UpdateTexture()
{
    float baseIndex = 0.0f;
    if (GetPyramidMovementComponent()->IsMoving())
    {
        baseIndex = 1.0f;
    }

    constexpr float textureWidth = 16.0f; 
    constexpr float textureHeight = 32.0f;
    const float textureOffsets[] = {
        2.0f * textureWidth,  // UpRight (stationary)
        3.0f * textureWidth,  // UpRight (moving)
        4.0f * textureWidth,  // UpLeft (stationary)
        5.0f * textureWidth,  // UpLeft (moving)
        6.0f * textureWidth,  // DownRight (stationary)
        7.0f * textureWidth,  // DownRight (moving)
        8.0f * textureWidth,  // DownLeft (stationary)
        9.0f * textureWidth   // DownLeft (moving)
    };

    int directionIndex = static_cast<int>(m_Direction);
    float index = 2.0f * directionIndex + baseIndex;
    float sourceX = textureOffsets[static_cast<int>(index)];
    GetTextureComponent()->SetSourceInfo(sourceX, 0.0f, textureWidth, textureHeight);
}


dae::CoilyState::CoilyStateEnum dae::SnakeState::GetNextState(Coily*)
{
    return CoilyStateEnum::Snake;
}


