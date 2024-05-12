#pragma once

#include <memory>
#include "Command.h"
#include "HelperStructsInput.h"

namespace dae 
{
	class Controller
	{
	public:
		Controller(int controllerIndex);

		~Controller();

		bool ProcessInput();

		void BindGamePadAction(const GamePadInputBinding& binding);
		void BindGamePadAction(int button, InputType inputType, auto command)
		{
			BindGamePadAction(GamePadInputBinding(button, inputType, command));
		}
	private:

		class Pimpl;
		Pimpl* m_pPimpl;

	};
	




};

