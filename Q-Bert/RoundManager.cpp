#include "RoundManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TransfomComponent.h"
#include "TextureComponent.h"
#include "LevelPyramid.h"
#include "Qbert.h"
#include "InputManager.h"
#include "QbertCommands.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include <LoggingSoundSystem.h>
#include "SDLSoundSystem.h"
#include "LevelManager.h"
#include "Coily.h"
#include "UggWrongWay.h"
#include "SlickSam.h"
#include "Disk.h"
#include "StartScreenSelection.h"
#include "MenuCommands.h"
#include "ScoreAndLivesManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>


namespace dae
{
	RoundManager::RoundManager()
        :m_Rounds{}
        ,m_CurrentRoundIdx{0}
        ,m_CurrentLevelIdx{0}
	{

	}


	RoundManager::~RoundManager()
	{
	}

	void RoundManager::LoadRoundData(const std::string& filePath, const std::string& SceneName)
	{
        SceneManager::GetInstance().CreateScene(SceneName);

        std::ifstream levelFile(filePath);
        if (!levelFile) {
            std::cout << "Level file couldn't be opened\n";
            return;
        }


        std::string line;
        while (std::getline(levelFile, line)) {
            Round round;
            std::istringstream iss(line);
            std::string key;
            while (iss >> key) {
                if (key == "Round") {
                    iss >> round.roundNumber;
                }
                else if (key == "Level") {
                    iss >> round.level;
                }
                else if (key == "ColorIdx") {
                    iss >> round.colorIdx;
                }
                else if (key == "SpawnSlickSams") {
                    iss >> round.spawnSlickSams;
                }
                else if (key == "SpawnUggWrongs") {
                    iss >> round.spawnUggWrongs;
                }
                else if (key == "SlickSamsSpawnInterval") {
                    iss >> round.slickSamsSpawnInterval;
                }
                else if (key == "UggWrongSpawnInterval") {
                    iss >> round.uggWrongSpawnInterval;
                }
                else if (key == "GameMode") {
                    iss >> round.gameMode;
                }
            }
            if (line.empty()) {
                m_Rounds.push_back(round);
            }
        }
        levelFile.close();
	}

	std::vector<std::shared_ptr<GameObject>> RoundManager::MakeUI()
	{
		auto& resourceManager = dae::ResourceManager::GetInstance();
		auto mainTextFont = resourceManager.LoadFont("Minecraft.ttf", 20);

		std::vector<std::shared_ptr<dae::GameObject>> UI;

		std::string livesStr = "Lives: 3";
		std::string roundStr = "Round: " + std::to_string(m_Rounds[m_CurrentRoundIdx].roundNumber);
		std::string levelStr = "Level: " + std::to_string(m_Rounds[m_CurrentRoundIdx].level);

		auto score = std::make_shared<dae::GameObject>();
		score->GetTransform()->SetLocalPosition(glm::vec2{ 0,0 });
		score->AddComponent<dae::TextComponent>("Score: 0", mainTextFont);

		UI.push_back(score);

		auto lives = std::make_shared<dae::GameObject>();
		lives->GetTransform()->SetLocalPosition(glm::vec2{ 0,50 });
		lives->AddComponent<dae::TextComponent>(livesStr, mainTextFont);
		UI.push_back(lives);

		ScoreAndLivesManager::GetInstance().Initialize(score->GetComponent<dae::TextComponent>(), lives->GetComponent<dae::TextComponent>());

		auto roundText = std::make_shared<dae::GameObject>();
		roundText->GetTransform()->SetLocalPosition(glm::vec2{ 250,440 });
		roundText->AddComponent<dae::TextComponent>(roundStr, mainTextFont);
		UI.push_back(roundText);

		auto levelText = std::make_shared<dae::GameObject>();
		levelText->GetTransform()->SetLocalPosition(glm::vec2{ 350,440 });
		levelText->AddComponent<dae::TextComponent>(levelStr, mainTextFont);
		UI.push_back(levelText);

		return UI;
	}





	void RoundManager::SwitchToNextRound()
	{
		++m_CurrentRoundIdx;
			ResetRound();

	}

	void RoundManager::ResetRound()
	{


		dae::LevelPyramid::PyramidSettings settings{};
		settings.StartPos = glm::vec2{ 300,70 };
		settings.Rows = 7;
		settings.CubeSize = glm::vec2{ 62, 64 };
		settings.Level = m_Rounds[m_CurrentRoundIdx].level;
		settings.ColorIndex = m_Rounds[m_CurrentRoundIdx].colorIdx;
		settings.SpriteSize = glm::vec2{ 32, 32 };

		m_pLevelPyramid->SetSettings(settings);
		m_pLevelPyramid->NextRound();

		m_pLevelManager->InitializeRound(m_Rounds[m_CurrentRoundIdx].level, m_Rounds[m_CurrentRoundIdx].roundNumber, m_Rounds[m_CurrentRoundIdx].spawnSlickSams, m_Rounds[m_CurrentRoundIdx].spawnUggWrongs, m_Rounds[m_CurrentRoundIdx].slickSamsSpawnInterval, m_Rounds[m_CurrentRoundIdx].uggWrongSpawnInterval, m_Rounds[m_CurrentRoundIdx].gameMode);
		m_pDisk->SetColorIndex(m_Rounds[m_CurrentRoundIdx].colorIdx);
		m_pDisk2->SetColorIndex(m_Rounds[m_CurrentRoundIdx].colorIdx);



	}

	void RoundManager::SwithToNextLevel()
	{
        SceneManager::GetInstance().ChangeScene(SceneManager::GetInstance().GetCurrentSceneIndex() + 1);
        
        LoadLevel();

	}

    void RoundManager::LoadLevel()
    {
		auto scene = SceneManager::GetInstance().GetCurrentScene();

		auto level = std::make_shared<dae::GameObject>();
		level->GetTransform()->SetLocalPosition(glm::vec2{ 0,0 });

		dae::LevelPyramid::PyramidSettings settings{};
		settings.StartPos = glm::vec2{ 300,70 };
		settings.Rows = 7;
		settings.CubeSize = glm::vec2{ 62, 64 };
		settings.Level = m_Rounds[m_CurrentRoundIdx].level;
		settings.ColorIndex = m_Rounds[m_CurrentRoundIdx].colorIdx;
		settings.SpriteSize = glm::vec2{ 32, 32 };

		m_pLevelPyramid = level->AddComponent<dae::LevelPyramid>(settings);

		for (const auto& cube : m_pLevelPyramid->GetCubes())
		{
			scene->Add(cube);
		}

		scene->Add(level);


		std::vector<std::shared_ptr<dae::GameObject>> qberts;
		auto Qbert1 = std::make_shared<dae::GameObject>();
		if (m_Rounds[m_CurrentRoundIdx].gameMode == 1)
		{
			Qbert1->AddComponent<dae::Qbert>(m_pLevelPyramid, 21, 6, false);
			qberts.push_back(Qbert1);
		}
		else
		{

			Qbert1->AddComponent<dae::Qbert>(m_pLevelPyramid, 0, 0, false);
			qberts.push_back(Qbert1);

		}



		dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_D, InputType::DownThisFrame, MoveDownRightCommand(Qbert1));
		dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_W, InputType::DownThisFrame, MoveUpRightCommand(Qbert1));
		dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_A, InputType::DownThisFrame, MoveUpLeftCommand(Qbert1));
		dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_S, InputType::DownThisFrame, MoveDownLeftCommand(Qbert1));

		Qbert1->GetComponent<dae::Qbert>()->SetFrozen(true);

		if (m_Rounds[m_CurrentRoundIdx].gameMode == 1)
		{
			auto Qbert2 = std::make_shared<dae::GameObject>();
			Qbert2->AddComponent<dae::Qbert>(m_pLevelPyramid, 27, 6, true);
			qberts.push_back(Qbert2);


			dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_L, InputType::DownThisFrame, MoveDownRightCommand(Qbert2));
			dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_K, InputType::DownThisFrame, MoveDownLeftCommand(Qbert2));
			dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_J, InputType::DownThisFrame, MoveUpLeftCommand(Qbert2));
			dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_I, InputType::DownThisFrame, MoveUpRightCommand(Qbert2));
			Qbert2->GetComponent<dae::Qbert>()->SetFrozen(true);


		}

		for (const auto& qbert : qberts)
		{
			scene->Add(qbert);
		}

		std::vector<std::shared_ptr<dae::GameObject>> UI = MakeUI();

		for (const auto& ui : UI)
		{
			scene->Add(ui);
		}

		auto Disk = std::make_shared<dae::GameObject>();
		m_pDisk = Disk->AddComponent<dae::Disk>(qberts, m_pLevelPyramid, 4, true, m_Rounds[m_CurrentRoundIdx].colorIdx);

		scene->Add(Disk);

		auto Disk2 = std::make_shared<dae::GameObject>();
		m_pDisk2 = Disk2->AddComponent<dae::Disk>(qberts, m_pLevelPyramid, 5, false, m_Rounds[m_CurrentRoundIdx].colorIdx);

		scene->Add(Disk2);



		auto levelManager = std::make_shared<dae::GameObject>();
		m_pLevelManager = levelManager->AddComponent<dae::LevelManager>(m_pLevelPyramid, qberts,shared_from_this());
		levelManager->GetComponent<dae::LevelManager>()->InitializeRound(m_Rounds[m_CurrentRoundIdx].level, m_Rounds[m_CurrentRoundIdx].roundNumber, m_Rounds[m_CurrentRoundIdx].spawnSlickSams, m_Rounds[m_CurrentRoundIdx].spawnUggWrongs, m_Rounds[m_CurrentRoundIdx].slickSamsSpawnInterval, m_Rounds[m_CurrentRoundIdx].uggWrongSpawnInterval, m_Rounds[m_CurrentRoundIdx].gameMode);


		scene->Add(levelManager);
    }

	void RoundManager::SetCurrentRound(int roundIdx)
	{
			m_CurrentRoundIdx = roundIdx;
	}

	void RoundManager::ClearRounds()
	{
		m_Rounds.clear();
		m_CurrentRoundIdx = 0;
		m_CurrentLevelIdx = 0;
	}








};