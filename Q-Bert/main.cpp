#if _DEBUG
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "Minigin.h"
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

#include <fstream>
#include <sstream>

// MiguelCPereiras code but with textfiles instead of binary files
struct Round {
	int roundNumber;
	int level;
	int colorIdx;
	bool spawnSlickSams;
	bool spawnUggWrongs;
	float slickSamsSpawnInterval;
	float uggWrongSpawnInterval;
	int gameMode;
};


void LoadStartScreen()
{
	constexpr int width = 640;
	//constexpr int height = 480;
	constexpr int halfWidth = width / 2;
	//constexpr int halfHeight = height / 2;
	
	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto mainTextFont = resourceManager.LoadFont("Minecraft.ttf", 36);

	
	auto& scene = dae::SceneManager::GetInstance().CreateScene("StartScreen");
	auto startScreen = std::make_shared<dae::GameObject>();
	startScreen->GetTransform()->SetLocalPosition(glm::vec2{ 0,0 });

	auto SoloButton = std::make_shared<dae::GameObject>();
	SoloButton->GetTransform()->SetLocalPosition(glm::vec2{ halfWidth-36,200 });
	SoloButton->AddComponent<dae::TextComponent>("Solo", mainTextFont);
	scene.Add(SoloButton);

	auto VersuzButton = std::make_shared<dae::GameObject>();
	VersuzButton->GetTransform()->SetLocalPosition(glm::vec2{ halfWidth-36,300 });
	VersuzButton->AddComponent<dae::TextComponent>("Versuz", mainTextFont);
	scene.Add(VersuzButton);
	
	auto CoopButton = std::make_shared<dae::GameObject>();
	CoopButton->GetTransform()->SetLocalPosition(glm::vec2{ halfWidth-36,250 });
	CoopButton->AddComponent<dae::TextComponent>("Coop", mainTextFont);
	scene.Add(CoopButton);

	dae::TextureComponent::SpriteInfo spriteInfo{};
	spriteInfo.width = 350;
	spriteInfo.height = 150;
	spriteInfo.SrcX = 0;
	spriteInfo.SrcY = 0;
	spriteInfo.SrcWidth = 474;
	spriteInfo.SrcHeight = 150;

	auto Logo = std::make_shared<dae::GameObject>();
	Logo->GetTransform()->SetLocalPosition(glm::vec2{ halfWidth - 175,15 });
	Logo->AddComponent<dae::TextureComponent>("GameTitle.png", spriteInfo);
	scene.Add(Logo);

	dae::TextureComponent::SpriteInfo spriteInfoSelectArrow{};
	spriteInfoSelectArrow.width = 32;
	spriteInfoSelectArrow.height = 32;
	spriteInfoSelectArrow.SrcX = 0;
	spriteInfoSelectArrow.SrcY = 0;
	spriteInfoSelectArrow.SrcWidth = 6;
	spriteInfoSelectArrow.SrcHeight = 9;


	auto selectionArrow = std::make_shared<dae::GameObject>();
	selectionArrow->GetTransform()->SetLocalPosition(glm::vec2{ halfWidth - 70,200 });
	selectionArrow->AddComponent<dae::TextureComponent>("SelectionArrow.png", spriteInfoSelectArrow);
	scene.Add(selectionArrow);

	auto startScreenSelection = std::make_shared<dae::GameObject>();
	startScreenSelection->AddComponent<dae::StartScreenSelection>(selectionArrow.get(), 50.f);
	scene.Add(startScreenSelection);

	dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_S, InputType::DownThisFrame, StartScreenMoveDown(startScreenSelection));
	dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_W, InputType::DownThisFrame, StartScreenMoveUp(startScreenSelection));
	dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_SPACE, InputType::DownThisFrame, StartScreenSelect(startScreenSelection));

	scene.Add(startScreen);
}

void SoloLevel1()
{

	std::ofstream levelOne("Level01Solo.txt");

	if (!levelOne) {
		std::cout << "Level 01 Solo file couldn't be created\n";
		return;
	}


	Round rounds[3]{};

	rounds[0].roundNumber = 1;
	rounds[0].level = 1;
	rounds[0].colorIdx = 0;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = true;
	rounds[0].slickSamsSpawnInterval= 11.f;
	rounds[0].uggWrongSpawnInterval = 5.f;
	rounds[0].gameMode = 0;

	rounds[1].roundNumber = 2;
	rounds[1].level = 1;
	rounds[1].colorIdx = 1;
	rounds[1].spawnSlickSams = false;
	rounds[1].spawnUggWrongs = false;
	rounds[1].slickSamsSpawnInterval= 0;
	rounds[1].uggWrongSpawnInterval = 0;
	rounds[1].gameMode = 0;

	rounds[2].roundNumber = 3;
	rounds[2].level = 1;
	rounds[2].colorIdx = 2;
	rounds[2].spawnSlickSams = false;
	rounds[2].spawnUggWrongs = false;
	rounds[2].slickSamsSpawnInterval = 0;
	rounds[2].uggWrongSpawnInterval = 0;
	rounds[2].gameMode = 0;




	for (int i = 0; i < 3; ++i) {
		levelOne << "Round " << rounds[i].roundNumber << "\n"
			<< "Level " << rounds[i].level << "\n"
			<< "ColorIdx " << rounds[i].colorIdx << "\n"
			<< "SpawnSlickSams " << rounds[i].spawnSlickSams << "\n"
			<< "SpawnUggWrongs " << rounds[i].spawnUggWrongs << "\n"
			<< "SlickSamsSpawnInterval " << rounds[i].slickSamsSpawnInterval << "\n"
			<< "UggWrongSpawnInterval " << rounds[i].uggWrongSpawnInterval << "\n"
			<< "GameMode " << rounds[i].gameMode << "\n\n";
	}

	levelOne.close();

	if (!levelOne.good()) {
		std::cout << "Level 01 Solo file wasn't properly written\n";
	}
}
void SoloLevel2()
{

	std::ofstream levelOne("Level02Solo.txt");

	if (!levelOne) {
		std::cout << "Level 01 Solo file couldn't be created\n";
		return;
	}


	Round rounds[3]{};

	rounds[0].roundNumber = 1;
	rounds[0].level = 2;
	rounds[0].colorIdx = 3;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = true;
	rounds[0].slickSamsSpawnInterval = 11.f;
	rounds[0].uggWrongSpawnInterval = 5.f;
	rounds[0].gameMode = 0;

	rounds[1].roundNumber = 2;
	rounds[1].level = 2;
	rounds[1].colorIdx = 4;
	rounds[1].spawnSlickSams = false;
	rounds[1].spawnUggWrongs = false;
	rounds[1].slickSamsSpawnInterval = 0;
	rounds[1].uggWrongSpawnInterval = 0;
	rounds[1].gameMode = 0;

	rounds[2].roundNumber = 3;
	rounds[2].level = 2;
	rounds[2].colorIdx = 5;
	rounds[2].spawnSlickSams = false;
	rounds[2].spawnUggWrongs = false;
	rounds[2].slickSamsSpawnInterval = 0;
	rounds[2].uggWrongSpawnInterval = 0;
	rounds[2].gameMode = 0;


	for (int i = 0; i < 3; ++i) {
		levelOne << "Round " << rounds[i].roundNumber << "\n"
			<< "Level " << rounds[i].level << "\n"
			<< "ColorIdx " << rounds[i].colorIdx << "\n"
			<< "SpawnSlickSams " << rounds[i].spawnSlickSams << "\n"
			<< "SpawnUggWrongs " << rounds[i].spawnUggWrongs << "\n"
			<< "SlickSamsSpawnInterval " << rounds[i].slickSamsSpawnInterval << "\n"
			<< "UggWrongSpawnInterval " << rounds[i].uggWrongSpawnInterval << "\n"
			<< "GameMode " << rounds[i].gameMode << "\n\n";
	}

	levelOne.close();

	if (!levelOne.good()) {
		std::cout << "Level 01 Solo file wasn't properly written\n";
	}
}
void VersuzLevel1()
{

	std::ofstream levelOne("Level01Versuz.txt");

	if (!levelOne) {
		std::cout << "Level 01 Solo file couldn't be created\n";
		return;
	}


	Round rounds[3]{};

	rounds[0].roundNumber = 1;
	rounds[0].level = 1;
	rounds[0].colorIdx = 0;
	rounds[0].spawnSlickSams = false;
	rounds[0].spawnUggWrongs = false;
	rounds[0].slickSamsSpawnInterval = 0.f;
	rounds[0].uggWrongSpawnInterval = 0.f;
	rounds[0].gameMode = 3;

	rounds[1].roundNumber = 2;
	rounds[1].level = 1;
	rounds[1].colorIdx = 1;
	rounds[1].spawnSlickSams = false;
	rounds[1].spawnUggWrongs = false;
	rounds[1].slickSamsSpawnInterval = 0;
	rounds[1].uggWrongSpawnInterval = 0;
	rounds[1].gameMode = 3;

	rounds[2].roundNumber = 3;
	rounds[2].level = 1;
	rounds[2].colorIdx = 2;
	rounds[2].spawnSlickSams = false;
	rounds[2].spawnUggWrongs = false;
	rounds[2].slickSamsSpawnInterval = 0;
	rounds[2].uggWrongSpawnInterval = 0;
	rounds[2].gameMode = 3;




	for (int i = 0; i < 3; ++i) {
		levelOne << "Round " << rounds[i].roundNumber << "\n"
			<< "Level " << rounds[i].level << "\n"
			<< "ColorIdx " << rounds[i].colorIdx << "\n"
			<< "SpawnSlickSams " << rounds[i].spawnSlickSams << "\n"
			<< "SpawnUggWrongs " << rounds[i].spawnUggWrongs << "\n"
			<< "SlickSamsSpawnInterval " << rounds[i].slickSamsSpawnInterval << "\n"
			<< "UggWrongSpawnInterval " << rounds[i].uggWrongSpawnInterval << "\n"
			<< "GameMode " << rounds[i].gameMode << "\n\n";
	}

	levelOne.close();

	if (!levelOne.good()) {
		std::cout << "Level 01 Solo file wasn't properly written\n";
	}
}


void LoadTextRound(const std::string& filePath) {
	std::ifstream levelFile(filePath);

	if (!levelFile) {
		std::cout << "Level file couldn't be opened\n";
		return;
	}


	std::vector<Round> rounds;
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
			rounds.push_back(round);
		}
	}

	levelFile.close();


	for (auto& round : rounds)
	{
		std::string scenename = "Level10";
		scenename += std::to_string(round.level);
		scenename += "-";
		scenename += std::to_string(round.roundNumber);

		auto& scene = dae::SceneManager::GetInstance().CreateScene(scenename);

		auto level = std::make_shared<dae::GameObject>();
		level->GetTransform()->SetLocalPosition(glm::vec2{ 0,0 });

		dae::LevelPyramid::PyramidSettings settings{};
		settings.StartPos = glm::vec2{ 300,70 };
		settings.Rows = 7;
		settings.CubeSize = glm::vec2{ 62, 64 };
		settings.Level = round.level;
		settings.ColorIndex = round.colorIdx;
		settings.SpriteSize = glm::vec2{ 32, 32 };

		auto pyramid = level->AddComponent<dae::LevelPyramid>(settings);

		for (const auto& cube : pyramid->GetCubes())
		{
			scene.Add(cube);
		}

		scene.Add(level);


		std::vector<std::shared_ptr<dae::GameObject>> qberts;
		auto Qbert1 = std::make_shared<dae::GameObject>();

		
		if (round.gameMode == 1)
		{
			Qbert1->AddComponent<dae::Qbert>(pyramid,21,6 ,false);
			qberts.push_back(Qbert1);
		}
		else
		{
			
				Qbert1->AddComponent<dae::Qbert>(pyramid, 0, 0, false);
				qberts.push_back(Qbert1);

		}

		dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_D, InputType::DownThisFrame, MoveDownRightCommand(Qbert1));
		dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_S, InputType::DownThisFrame, MoveDownLeftCommand(Qbert1));
		dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_A, InputType::DownThisFrame, MoveUpLeftCommand(Qbert1));
		dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_W, InputType::DownThisFrame, MoveUpRightCommand(Qbert1));

		if (round.gameMode == 1)
		{
			auto Qbert2 = std::make_shared<dae::GameObject>();
			Qbert2->AddComponent<dae::Qbert>(pyramid,27,6,true);
			qberts.push_back(Qbert2);

			dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_L, InputType::DownThisFrame, MoveDownRightCommand(Qbert2));
			dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_K, InputType::DownThisFrame, MoveDownLeftCommand(Qbert2));
			dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_J, InputType::DownThisFrame, MoveUpLeftCommand(Qbert2));
			dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_I, InputType::DownThisFrame, MoveUpRightCommand(Qbert2));


		}

		for (const auto& qbert : qberts)
		{
			scene.Add(qbert);
		}

		auto Disk = std::make_shared<dae::GameObject>();
		Disk->AddComponent<dae::Disk>(qberts, pyramid, 4, true, round.colorIdx);

		scene.Add(Disk);

		auto Disk2 = std::make_shared<dae::GameObject>();
		Disk2->AddComponent<dae::Disk>(qberts, pyramid, 6, false, round.colorIdx);

		scene.Add(Disk2);

	

		auto levelManager = std::make_shared<dae::GameObject>();
		levelManager->AddComponent<dae::LevelManager>(pyramid, qberts);
		levelManager->GetComponent<dae::LevelManager>()->InitializeRound(round.level,round.roundNumber,round.spawnSlickSams, round.spawnUggWrongs, round.slickSamsSpawnInterval, round.uggWrongSpawnInterval, round.gameMode);


		scene.Add(levelManager);
	}



}


void load()
{
	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto mainTextFont = resourceManager.LoadFont("Minecraft.ttf", 36);


	std::unique_ptr<dae::SoundService> soundSystem = std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>());
	dae::ServiceLocator::RegisterSoundSystem(std::move(soundSystem));

	//SoloLevel2();

	//LoadTextRound("Level01Solo.txt");
	//LoadTextRound("Level02Solo.txt");
	LoadStartScreen();
	LoadTextRound("Level01Solo.txt");
	LoadTextRound("Level01CoOp.txt");
	LoadTextRound("Level01Versuz.txt");


	
}

int main(int, char* []) {
	dae::Minigin engine{"../Data/"};
	engine.Run(load);
	return 0;
}