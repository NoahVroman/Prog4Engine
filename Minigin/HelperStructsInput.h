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
    InputType inputType;
    std::shared_ptr<dae::Command> command;

    template<typename CommandType>
    KeyBoardInputBinding(SDL_Scancode keyIn,InputType inputTypeIn ,CommandType commandIn)
        : key{ keyIn } , inputType{ inputTypeIn }
    {
        static_assert(std::is_base_of<dae::Command, CommandType>::value, "CommandType must be derived from Command");
        command = std::make_shared<CommandType>(commandIn);
    }
};
