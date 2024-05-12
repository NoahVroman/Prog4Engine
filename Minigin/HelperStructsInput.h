#pragma once

#include <SDL.h>
#include <memory>
#include "Command.h"

//////////////////////////
// Input Type Definitions
//////////////////////////

enum class InputType {
    Pressed,
    DownThisFrame,
    UpThisFrame
};

//////////////////////////
// Input Binding Structures
//////////////////////////

struct GamePadInputBinding 
{
    int button;
    InputType inputType;
    std::shared_ptr<dae::Command> command;

    template<typename CommandType>
    GamePadInputBinding(int buttonIn, InputType inputTypeIn, CommandType commandIn)
        : button{ buttonIn },
        inputType{ inputTypeIn } {
        static_assert(std::is_base_of<dae::Command, CommandType>::value, "CommandType must be derived from Command");
        command = std::make_shared<CommandType>(commandIn);
    }
};

struct KeyBoardInputBinding 
{
    SDL_Scancode key;
    std::shared_ptr<dae::Command> command;

    template<typename CommandType>
    KeyBoardInputBinding(SDL_Scancode keyIn, CommandType commandIn)
        : key{ keyIn } {
        static_assert(std::is_base_of<dae::Command, CommandType>::value, "CommandType must be derived from Command");
        command = std::make_shared<CommandType>(commandIn);
    }
};
