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

		
		// Check if the GameObject has a Coily component

	
		if (auto coily = GetGameObject()->GetComponent<dae::Coily>())
		{
			// Check if Coily has the PyramidMovementComponent
			auto movementComponent = coily->GetPyramidMovementComponent();
			if (!movementComponent)
			{
				std::cout << "Coily is not in the Snake state; cannot move." << std::endl;
				return;
			}

			// Check movement conditions and execute movement
			if (!movementComponent->IsOnFirstCubeInRow() && !movementComponent->IsOnLastCubeInRow())
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

			
			if (auto coily = GetGameObject()->GetComponent<dae::Coily>())
			{
				auto movementComponent = coily->GetPyramidMovementComponent();
				if (!movementComponent)
				{
					std::cout << "Coily is not in the Snake state; cannot move." << std::endl;
					return;
				}

				if (!movementComponent->IsOnFirstCubeInRow() && !movementComponent->IsOnLastCubeInRow())
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

			
			if (auto coily = GetGameObject()->GetComponent<dae::Coily>())
			{
				auto movementComponent = coily->GetPyramidMovementComponent();
				if (!movementComponent)
				{
					std::cout << "Coily is not in the Snake state; cannot move." << std::endl;
					return;
				}

				if (!movementComponent->IsOnFirstCubeInRow() && !movementComponent->IsOnLastCubeInRow())
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

			if (auto coily = GetGameObject()->GetComponent<dae::Coily>())
			{
				auto movementComponent = coily->GetPyramidMovementComponent();
				if (!movementComponent)
				{
					std::cout << "Coily is not in the Snake state; cannot move." << std::endl;
					return;
				}

				if (!movementComponent->IsOnFirstCubeInRow() && !movementComponent->IsOnLastCubeInRow())
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
