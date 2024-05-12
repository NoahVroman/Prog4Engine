#pragma once
#include "SoundSystem.h"


namespace dae
{
	class SDLSoundSystem final : public SoundService
	{
		public:
		SDLSoundSystem();
		~SDLSoundSystem();

		void Play(unsigned int soundIndx, int volume) override;
		void Pause(unsigned int soundIndx)  override;
		void Resume(unsigned int soundIndx)  override;
		void Stop(unsigned int soundIndx)  override;
		void Mute(bool mute) override;
		void SetVolume(unsigned int soundIndx, int volume) override;
		void AddSound(const std::string& path) override;
		bool Muted()  override;
		unsigned int GetSoundIndex(const std::string& name) override;

		private:
			
			class Pimpl;
		 	Pimpl* m_pPimpl;




	};

}

