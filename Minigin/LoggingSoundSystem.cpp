#include "LoggingSoundSystem.h"
#include <iostream>

dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<SoundService>&& soundsystem)
	:m_pSoundSystem(std::move(soundsystem))
{
}


void dae::LoggingSoundSystem::Play(unsigned int soundIndx, int volume)
{

	std::cout << "Playing sound with index: " << soundIndx << " and volume: " << volume << std::endl;
	m_pSoundSystem->Play(soundIndx, volume);


}

void dae::LoggingSoundSystem::Pause(unsigned int soundIndx)
{
	std::cout << "Pausing sound with index: " << soundIndx << std::endl;
	m_pSoundSystem->Pause(soundIndx);
}

void dae::LoggingSoundSystem::Resume(unsigned int soundIndx)
{
		std::cout << "Resuming sound with index: " << soundIndx << std::endl;
	m_pSoundSystem->Resume(soundIndx);
}

void dae::LoggingSoundSystem::Stop(unsigned int soundIndx)
{
		std::cout << "Stopping sound with index: " << soundIndx << std::endl;
	m_pSoundSystem->Stop(soundIndx);
}

void dae::LoggingSoundSystem::Mute(bool mute)
{
	std::cout << "Muting sound" << std::endl;
	m_pSoundSystem->Mute(mute);
}

void dae::LoggingSoundSystem::SetVolume(unsigned int soundIndx, int volume)
{
		std::cout << "Setting volume of sound with index: " << soundIndx << " to: " << volume << std::endl;
	m_pSoundSystem->SetVolume(soundIndx, volume);
}

void dae::LoggingSoundSystem::AddSound(const std::string& path)
{
			std::cout << "Adding sound with path: " << path << std::endl;
	m_pSoundSystem->AddSound(path);
}

bool dae::LoggingSoundSystem::Muted()
{
	return m_pSoundSystem->Muted();
}

unsigned int dae::LoggingSoundSystem::GetSoundIndex(const std::string& name)
{
	return m_pSoundSystem->GetSoundIndex(name);
}
