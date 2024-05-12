#include <SDL.h>
#include "InputManager.h"

dae::InputManager::InputManager()
{
	m_GamePadControllers.resize(AmountOfControllers);
	for (int index{}; index < AmountOfControllers; ++index)
	{
		m_GamePadControllers[index] = std::make_unique<Controller>(index);
		m_GamePadControllers[index] = std::make_unique<Controller>(index);
	}

	m_KeyBoard = std::make_unique<Keyboard>();
}

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}

	}

	m_KeyBoard->ProcessInput();

	for (auto& controller : m_GamePadControllers)
	{
		controller->ProcessInput();
	}

	return true;
}
