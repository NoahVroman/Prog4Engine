#pragma once

#include <memory>
#include "SoundSystem.h"

namespace dae 
{

	class NullSoundSystem final : public SoundService
	{

		public:
			void Play(unsigned int , int ) override {};
			void Pause(unsigned int )  override {};
			void Resume(unsigned int )  override {};
			void Stop(unsigned int )  override {};
			void Mute(bool ) override {};
			void SetVolume(unsigned int , int ) override {};
			void AddSound(const std::string& ) override {};
			bool Muted()  override { return false; }; 
			unsigned int GetSoundIndex(const std::string& ) override {return UINT32_MAX;};
	};



	class ServiceLocator final
	{
		public:
		static void RegisterSoundSystem(std::unique_ptr<SoundService> soundSystem);
		static SoundService& GetSoundSystem();
		private:
			static std::unique_ptr<SoundService> m_pSoundSystemInstance;
			static std::unique_ptr<SoundService> m_pDefaultSoundSystem;

	};

}

