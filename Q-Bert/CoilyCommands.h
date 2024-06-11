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

		
		if (GetGameObject() != nullptr)
		{
			auto coily = GetGameObject()->GetComponent<dae::Coily>();
			if (!coily)
			{
				std::cout << "No Coily component found; cannot move." << std::endl;
				return;
			}

			// Check if Coily has the PyramidMovementComponent
			auto movementComponent = coily->GetPyramidMovementComponent();
			if (!movementComponent)
			{
				std::cout << "Coily is not in the Snake state; cannot move." << std::endl;
				return;
			}

			if (movementComponent->GetCurrentRow() < movementComponent->GetRows() - 1)
			{
				movementComponent->MoveDownRight();
			}
			else
			{
				std::cout << "Movement condition not met for MoveDownRight." << std::endl;
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
			if (GetGameObject() != nullptr)
			{
				auto coily = GetGameObject()->GetComponent<dae::Coily>();
				if (!coily)
				{
					std::cout << "No Coily component found; cannot move." << std::endl;
					return;
				}

				auto movementComponent = coily->GetPyramidMovementComponent();
				if (!movementComponent)
				{
					std::cout << "Coily is not in the Snake state; cannot move." << std::endl;
					return;
				}

				if (movementComponent->GetCurrentRow() < movementComponent->GetRows() - 1)
				{
					movementComponent->MoveDownLeft();
				}
				else
				{
					std::cout << "Movement condition not met for MoveDownLeft." << std::endl;
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
			if (GetGameObject() != nullptr)
			{
				auto coily = GetGameObject()->GetComponent<dae::Coily>();
				if (!coily)
				{
					std::cout << "No Coily component found; cannot move." << std::endl;
					return;
				}

				auto movementComponent = coily->GetPyramidMovementComponent();
				if (!movementComponent)
				{
					std::cout << "Coily is not in the Snake state; cannot move." << std::endl;
					return;
				}

				if (!movementComponent->IsOnFirstCubeInRow())
				{
					movementComponent->MoveUpLeft();
				}
				else
				{
					std::cout << "Movement condition not met for MoveUpLeft." << std::endl;
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
			if (GetGameObject() != nullptr)
			{
				auto coily = GetGameObject()->GetComponent<dae::Coily>();
				if (!coily)
				{
					std::cout << "No Coily component found; cannot move." << std::endl;
					return;
				}

				auto movementComponent = coily->GetPyramidMovementComponent();
				if (!movementComponent)
				{
					std::cout << "Coily is not in the Snake state; cannot move." << std::endl;
					return;
				}

				if (!movementComponent->IsOnLastCubeInRow())
				{
					movementComponent->MoveUpRight();
				}
				else
				{
					std::cout << "Movement condition not met for MoveUpRight." << std::endl;
				}

			}

		}

	
};
