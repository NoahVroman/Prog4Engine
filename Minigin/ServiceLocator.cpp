#include "ServiceLocator.h"
#include <stdexcept>


std::unique_ptr<dae::SoundService> dae::ServiceLocator::m_pSoundSystemInstance{ nullptr };

std::unique_ptr<dae::SoundService> dae::ServiceLocator::m_pDefaultSoundSystem{ std::make_unique<NullSoundSystem>() };

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundService> soundSystem)
{
	m_pSoundSystemInstance = std::move(soundSystem);
}

dae::SoundService& dae::ServiceLocator::GetSoundSystem()
{
	if (m_pSoundSystemInstance == nullptr)
	{
		m_pSoundSystemInstance = std::move(m_pDefaultSoundSystem);
	}
	return *m_pSoundSystemInstance;
}

