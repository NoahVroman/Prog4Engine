#include "EggState.h"
#include "Coily.h"
#include "SnakeState.h"
#include <ctime>

dae::EggState::EggState()
    : CoilyState(CoilyState::CoilyStateEnum::Egg)
{
   
    srand(static_cast<unsigned int>(time(nullptr)));
    
}

dae::EggState::~EggState()
{

}


dae::CoilyState::CoilyStateEnum dae::EggState::GetNextState(Coily* coily)
{
    if (coily->GetCurrentRow() >= coily->GetPyramid()->GetRows() - 1)
    {
        return CoilyStateEnum::Snake;
    }

    return CoilyStateEnum::Egg;
}

void dae::EggState::Update(Coily* coily)
{
    if (coily->GetCurrentRow() < coily->GetPyramid()->GetRows() - 1)
    {
        int random = rand() % 2;
        if (random == 0)
        {
            coily->MoveDownLeft();
        }
        else
        {
            coily->MoveDownRight();
        }
    }	
}
