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

// Based on MiguelCPereiras code but with textfiles instead of binary files and some extra and diffrent stuff
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

	if (dae::SceneManager::GetInstance().GetCurrentSceneIndex() == 0)
	{
		dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_S, InputType::DownThisFrame, StartScreenMoveDown(startScreenSelection));
		dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_W, InputType::DownThisFrame, StartScreenMoveUp(startScreenSelection));
		dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_SPACE, InputType::DownThisFrame, StartScreenSelect(startScreenSelection));

		dae::InputManager::GetInstance().BindGamePadAction(0, XINPUT_GAMEPAD_DPAD_DOWN, InputType::DownThisFrame, StartScreenMoveDown(startScreenSelection));
		dae::InputManager::GetInstance().BindGamePadAction(0, XINPUT_GAMEPAD_DPAD_UP, InputType::DownThisFrame, StartScreenMoveUp(startScreenSelection));
		dae::InputManager::GetInstance().BindGamePadAction(0, XINPUT_GAMEPAD_START, InputType::DownThisFrame, StartScreenSelect(startScreenSelection));

	}


	scene.Add(startScreen);
}

void LoadGameOverScreen() 
{

	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto mainTextFont = resourceManager.LoadFont("Minecraft.ttf", 36);

	auto& scene = dae::SceneManager::GetInstance().CreateScene("GameOverScreen");

	auto gameOverScreen = std::make_shared<dae::GameObject>();
	gameOverScreen->GetTransform()->SetLocalPosition(glm::vec2{ 0,0 });

	auto gameOverText = std::make_shared<dae::GameObject>();
	gameOverText->GetTransform()->SetLocalPosition(glm::vec2{ 200,200 });
	gameOverText->AddComponent<dae::TextComponent>("Game Over", mainTextFont);
	scene.Add(gameOverText);

	auto restartText = std::make_shared<dae::GameObject>();
	restartText->GetTransform()->SetLocalPosition(glm::vec2{ 200,250 });
	restartText->AddComponent<dae::TextComponent>("Press R to restart", mainTextFont);
	scene.Add(restartText);


	dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_R, InputType::DownThisFrame, BackToMenu(nullptr));
	dae::InputManager::GetInstance().BindGamePadAction(0, XINPUT_GAMEPAD_START, InputType::DownThisFrame, BackToMenu(nullptr));



}

void LoadVictoryScreen()
{

	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto mainTextFont = resourceManager.LoadFont("Minecraft.ttf", 36);

	auto& scene = dae::SceneManager::GetInstance().CreateScene("VictoryScreen");

	auto victoryScreen = std::make_shared<dae::GameObject>();
	victoryScreen->GetTransform()->SetLocalPosition(glm::vec2{ 0,0 });

	auto victoryText = std::make_shared<dae::GameObject>();
	victoryText->GetTransform()->SetLocalPosition(glm::vec2{ 200,200 });
	victoryText->AddComponent<dae::TextComponent>("Victory", mainTextFont);
	scene.Add(victoryText);

	auto restartText = std::make_shared<dae::GameObject>();
	restartText->GetTransform()->SetLocalPosition(glm::vec2{ 200,250 });
	restartText->AddComponent<dae::TextComponent>("Press R to restart", mainTextFont);
	scene.Add(restartText);

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
	rounds[0].spawnSlickSams = false;
	rounds[0].spawnUggWrongs = false;
	rounds[0].slickSamsSpawnInterval = 15.f; // Increased spawn interval
	rounds[0].uggWrongSpawnInterval = 8.f; // Increased spawn interval
	rounds[0].gameMode = 0;

	// Adjust parameters for the second round to make it easier
	rounds[1].roundNumber = 2;
	rounds[1].level = 1;
	rounds[1].colorIdx = 1;
	rounds[1].spawnSlickSams = false; // Disable Slick Sams spawning
	rounds[1].spawnUggWrongs = false; // Enable Ugg Wrongs spawning
	rounds[1].slickSamsSpawnInterval = 0; // No Slick Sams spawning
	rounds[1].uggWrongSpawnInterval = 15.f; // Decrease Ugg Wrongs spawn interval
	rounds[1].gameMode = 0;

	// Adjust parameters for the third round to make it easier
	rounds[2].roundNumber = 3;
	rounds[2].level = 1;
	rounds[2].colorIdx = 2;
	rounds[2].spawnSlickSams = false; // Disable Slick Sams spawning
	rounds[2].spawnUggWrongs = true; // Disable Ugg Wrongs spawning
	rounds[2].slickSamsSpawnInterval = 0; // No Slick Sams spawning
	rounds[2].uggWrongSpawnInterval = 10.f; // No Ugg Wrongs spawning
	rounds[2].gameMode = 0;

	// Writing the rounds to the file
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
	std::ofstream levelTwo("Level02Solo.txt");

	if (!levelTwo) {
		std::cout << "Level 02 Solo file couldn't be created\n";
		return;
	}

	Round rounds[3]{};

	rounds[0].roundNumber = 1;
	rounds[0].level = 2;
	rounds[0].colorIdx = 3;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = true;
	rounds[0].slickSamsSpawnInterval = 15.f;
	rounds[0].uggWrongSpawnInterval = 10.f;
	rounds[0].gameMode = 0;

	// Adjust parameters for the second round to make it harder
	rounds[1].roundNumber = 2;
	rounds[1].level = 2;
	rounds[1].colorIdx = 4;
	rounds[1].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[1].spawnUggWrongs = false; // Disable Ugg Wrongs spawning
	rounds[1].slickSamsSpawnInterval = 14.f; // Decrease Slick Sams spawn interval
	rounds[1].uggWrongSpawnInterval = 0; // No Ugg Wrongs spawning
	rounds[1].gameMode = 0;

	// Adjust parameters for the third round to make it harder
	rounds[2].roundNumber = 3;
	rounds[2].level = 2;
	rounds[2].colorIdx = 5;
	rounds[2].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[2].spawnUggWrongs = true; // Enable Ugg Wrongs spawning
	rounds[2].slickSamsSpawnInterval = 13.f; // Further decrease Slick Sams spawn interval
	rounds[2].uggWrongSpawnInterval = 10.f; // Further decrease Ugg Wrongs spawn interval
	rounds[2].gameMode = 0;

	// Writing the rounds to the file
	for (int i = 0; i < 3; ++i) {
		levelTwo << "Round " << rounds[i].roundNumber << "\n"
			<< "Level " << rounds[i].level << "\n"
			<< "ColorIdx " << rounds[i].colorIdx << "\n"
			<< "SpawnSlickSams " << rounds[i].spawnSlickSams << "\n"
			<< "SpawnUggWrongs " << rounds[i].spawnUggWrongs << "\n"
			<< "SlickSamsSpawnInterval " << rounds[i].slickSamsSpawnInterval << "\n"
			<< "UggWrongSpawnInterval " << rounds[i].uggWrongSpawnInterval << "\n"
			<< "GameMode " << rounds[i].gameMode << "\n\n";
	}

	levelTwo.close();

	if (!levelTwo.good()) {
		std::cout << "Level 02 Solo file wasn't properly written\n";
	}
}
void SoloLevel3()
{
	std::ofstream levelThree("Level03Solo.txt");

	if (!levelThree) {
		std::cout << "Level 03 Solo file couldn't be created\n";
		return;
	}

	Round rounds[3]{};

	rounds[0].roundNumber = 1;
	rounds[0].level = 3;
	rounds[0].colorIdx = 1;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = true;
	rounds[0].slickSamsSpawnInterval = 15.f; // Increased spawn interval
	rounds[0].uggWrongSpawnInterval = 10.f; // Increased spawn interval
	rounds[0].gameMode = 0;

	// Adjust parameters for the second round to make it harder
	rounds[1].roundNumber = 2;
	rounds[1].level = 3;
	rounds[1].colorIdx = 2;
	rounds[1].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[1].spawnUggWrongs = true; // Enable Ugg Wrongs spawning
	rounds[1].slickSamsSpawnInterval = 12.f; // Further decrease Slick Sams spawn interval
	rounds[1].uggWrongSpawnInterval = 10.f; // Further decrease Ugg Wrongs spawn interval
	rounds[1].gameMode = 0;

	// Adjust parameters for the third round to make it harder
	rounds[2].roundNumber = 3;
	rounds[2].level = 3;
	rounds[2].colorIdx = 3;
	rounds[2].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[2].spawnUggWrongs = true; // Enable Ugg Wrongs spawning
	rounds[2].slickSamsSpawnInterval = 10.f; // Further decrease Slick Sams spawn interval
	rounds[2].uggWrongSpawnInterval = 9.f; // Further decrease Ugg Wrongs spawn interval
	rounds[2].gameMode = 0;

	// Writing the rounds to the file
	for (int i = 0; i < 3; ++i) {
		levelThree << "Round " << rounds[i].roundNumber << "\n"
			<< "Level " << rounds[i].level << "\n"
			<< "ColorIdx " << rounds[i].colorIdx << "\n"
			<< "SpawnSlickSams " << rounds[i].spawnSlickSams << "\n"
			<< "SpawnUggWrongs " << rounds[i].spawnUggWrongs << "\n"
			<< "SlickSamsSpawnInterval " << rounds[i].slickSamsSpawnInterval << "\n"
			<< "UggWrongSpawnInterval " << rounds[i].uggWrongSpawnInterval << "\n"
			<< "GameMode " << rounds[i].gameMode << "\n\n";
	}

	levelThree.close();

	if (!levelThree.good()) {
		std::cout << "Level 03 Solo file wasn't properly written\n";
	}
}

void CoOpLevel1()
{
	std::ofstream levelOne("CoOpLevel01.txt");

	if (!levelOne) {
		std::cout << "CoOp Level 01 file couldn't be created\n";
		return;
	}

	Round rounds[3]{};

	rounds[0].roundNumber = 1;
	rounds[0].level = 1;
	rounds[0].colorIdx = 0;
	rounds[0].spawnSlickSams = false;
	rounds[0].spawnUggWrongs = false;
	rounds[0].slickSamsSpawnInterval = 15.f; // Increased spawn interval
	rounds[0].uggWrongSpawnInterval = 8.f; // Increased spawn interval
	rounds[0].gameMode = 1; // Co-Op mode

	// Adjust parameters for the second round to make it easier
	rounds[1].roundNumber = 2;
	rounds[1].level = 1;
	rounds[1].colorIdx = 1;
	rounds[1].spawnSlickSams = false; // Disable Slick Sams spawning
	rounds[1].spawnUggWrongs = false; // Enable Ugg Wrongs spawning
	rounds[1].slickSamsSpawnInterval = 0; // No Slick Sams spawning
	rounds[1].uggWrongSpawnInterval = 15.f; // Decrease Ugg Wrongs spawn interval
	rounds[1].gameMode = 1; // Co-Op mode

	// Adjust parameters for the third round to make it easier
	rounds[2].roundNumber = 3;
	rounds[2].level = 1;
	rounds[2].colorIdx = 2;
	rounds[2].spawnSlickSams = false; // Disable Slick Sams spawning
	rounds[2].spawnUggWrongs = true; // Disable Ugg Wrongs spawning
	rounds[2].slickSamsSpawnInterval = 0; // No Slick Sams spawning
	rounds[2].uggWrongSpawnInterval = 10.f; // No Ugg Wrongs spawning
	rounds[2].gameMode = 1; // Co-Op mode

	// Writing the rounds to the file
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
		std::cout << "CoOp Level 01 file wasn't properly written\n";
	}
}
void CoOpLevel2()
{
	std::ofstream levelTwo("CoOpLevel02.txt");

	if (!levelTwo) {
		std::cout << "CoOp Level 02 file couldn't be created\n";
		return;
	}

	Round rounds[3]{};

	rounds[0].roundNumber = 1;
	rounds[0].level = 2;
	rounds[0].colorIdx = 3;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = true;
	rounds[0].slickSamsSpawnInterval = 15.f;
	rounds[0].uggWrongSpawnInterval = 10.f;
	rounds[0].gameMode = 1; // Co-Op mode

	// Adjust parameters for the second round to make it harder
	rounds[1].roundNumber = 2;
	rounds[1].level = 2;
	rounds[1].colorIdx = 4;
	rounds[1].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[1].spawnUggWrongs = false; // Disable Ugg Wrongs spawning
	rounds[1].slickSamsSpawnInterval = 14.f; // Decrease Slick Sams spawn interval
	rounds[1].uggWrongSpawnInterval = 0; // No Ugg Wrongs spawning
	rounds[1].gameMode = 1; // Co-Op mode

	// Adjust parameters for the third round to make it harder
	rounds[2].roundNumber = 3;
	rounds[2].level = 2;
	rounds[2].colorIdx = 5;
	rounds[2].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[2].spawnUggWrongs = true; // Enable Ugg Wrongs spawning
	rounds[2].slickSamsSpawnInterval = 13.f; // Further decrease Slick Sams spawn interval
	rounds[2].uggWrongSpawnInterval = 10.f; // Further decrease Ugg Wrongs spawn interval
	rounds[2].gameMode = 1; // Co-Op mode

	// Writing the rounds to the file
	for (int i = 0; i < 3; ++i) {
		levelTwo << "Round " << rounds[i].roundNumber << "\n"
			<< "Level " << rounds[i].level << "\n"
			<< "ColorIdx " << rounds[i].colorIdx << "\n"
			<< "SpawnSlickSams " << rounds[i].spawnSlickSams << "\n"
			<< "SpawnUggWrongs " << rounds[i].spawnUggWrongs << "\n"
			<< "SlickSamsSpawnInterval " << rounds[i].slickSamsSpawnInterval << "\n"
			<< "UggWrongSpawnInterval " << rounds[i].uggWrongSpawnInterval << "\n"
			<< "GameMode " << rounds[i].gameMode << "\n\n";
	}

	levelTwo.close();

	if (!levelTwo.good()) {
		std::cout << "CoOp Level 02 file wasn't properly written\n";
	}
}
void CoOpLevel3()
{
	std::ofstream levelThree("CoOpLevel03.txt");

	if (!levelThree) {
		std::cout << "CoOp Level 03 file couldn't be created\n";
		return;
	}

	Round rounds[3]{};

	rounds[0].roundNumber = 1;
	rounds[0].level = 3;
	rounds[0].colorIdx = 1;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = true;
	rounds[0].slickSamsSpawnInterval = 15.f; // Increased spawn interval
	rounds[0].uggWrongSpawnInterval = 10.f; // Increased spawn interval
	rounds[0].gameMode = 1; // Co-Op mode

	// Adjust parameters for the second round to make it harder
	rounds[1].roundNumber = 2;
	rounds[1].level = 3;
	rounds[1].colorIdx = 2;
	rounds[1].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[1].spawnUggWrongs = true; // Enable Ugg Wrongs spawning
	rounds[1].slickSamsSpawnInterval = 12.f; // Further decrease Slick Sams spawn interval
	rounds[1].uggWrongSpawnInterval = 10.f; // Further decrease Ugg Wrongs spawn interval
	rounds[1].gameMode = 1; // Co-Op mode

	// Adjust parameters for the third round to make it harder
	rounds[2].roundNumber = 3;
	rounds[2].level = 3;
	rounds[2].colorIdx = 3;
	rounds[2].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[2].spawnUggWrongs = true; // Enable Ugg Wrongs spawning
	rounds[2].slickSamsSpawnInterval = 10.f; // Further decrease Slick Sams spawn interval
	rounds[2].uggWrongSpawnInterval = 9.f; // Further decrease Ugg Wrongs spawn interval
	rounds[2].gameMode = 1; // Co-Op mode

	// Writing the rounds to the file
	for (int i = 0; i < 3; ++i) {
		levelThree << "Round " << rounds[i].roundNumber << "\n"
			<< "Level " << rounds[i].level << "\n"
			<< "ColorIdx " << rounds[i].colorIdx << "\n"
			<< "SpawnSlickSams " << rounds[i].spawnSlickSams << "\n"
			<< "SpawnUggWrongs " << rounds[i].spawnUggWrongs << "\n"
			<< "SlickSamsSpawnInterval " << rounds[i].slickSamsSpawnInterval << "\n"
			<< "UggWrongSpawnInterval " << rounds[i].uggWrongSpawnInterval << "\n"
			<< "GameMode " << rounds[i].gameMode << "\n\n";
	}

	levelThree.close();

	if (!levelThree.good()) {
		std::cout << "CoOp Level 03 file wasn't properly written\n";
	}
}

void VersusLevel1()
{
	std::ofstream levelOne("Level01Versus.txt");

	if (!levelOne) {
		std::cout << "Level 01 Versus file couldn't be created\n";
		return;
	}

	Round rounds[3]{};

	rounds[0].roundNumber = 1;
	rounds[0].level = 1;
	rounds[0].colorIdx = 0;
	rounds[0].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[0].spawnUggWrongs = false; // Disable Ugg Wrongs spawning
	rounds[0].slickSamsSpawnInterval = 15.f; // Increased spawn interval
	rounds[0].uggWrongSpawnInterval = 0.f; // No Ugg Wrongs spawning
	rounds[0].gameMode = 3; // Versus mode

	// Adjust parameters for the second round to make it harder
	rounds[1].roundNumber = 2;
	rounds[1].level = 1;
	rounds[1].colorIdx = 1;
	rounds[1].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[1].spawnUggWrongs = true; // Enable Ugg Wrongs spawning
	rounds[1].slickSamsSpawnInterval = 14.f; // Decrease Slick Sams spawn interval
	rounds[1].uggWrongSpawnInterval = 10.f; // Set Ugg Wrongs spawn interval
	rounds[1].gameMode = 3; // Versus mode

	// Adjust parameters for the third round to make it harder
	rounds[2].roundNumber = 3;
	rounds[2].level = 1;
	rounds[2].colorIdx = 2;
	rounds[2].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[2].spawnUggWrongs = true; // Enable Ugg Wrongs spawning
	rounds[2].slickSamsSpawnInterval = 12.f; // Further decrease Slick Sams spawn interval
	rounds[2].uggWrongSpawnInterval = 8.f; // Further decrease Ugg Wrongs spawn interval
	rounds[2].gameMode = 3; // Versus mode

	// Writing the rounds to the file
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
		std::cout << "Level 01 Versus file wasn't properly written\n";
	}
}
void VersusLevel2()
{
	std::ofstream levelTwo("Level02Versus.txt");

	if (!levelTwo) {
		std::cout << "Level 02 Versus file couldn't be created\n";
		return;
	}

	Round rounds[3]{};

	rounds[0].roundNumber = 1;
	rounds[0].level = 2;
	rounds[0].colorIdx = 3;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = false;
	rounds[0].slickSamsSpawnInterval = 15.f; // Increased spawn interval
	rounds[0].uggWrongSpawnInterval = 0.f; // No Ugg Wrongs spawning
	rounds[0].gameMode = 3; // Versus mode

	// Adjust parameters for the second round to make it harder
	rounds[1].roundNumber = 2;
	rounds[1].level = 2;
	rounds[1].colorIdx = 4;
	rounds[1].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[1].spawnUggWrongs = true; // Enable Ugg Wrongs spawning
	rounds[1].slickSamsSpawnInterval = 14.f; // Decrease Slick Sams spawn interval
	rounds[1].uggWrongSpawnInterval = 10.f; // Set Ugg Wrongs spawn interval
	rounds[1].gameMode = 3; // Versus mode

	// Adjust parameters for the third round to make it harder
	rounds[2].roundNumber = 3;
	rounds[2].level = 2;
	rounds[2].colorIdx = 5;
	rounds[2].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[2].spawnUggWrongs = true; // Enable Ugg Wrongs spawning
	rounds[2].slickSamsSpawnInterval = 12.f; // Further decrease Slick Sams spawn interval
	rounds[2].uggWrongSpawnInterval = 8.f; // Further decrease Ugg Wrongs spawn interval
	rounds[2].gameMode = 3; // Versus mode

	// Writing the rounds to the file
	for (int i = 0; i < 3; ++i) {
		levelTwo << "Round " << rounds[i].roundNumber << "\n"
			<< "Level " << rounds[i].level << "\n"
			<< "ColorIdx " << rounds[i].colorIdx << "\n"
			<< "SpawnSlickSams " << rounds[i].spawnSlickSams << "\n"
			<< "SpawnUggWrongs " << rounds[i].spawnUggWrongs << "\n"
			<< "SlickSamsSpawnInterval " << rounds[i].slickSamsSpawnInterval << "\n"
			<< "UggWrongSpawnInterval " << rounds[i].uggWrongSpawnInterval << "\n"
			<< "GameMode " << rounds[i].gameMode << "\n\n";
	}

	levelTwo.close();

	if (!levelTwo.good()) {
		std::cout << "Level 02 Versus file wasn't properly written\n";
	}
}
void VersusLevel3()
{
	std::ofstream levelThree("Level03Versus.txt");

	if (!levelThree) {
		std::cout << "Level 03 Versus file couldn't be created\n";
		return;
	}

	Round rounds[3]{};

	rounds[0].roundNumber = 1;
	rounds[0].level = 3;
	rounds[0].colorIdx = 1;
	rounds[0].spawnSlickSams = true;
	rounds[0].spawnUggWrongs = false;
	rounds[0].slickSamsSpawnInterval = 15.f; // Increased spawn interval
	rounds[0].uggWrongSpawnInterval = 0.f; // No Ugg Wrongs spawning
	rounds[0].gameMode = 3; // Versus mode

	// Adjust parameters for the second round to make it harder
	rounds[1].roundNumber = 2;
	rounds[1].level = 3;
	rounds[1].colorIdx = 2;
	rounds[1].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[1].spawnUggWrongs = true; // Enable Ugg Wrongs spawning
	rounds[1].slickSamsSpawnInterval = 14.f; // Decrease Slick Sams spawn interval
	rounds[1].uggWrongSpawnInterval = 10.f; // Set Ugg Wrongs spawn interval
	rounds[1].gameMode = 3; // Versus mode

	// Adjust parameters for the third round to make it harder
	rounds[2].roundNumber = 3;
	rounds[2].level = 3;
	rounds[2].colorIdx = 3;
	rounds[2].spawnSlickSams = true; // Enable Slick Sams spawning
	rounds[2].spawnUggWrongs = true; // Enable Ugg Wrongs spawning
	rounds[2].slickSamsSpawnInterval = 12.f; // Further decrease Slick Sams spawn interval
	rounds[2].uggWrongSpawnInterval = 8.f; // Further decrease Ugg Wrongs spawn interval
	rounds[2].gameMode = 3; // Versus mode

	// Writing the rounds to the file
	for (int i = 0; i < 3; ++i) {
		levelThree << "Round " << rounds[i].roundNumber << "\n"
			<< "Level " << rounds[i].level << "\n"
			<< "ColorIdx " << rounds[i].colorIdx << "\n"
			<< "SpawnSlickSams " << rounds[i].spawnSlickSams << "\n"
			<< "SpawnUggWrongs " << rounds[i].spawnUggWrongs << "\n"
			<< "SlickSamsSpawnInterval " << rounds[i].slickSamsSpawnInterval << "\n"
			<< "UggWrongSpawnInterval " << rounds[i].uggWrongSpawnInterval << "\n"
			<< "GameMode " << rounds[i].gameMode << "\n\n";
	}

	levelThree.close();

	if (!levelThree.good()) {
		std::cout << "Level 03 Versus file wasn't properly written\n";
	}
}


std::vector<std::shared_ptr<dae::GameObject>> MakeUI(int roundnumber,int Level)
{
	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto mainTextFont = resourceManager.LoadFont("Minecraft.ttf", 20);

	std::vector<std::shared_ptr<dae::GameObject>> UI;

	std::string roundStr = "Round: " + std::to_string(roundnumber);
	std::string levelStr = "Level: " + std::to_string(Level);



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

		dae::InputManager::GetInstance().BindGamePadAction(0, XINPUT_GAMEPAD_DPAD_RIGHT ,InputType::DownThisFrame, MoveUpRightCommand(Qbert1));
		dae::InputManager::GetInstance().BindGamePadAction(0, XINPUT_GAMEPAD_DPAD_LEFT, InputType::DownThisFrame, MoveUpLeftCommand(Qbert1));
		dae::InputManager::GetInstance().BindGamePadAction(0, XINPUT_GAMEPAD_DPAD_DOWN, InputType::DownThisFrame, MoveDownLeftCommand(Qbert1));
		dae::InputManager::GetInstance().BindGamePadAction(0, XINPUT_GAMEPAD_DPAD_UP, InputType::DownThisFrame, MoveUpRightCommand(Qbert1));

		if (round.gameMode == 1)
		{
			auto Qbert2 = std::make_shared<dae::GameObject>();
			Qbert2->AddComponent<dae::Qbert>(pyramid,27,6,true);
			qberts.push_back(Qbert2);

			dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_L, InputType::DownThisFrame, MoveDownRightCommand(Qbert2));
			dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_K, InputType::DownThisFrame, MoveDownLeftCommand(Qbert2));
			dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_J, InputType::DownThisFrame, MoveUpLeftCommand(Qbert2));
			dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_I, InputType::DownThisFrame, MoveUpRightCommand(Qbert2));



			dae::InputManager::GetInstance().BindGamePadAction(1, XINPUT_GAMEPAD_DPAD_RIGHT, InputType::DownThisFrame, MoveUpRightCommand(Qbert2));
			dae::InputManager::GetInstance().BindGamePadAction(1, XINPUT_GAMEPAD_DPAD_LEFT, InputType::DownThisFrame, MoveUpLeftCommand(Qbert2));
			dae::InputManager::GetInstance().BindGamePadAction(1, XINPUT_GAMEPAD_DPAD_DOWN, InputType::DownThisFrame, MoveDownLeftCommand(Qbert2));
			dae::InputManager::GetInstance().BindGamePadAction(1, XINPUT_GAMEPAD_DPAD_UP, InputType::DownThisFrame, MoveUpRightCommand(Qbert2));
		
		}


		auto ui = MakeUI(round.roundNumber, round.level);

		for (const auto& uiElement : ui)
		{
			scene.Add(uiElement);
		}

		for (const auto& qbert : qberts)
		{
			scene.Add(qbert);
		}

		auto Disk = std::make_shared<dae::GameObject>();
		Disk->AddComponent<dae::Disk>(qberts, pyramid, 4, true, round.colorIdx);

		scene.Add(Disk);

		auto Disk2 = std::make_shared<dae::GameObject>();
		Disk2->AddComponent<dae::Disk>(qberts, pyramid, 5, false, round.colorIdx);

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


	//CoOpLevel1();
	//CoOpLevel2();
	//CoOpLevel3();

	//VersusLevel1();
	//VersusLevel2();
	//VersusLevel3();

	dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/QBertJump.wav"); //done
	dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/RoundComplete.wav");//done
	dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/CoilySnakeJump.wav");//done
	dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/QBert Fall.wav");
	dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/SlickSamCaught.wav"); //done
	dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/Swearing.wav"); //done
	dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/DiskLift.wav");
	dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/ChangeSelection.wav"); //done
	dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/CoilyEggJump.wav");
	dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/Level.wav");






	dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_F1, InputType::DownThisFrame, LevelSkip(nullptr));


	LoadStartScreen();
	LoadGameOverScreen();
	LoadVictoryScreen();
	LoadTextRound("Level01Solo.txt"); //1-3
	LoadTextRound("Level02Solo.txt"); //4-6
	LoadTextRound("Level03Solo.txt"); //7-10
	LoadTextRound("CoOpLevel01.txt"); //11-14
	LoadTextRound("CoOpLevel02.txt"); //15-18
	LoadTextRound("CoOpLevel03.txt"); //19-22
	LoadTextRound("Level01Versus.txt"); //23-26
	LoadTextRound("Level02Versus.txt"); //27-30
	LoadTextRound("Level03Versus.txt");// 31-34
	

	
}

int main(int, char* []) {
	dae::Minigin engine{"../Data/"};
	engine.Run(load);
	return 0;
}