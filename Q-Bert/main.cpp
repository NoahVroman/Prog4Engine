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

#include <fstream>
#include <sstream>

auto& scene = dae::SceneManager::GetInstance().CreateScene("GameScene");

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
	rounds[0].slickSamsSpawnInterval = 0;
	rounds[0].uggWrongSpawnInterval = 0;
	rounds[0].gameMode = 0;

	rounds[1].roundNumber = 2;
	rounds[1].level = 1;
	rounds[1].colorIdx = 1;
	rounds[1].spawnSlickSams = false;
	rounds[1].spawnUggWrongs = false;
	rounds[1].slickSamsSpawnInterval = 0;
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



void LoadTextRound(const std::string& filePath,int roundindex) {
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

	//if (!levelFile.good()) {
	//	std::cout << "Level file wasn't properly read\n";
	//}


	auto level = std::make_shared<dae::GameObject>();
	level->GetTransform()->SetLocalPosition(glm::vec2{ 0,0 });

	dae::LevelPyramid::PyramidSettings settings{};
	settings.StartPos = glm::vec2{ 300,70 };
	settings.Rows = 7;
	settings.CubeSize = glm::vec2{ 62, 64 };
	settings.Level = rounds[roundindex].level;
	settings.ColorIndex = rounds[roundindex].colorIdx;
	settings.SpriteSize = glm::vec2{ 32, 32 };

	auto pyramid = level->AddComponent<dae::LevelPyramid>(settings);

	for (const auto& cube : pyramid->GetCubes())
	{
		scene.Add(cube);
	}
	
	scene.Add(level);

	auto Qbert = std::make_shared<dae::GameObject>();
	auto qbertcomponent = Qbert->AddComponent<dae::Qbert>(pyramid);

	dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_D, InputType::DownThisFrame, MoveDownRightCommand(Qbert));
	dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_S, InputType::DownThisFrame, MoveDownLeftCommand(Qbert));
	dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_A, InputType::DownThisFrame, MoveUpLeftCommand(Qbert));
	dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_W, InputType::DownThisFrame, MoveUpRightCommand(Qbert));

	scene.Add(Qbert);

	auto Disk = std::make_shared<dae::GameObject>();
	Disk->AddComponent<dae::Disk>(Qbert.get(), pyramid, 4, true, rounds[roundindex].colorIdx);

	scene.Add(Disk);

	auto Disk2 = std::make_shared<dae::GameObject>();
	Disk2->AddComponent<dae::Disk>(Qbert.get(), pyramid, 6, false, rounds[roundindex].colorIdx);

	scene.Add(Disk2);



	auto Coily = std::make_shared<dae::GameObject>();
	Coily->AddComponent<dae::Coily>(qbertcomponent, pyramid, 4, 2);

	scene.Add(Coily);


	auto Ugg = std::make_shared<dae::GameObject>();
	Ugg->AddComponent<dae::UggWrongWay>(pyramid, 6, true);
	scene.Add(Ugg);

	auto SlickSam = std::make_shared<dae::GameObject>();
	SlickSam->AddComponent<dae::SlickSam>(pyramid, qbertcomponent, 1, 1);
	scene.Add(SlickSam);



	auto levelManager = std::make_shared<dae::GameObject>();
	levelManager->AddComponent<dae::LevelManager>(pyramid, Qbert.get(), Coily.get(), Ugg.get(), SlickSam.get());

	scene.Add(levelManager);


}


void load()
{
	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto mainTextFont = resourceManager.LoadFont("Minecraft.ttf", 36);


	std::unique_ptr<dae::SoundService> soundSystem = std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>());
	dae::ServiceLocator::RegisterSoundSystem(std::move(soundSystem));

	LoadTextRound("Level01Solo.txt",0);

	
}

int main(int, char* []) {
	dae::Minigin engine{"../Data/"};
	engine.Run(load);
	return 0;
}