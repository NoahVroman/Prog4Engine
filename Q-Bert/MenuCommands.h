#pragma once
#include "Command.h"
#include "GameObject.h"
#include "StartScreenSelection.h"
#include "SceneManager.h"
#include "RoundManager.h"

class StartScreenMoveDown : public dae::GameObjectCommand
{
public:

	StartScreenMoveDown(std::shared_ptr<dae::GameObject> pGameObject) : GameObjectCommand(pGameObject)
	{

	}

	void Execute() override
	{

		if (auto startScreen = GetGameObject()->GetComponent<dae::StartScreenSelection>())
		{
			startScreen->MoveDown();
		}

	};


};

class StartScreenMoveUp : public dae::GameObjectCommand
{

	public:

		StartScreenMoveUp(std::shared_ptr<dae::GameObject> pGameObject) : GameObjectCommand(pGameObject)
		{

	}

		void Execute() override
		{

			if (auto startScreen = GetGameObject()->GetComponent<dae::StartScreenSelection>())
			{
			startScreen->MoveUp();
		}

	};
};


class StartScreenSelect : public dae::GameObjectCommand
{
	
	public:

		StartScreenSelect(std::shared_ptr<dae::GameObject> pGameObject, std::shared_ptr<dae::RoundManager> roundManager ) : GameObjectCommand(pGameObject), m_RoundManager(roundManager)
		{

		}

		void Execute() override
		{

			if (auto startScreen = GetGameObject()->GetComponent<dae::StartScreenSelection>())
			{
				startScreen->Confirm(*m_RoundManager);
			}

		};
		private:
			std::shared_ptr<dae::RoundManager> m_RoundManager;
};





