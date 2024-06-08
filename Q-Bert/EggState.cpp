#include "EggState.h"
#include "Coily.h"
#include "SnakeState.h"
#include "TextComponent.h"
#include "GameTime.h"
#include <iostream>

dae::EggState::EggState(GameObject* const pParent)
    : CoilyState(CoilyState::CoilyStateEnum::Egg,pParent)
    , m_JumpInterval{ 1.f }
    , m_JumpTimer{ 0.0f }
    , m_StateChangeDelay{ 1.f }
    , m_StateTimer{ 0.0f }
{
   
    srand(static_cast<unsigned int>(time(nullptr)));
    
}

dae::EggState::~EggState()
{

}


dae::CoilyState::CoilyStateEnum dae::EggState::GetNextState(Coily*)
{
    if (GetPyramidMovementComponent()->GetCurrentRow() >= GetPyramidMovementComponent()->GetRows() - 1)
    {
        m_StateTimer += GameTime::GetInstance().GetDeltaTime();

        if (m_StateTimer >= m_StateChangeDelay)
        {
            return CoilyStateEnum::Snake;

        }
    }

    return CoilyStateEnum::Egg;
}

void dae::EggState::Update(Coily*coily)
{
    Qbert* closestQbert = coily->GetQbert();

    if (closestQbert)
    {



        if (coily->GetQbert()->GetPreviousIndex() == 0 || closestQbert->HasJustJumped())
        {
            if (!closestQbert->isOnDisk())
            {
                if (coily->GetQbert()->GetCurrentIndex() == GetPyramidMovementComponent()->GetCurrentIndex())
                {
                    coily->GetSubject().Notify(Event::QbertDied, m_pParent);
                }

            }

        }
    }


    m_JumpTimer += GameTime::GetInstance().GetDeltaTime();

    if (GetPyramidMovementComponent()->GetCurrentRow() < GetPyramidMovementComponent()->GetRows() - 1)
    {
        if (GetPyramidMovementComponent()->IsMoving())
        {
            GetTextureComponent()->SetSourceInfo(16, 0, 16, 32);
        }
        else
        {
            GetTextureComponent()->SetSourceInfo(0, 0, 16, 32);
        }

        if (m_JumpTimer >= m_JumpInterval)
        {

            int random = rand() % 2;
            if (random == 0)
            {
                GetPyramidMovementComponent()->MoveDownLeft();
            }
            else
            {
                GetPyramidMovementComponent()->MoveDownRight();
            }
			m_JumpTimer = 0;
        }
    }	
}
