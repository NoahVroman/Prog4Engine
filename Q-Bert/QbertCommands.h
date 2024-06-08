#pragma once
#include "Command.h"
#include "GameObject.h"
#include "Qbert.h"
#include "ServiceLocator.h"


class MoveDownRightCommand : public dae::GameObjectCommand
{
	public:

		MoveDownRightCommand(std::shared_ptr<dae::GameObject> pGameObject) : GameObjectCommand(pGameObject)
		{
		
		}

		void Execute() override 
		{
			
			if (auto qbert = GetGameObject()->GetComponent<dae::Qbert>())
			{
				qbert->MoveDownRight();
				qbert->SetFrozen(false);
			}

		};


};

class MoveDownLeftCommand : public dae::GameObjectCommand
{
public:

	MoveDownLeftCommand(std::shared_ptr<dae::GameObject> pGameObject) : GameObjectCommand(pGameObject)
	{

	}

	void Execute() override
	{

		if (auto qbert = GetGameObject()->GetComponent<dae::Qbert>())
		{
			qbert->MoveDownLeft();
			qbert->SetFrozen(false);
		}

	};


};

class MoveUpLeftCommand : public dae::GameObjectCommand
{
public:

	MoveUpLeftCommand(std::shared_ptr<dae::GameObject> pGameObject) : GameObjectCommand(pGameObject)
	{

	}

	void Execute() override
	{

		if (auto qbert = GetGameObject()->GetComponent<dae::Qbert>())
		{
			qbert->MoveUpLeft();
			qbert->SetFrozen(false);
		}

	};


};


class MoveUpRightCommand : public dae::GameObjectCommand
{
public:

	MoveUpRightCommand(std::shared_ptr<dae::GameObject> pGameObject) : GameObjectCommand(pGameObject)
	{

	}

	void Execute() override
	{

		if (auto qbert = GetGameObject()->GetComponent<dae::Qbert>())
		{
			qbert->MoveUpRight();
			qbert->SetFrozen(false);
		}

	};


};