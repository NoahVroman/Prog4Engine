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
#include "ScoreAndLivesManager.h"
#include "RoundManager.h"

#include <fstream>
#include <sstream>

// MiguelCPereiras code but with textfiles instead of binary files
//struct Round {
//	int roundNumber;
//	int level;
//	int colorIdx;
//	bool spawnSlickSams;
//	bool spawnUggWrongs;
//	float slickSamsSpawnInterval;
//	float uggWrongSpawnInterval;
//	int gameMode;
//};


void LoadStartScreen(std::shared_ptr<dae::RoundManager> roundManager)
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
	dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_RETURN, InputType::DownThisFrame, StartScreenSelect(startScreenSelection,roundManager));

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
void SoloLevel3()
{

	std::ofstream levelOne("Level03Solo.txt");

	if (!levelOne) {
		std::cout << "Level 01 Solo file couldn't be created\n";
		return;
	}


	Round rounds[3]{};

	rounds[0].roundNumber = 1;
	rounds[0].level = 3;
	rounds[0].colorIdx = 3;
	rounds[0].spawnSlickSams = false;
	rounds[0].spawnUggWrongs = false;
	rounds[0].slickSamsSpawnInterval = 11.f;
	rounds[0].uggWrongSpawnInterval = 5.f;
	rounds[0].gameMode = 0;

	rounds[1].roundNumber = 2;
	rounds[1].level = 3;
	rounds[1].colorIdx = 4;
	rounds[1].spawnSlickSams = false;
	rounds[1].spawnUggWrongs = false;
	rounds[1].slickSamsSpawnInterval = 0;
	rounds[1].uggWrongSpawnInterval = 0;
	rounds[1].gameMode = 0;

	rounds[2].roundNumber = 3;
	rounds[2].level = 3;
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



void load()
{
	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto mainTextFont = resourceManager.LoadFont("Minecraft.ttf", 36);
    auto roundManager{std::make_shared<dae::RoundManager>()};

	std::unique_ptr<dae::SoundService> soundSystem = std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>());
	dae::ServiceLocator::RegisterSoundSystem(std::move(soundSystem));
	LoadStartScreen(roundManager);
	roundManager->LoadRoundData("Level01Solo.txt", "SoloLevel1");
	roundManager->LoadRoundData("Level02Solo.txt", "SoloLevel2");
	roundManager->LoadRoundData("Level03Solo.txt", "SoloLevel3");






	
}

int main(int, char* []) {
	dae::Minigin engine{"../Data/"};
	engine.Run(load);
	return 0;
}