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

			void BindKeyboardAction(SDL_Scancode key, auto command) {
				m_InputBindings.emplace_back(std::make_unique<KeyBoardInputBinding>(key, command));
			}
			

	private:
		std::vector<std::unique_ptr<KeyBoardInputBinding>> m_InputBindings{};
	};

}

