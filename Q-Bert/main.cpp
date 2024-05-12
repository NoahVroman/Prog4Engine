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




void load()
{
	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto mainTextFont = resourceManager.LoadFont("Minecraft.ttf", 36);


	std::unique_ptr<dae::SoundService> soundSystem = std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>());

	dae::ServiceLocator::RegisterSoundSystem(std::move(soundSystem));

	auto& sceneManager = dae::SceneManager::GetInstance();
	auto& gameScene = sceneManager.CreateScene("GameScene");

	auto level = std::make_shared<dae::GameObject>();
	level->GetTransform()->SetLocalPosition(glm::vec2{ 0,0 });

	dae::LevelPyramid::PyramidSettings settings{};
	settings.StartPos = glm::vec2{ 300,70 };
	settings.Rows = 7;
	settings.CubeSize = glm::vec2{ 62, 64 };
	settings.Level = 1;
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
	
	dae::InputManager::GetInstance().BindGamePadAction(0, XINPUT_GAMEPAD_DPAD_RIGHT,InputType::DownThisFrame ,MoveDownRightCommand(Qbert));
	dae::InputManager::GetInstance().BindGamePadAction(0, XINPUT_GAMEPAD_DPAD_DOWN, InputType::DownThisFrame, MoveDownLeftCommand(Qbert));
	dae::InputManager::GetInstance().BindGamePadAction(0, XINPUT_GAMEPAD_DPAD_LEFT, InputType::DownThisFrame, MoveUpLeftCommand(Qbert));
	dae::InputManager::GetInstance().BindGamePadAction(0, XINPUT_GAMEPAD_DPAD_UP, InputType::DownThisFrame, MoveUpRightCommand(Qbert));

	gameScene.Add(Qbert);


	auto Coily = std::make_shared<dae::GameObject>();
	auto coilyComponent = Coily->AddComponent<dae::Coily>(qbertcomponent,pyramid,2,1,0.65f);

	gameScene.Add(Coily);


	auto levelManager = std::make_shared<dae::GameObject>();
	levelManager->AddComponent<dae::LevelManager>(pyramid, qbertcomponent, coilyComponent);

	gameScene.Add(levelManager);






}

int main(int, char* []) {
	dae::Minigin engine{"../Data/"};
	engine.Run(load);
	return 0;
}