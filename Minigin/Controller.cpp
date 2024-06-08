#include "Controller.h"
#include <Windows.h>
#include <Xinput.h>
#include <WinUser.h>
namespace dae 
{
    class Controller::Pimpl 
    {

    public:

        Pimpl(int controllerIndex)
            : m_ControllerIndex(controllerIndex)
        {
		}

        ~Pimpl()
        {

		}

        bool ProcessInput()
        {
			XINPUT_STATE previousState{};
			CopyMemory(&previousState, &m_CurrentState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
			XInputGetState(m_ControllerIndex, &m_CurrentState);

			int buttonChanges{ m_CurrentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons };
			m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
			m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

            for (auto& inputBinding : m_InputBindings)
            {
				if (!inputBinding.command)
					continue;

                switch (inputBinding.inputType)
                {
				case InputType::Pressed:
                {
                    if (IsButtonPressed(inputBinding.button))
                    {
						inputBinding.command->Execute();
					}
					break;
				}
				case InputType::DownThisFrame:
                {
                    if (IsButtonPressedThisFrame(inputBinding.button))
                    {
						inputBinding.command->Execute();
					}
					break;
				}
				case InputType::UpThisFrame:
                {
                    if (IsButtonReleasedThisFrame(inputBinding.button))
                    {
						inputBinding.command->Execute();
					}
					break;
				}
				default:
					break;
				}
			}

			return true;
		}


		void BindGamePadAction(const GamePadInputBinding& binding)
		{
			m_InputBindings.emplace_back(binding);
		}

		void ClearBindings()
		{
			m_InputBindings.clear();
		}
    private:

        int m_ControllerIndex{ -1 };

        std::vector<GamePadInputBinding> m_InputBindings{};
        XINPUT_STATE m_CurrentState{};

        int m_ButtonsPressedThisFrame{};
        int m_ButtonsReleasedThisFrame{};

		bool IsButtonPressedThisFrame(unsigned int button) const
		{
			return m_ButtonsPressedThisFrame & button;
		}

		bool IsButtonReleasedThisFrame(unsigned int button) const
		{
			return m_ButtonsReleasedThisFrame & button;
		}

		bool IsButtonPressed(unsigned int button) const
		{
			return m_CurrentState.Gamepad.wButtons & button;
		}



    };
}


dae::Controller::Controller(int controllerIndex)
	: m_pPimpl(new Pimpl(controllerIndex))
{

}


dae::Controller::~Controller()
{
	delete m_pPimpl;
	m_pPimpl = nullptr;
}


bool dae::Controller::ProcessInput()
{
      return m_pPimpl->ProcessInput();
}

void dae::Controller::BindGamePadAction(const GamePadInputBinding& binding)
{
	m_pPimpl->BindGamePadAction(binding);

}

void dae::Controller::ClearBindings()
{
	m_pPimpl->ClearBindings();
}



