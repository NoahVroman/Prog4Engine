#pragma once

#include <string>

namespace dae
{
	class SoundService
	{
	public:

		virtual ~SoundService() = default;

		virtual	void Play(unsigned int soundIndx, int volume) = 0;
		virtual void Pause(unsigned int soundIndx)  = 0;
		virtual void Resume(unsigned int soundIndx)  = 0;
		virtual void Stop(unsigned int soundIndx)  = 0;
		virtual void Mute(bool mute) = 0;
		virtual void SetVolume(unsigned int soundIndx, int volume) = 0;
		virtual void AddSound(const std::string& path) = 0;
		virtual bool Muted()  = 0;
		virtual unsigned int GetSoundIndex(const std::string& name) = 0;

	};

}


