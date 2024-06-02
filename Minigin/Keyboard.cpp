#include "Keyboard.h"
bool dae::Keyboard::ProcessInput()
{
    m_CurrentKeyboardState = SDL_GetKeyboardState(nullptr);

    // Iterate through the input bindings and execute commands based on the input type
    for (auto& binding : m_InputBindings)
    {
        if (!binding->command)
            continue;

        switch (binding->inputType)
        {
        case InputType::Pressed:
            if (IsKeyPressed(binding->key))
            {
                binding->command->Execute();
            }
            break;

        case InputType::DownThisFrame:
            if (IsKeyPressedThisFrame(binding->key))
            {
                binding->command->Execute();
            }
            break;

        case InputType::UpThisFrame:
            if (IsKeyReleasedThisFrame(binding->key))
            {
                binding->command->Execute();
            }
            break;

        default:
            break;
        }
    }

    // Store the current keyboard state as the previous state for the next frame
    memcpy(m_PreviousKeyboardState, m_CurrentKeyboardState, sizeof(m_PreviousKeyboardState));

    return true;
}

bool dae::Keyboard::IsKeyPressed(SDL_Scancode key) const
{
    return m_CurrentKeyboardState[key];
}

bool dae::Keyboard::IsKeyPressedThisFrame(SDL_Scancode key) const
{
    return m_CurrentKeyboardState[key] && !m_PreviousKeyboardState[key];
}

bool dae::Keyboard::IsKeyReleasedThisFrame(SDL_Scancode key) const
{
    return !m_CurrentKeyboardState[key] && m_PreviousKeyboardState[key];
}
