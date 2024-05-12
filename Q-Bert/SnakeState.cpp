#include "SnakeState.h"
dae::SnakeState::SnakeState()
	: CoilyState(CoilyStateEnum::Snake)
{

}

dae::SnakeState::~SnakeState()
{
}


void dae::SnakeState::Update(Coily* coily)
{
    glm::vec2 qbertPos = coily->GetQbert()->GetCurrentPos() -  coily->GetCurrentPos();
    bool isOnSameRow = coily->GetQbert()->GetCurrentRow() == coily->GetCurrentRow();
    qbertPos.y = -qbertPos.y; 

    if (qbertPos.x >= 0 && (qbertPos.y > 0 || isOnSameRow))
    {
        coily->MoveUpRight();
    }
    else if (qbertPos.x < 0 && (qbertPos.y > 0 || isOnSameRow))
    {
        coily->MoveUpLeft();
    }
    else if (qbertPos.x > 0 && qbertPos.y < 0)
    {
        coily->MoveDownRight();
    }
    else if (qbertPos.x < 0 && qbertPos.y < 0)
    {
        coily->MoveDownLeft();
    }
}

dae::CoilyState::CoilyStateEnum dae::SnakeState::GetNextState(Coily*)
{
    return CoilyStateEnum::Snake;
}


