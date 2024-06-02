#pragma once

#include <Windows.h>
#include <Xinput.h>
#include <memory>
#include <type_traits>
#include <WinUser.h>

#include "Singleton.h"
#include <vector>
#include <memory>
#include "Command.h"
#include "Controller.h"
#include "Keyboard.h"
#include "HelperStructsInput.h"
namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:

		InputManager();
		bool ProcessInput();

		void BindGamePadAction(int controllerIndex, int button, InputType inputType, auto command) {
			assert(controllerIndex < static_cast<int>(m_GamePadControllers.size()));
			m_GamePadControllers[controllerIndex]->BindGamePadAction(button, inputType, command);
		}

		void BindKeyboardAction(SDL_Scancode key, InputType inputType ,auto command) {

			m_KeyBoard->BindKeyboardAction(key,inputType ,command);
		}

		private:
			std::vector<std::unique_ptr<dae::Controller>> m_GamePadControllers{};
			const int AmountOfControllers{ 2 };

			std::unique_ptr<Keyboard> m_KeyBoard{};


	};

}
