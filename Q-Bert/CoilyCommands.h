#pragma once
#include "Command.h"
#include "GameObject.h"
#include "Coily.h"
#include "PyramidMovementComponent.h"

class MoveDownRightCommandCoily : public dae::GameObjectCommand
{
public:

	MoveDownRightCommandCoily(std::shared_ptr<dae::GameObject> pGameObject) : GameObjectCommand(pGameObject)
	{

	}

	void Execute() override
	{

		if (auto coily = GetGameObject()->GetComponent<dae::Coily>())
		{
			if (auto movementComponent = coily->GetPyramidMovementComponent())
			{
				if (!movementComponent->IsOnFirstCubeInRow() || !movementComponent->IsOnLastCubeInRow())
				{
					movementComponent->MoveDownRight();
				}	
			}
			else
			{
				std::cout << "Coily is not in the Snake state; cannot move." << std::endl;
			}
		}

	};


};

class MoveDownLeftCommandCoily : public dae::GameObjectCommand
{

	public:

		MoveDownLeftCommandCoily(std::shared_ptr<dae::GameObject> pGameObject) : GameObjectCommand(pGameObject)
		{

		}

		void Execute() override
		{

			if (auto coily = GetGameObject()->GetComponent<dae::Coily>())
			{
				if (auto movementComponent = coily->GetPyramidMovementComponent())
				{
					if (!movementComponent->IsOnFirstCubeInRow() || !movementComponent->IsOnLastCubeInRow())
					{

						movementComponent->MoveDownLeft();
					}
				}
				else
				{
					std::cout << "Coily is not in the Snake state; cannot move." << std::endl;
				}
			}
		}


};

class MoveUpLeftCommandCoily : public dae::GameObjectCommand
{
		
	public:

		MoveUpLeftCommandCoily(std::shared_ptr<dae::GameObject> pGameObject) : GameObjectCommand(pGameObject)
		{

		}

		void Execute() override
		{

			if (auto coily = GetGameObject()->GetComponent<dae::Coily>())
			{
				if (auto movementComponent = coily->GetPyramidMovementComponent())
				{
					if (!movementComponent->IsOnFirstCubeInRow() || !movementComponent->IsOnLastCubeInRow())
					{

						movementComponent->MoveUpLeft();
					}
				}
				else
				{
					std::cout << "Coily is not in the Snake state; cannot move." << std::endl;
				}
			}
		}
	
};


class MoveUpRightCommandCoily : public dae::GameObjectCommand
{
		
	public:

		MoveUpRightCommandCoily(std::shared_ptr<dae::GameObject> pGameObject) : GameObjectCommand(pGameObject)
		{

		}

		void Execute() override
		{

			if (auto coily = GetGameObject()->GetComponent<dae::Coily>())
			{
				if (auto movementComponent = coily->GetPyramidMovementComponent())
				{
					if (!movementComponent->IsOnFirstCubeInRow() || !movementComponent->IsOnLastCubeInRow())
					{
						movementComponent->MoveUpRight();

					}
				}
				else
				{
					std::cout << "Coily is not in the Snake state; cannot move." << std::endl;
				}
			}
		}

	
};
