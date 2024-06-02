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



void load()
{
	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto mainTextFont = resourceManager.LoadFont("Minecraft.ttf", 36);


	//std::unique_ptr<dae::SoundService> soundSystem = std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>());
	//dae::ServiceLocator::RegisterSoundSystem(std::move(soundSystem));

	auto& sceneManager = dae::SceneManager::GetInstance();
	auto& gameScene = sceneManager.CreateScene("GameScene");

	auto level = std::make_shared<dae::GameObject>();
	level->GetTransform()->SetLocalPosition(glm::vec2{ 0,0 });

	dae::LevelPyramid::PyramidSettings settings{};
	settings.StartPos = glm::vec2{ 300,70 };
	settings.Rows = 7;
	settings.CubeSize = glm::vec2{ 62, 64 };
	settings.Level = 2;
	settings.ColorIndex = 0;
	settings.SpriteSize = glm::vec2{ 32, 32 };


	auto pyramid = level->AddComponent<dae::LevelPyramid>(settings);

	for (const auto& cube : pyramid->GetCubes())
	{
		gameScene.Add(cube);
	}

	gameScene.Add(level);

	auto Qbert = std::make_shared<dae::GameObject>();
	auto qbertcomponent =  Qbert->AddComponent<dae::Qbert>(pyramid);
	
	dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_D, InputType::DownThisFrame ,MoveDownRightCommand(Qbert));
	dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_S, InputType::DownThisFrame, MoveDownLeftCommand(Qbert));
	dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_A, InputType::DownThisFrame, MoveUpLeftCommand(Qbert));
	dae::InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_W, InputType::DownThisFrame, MoveUpRightCommand(Qbert));

	gameScene.Add(Qbert);


	auto Coily = std::make_shared<dae::GameObject>();
	Coily->AddComponent<dae::Coily>(qbertcomponent,pyramid,2,1);

	gameScene.Add(Coily);


	auto Ugg = std::make_shared<dae::GameObject>();
	Ugg->AddComponent<dae::UggWrongWay>(pyramid, 6, true);

	auto SlickSam = std::make_shared<dae::GameObject>();
	SlickSam->AddComponent<dae::SlickSam>(pyramid, 1, 1);

	gameScene.Add(Ugg);
	gameScene.Add(SlickSam);


	auto levelManager = std::make_shared<dae::GameObject>();
	levelManager->AddComponent<dae::LevelManager>(pyramid, Qbert.get(), Coily.get(), Ugg.get());

	gameScene.Add(levelManager);






}

int main(int, char* []) {
	dae::Minigin engine{"../Data/"};
	engine.Run(load);
	return 0;
}