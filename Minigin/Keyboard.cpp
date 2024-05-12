#include "Keyboard.h"
bool dae::Keyboard::ProcessInput()
{
    const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);

    for (auto& binding : m_InputBindings) {
        if (keyboardState[binding->key]) {
            binding->command->Execute();
        }
    }

    return true;

}
