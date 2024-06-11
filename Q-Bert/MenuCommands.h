#pragma once
#include "Command.h"
#include "GameObject.h"
#include "StartScreenSelection.h"
#include "SceneManager.h"

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

		StartScreenSelect(std::shared_ptr<dae::GameObject> pGameObject) : GameObjectCommand(pGameObject)
		{

		}

		void Execute() override
		{

			if (auto startScreen = GetGameObject()->GetComponent<dae::StartScreenSelection>())
			{
				startScreen->Confirm();
			}

	};
};

class LevelSkip : public dae::GameObjectCommand
{

	public:

		LevelSkip(std::shared_ptr<dae::GameObject> pGameObject) : GameObjectCommand(pGameObject)
			, presscount(0)

		{

		}

		void Execute() override
		{
			++presscount;
			if (presscount < 3 )
			{
				dae::SceneManager::GetInstance().ChangeScene(dae::SceneManager::GetInstance().GetCurrentSceneIndex() + 3);

			}


		};
private:
	int presscount;


};	

class BackToMenu : public dae::GameObjectCommand
{

	public:

		BackToMenu(std::shared_ptr<dae::GameObject> pGameObject) : GameObjectCommand(pGameObject)
		{

		}

		void Execute() override
		{
			dae::SceneManager::GetInstance().ChangeScene(0);
		};

};
