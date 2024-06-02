#pragma once
#include <memory>
#include <vector>
#include "HelperStructsInput.h"
#include "Command.h"
namespace dae
{
	class Keyboard final
	{
		public:
			Keyboard() = default;

			bool ProcessInput();

			void BindKeyboardAction(SDL_Scancode key,InputType inputType ,auto command) {
				m_InputBindings.emplace_back(std::make_unique<KeyBoardInputBinding>(key,inputType ,command));
			}
			

	private:

		bool IsKeyPressed(SDL_Scancode key) const;
		bool IsKeyPressedThisFrame(SDL_Scancode key) const;
		bool IsKeyReleasedThisFrame(SDL_Scancode key) const;

		const uint8_t* m_CurrentKeyboardState;
		uint8_t m_PreviousKeyboardState[SDL_NUM_SCANCODES];

		std::vector<std::unique_ptr<KeyBoardInputBinding>> m_InputBindings{};
	};

}

