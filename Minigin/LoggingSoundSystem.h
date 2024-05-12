#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae
{
	class LoggingSoundSystem final : public SoundService
	{
	public:
		LoggingSoundSystem(std::unique_ptr<SoundService>&& soundsystem);
		~LoggingSoundSystem() = default;

		LoggingSoundSystem(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem(LoggingSoundSystem&& other) = delete;
		LoggingSoundSystem& operator=(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem& operator=(LoggingSoundSystem&& other) = delete;


		virtual void Play(unsigned int soundIndx, int volume) override;
		virtual void Pause(unsigned int soundIndx) override;
		virtual void Resume(unsigned int soundIndx) override;
		virtual void Stop(unsigned int soundIndx) override;
		virtual void Mute(bool mute) override;
		virtual void SetVolume(unsigned int soundIndx, int volume) override;
		virtual void AddSound(const std::string& path) override;
		virtual bool Muted() override;
		virtual unsigned int GetSoundIndex(const std::string& name) override;

	private:

		std::unique_ptr<SoundService> m_pSoundSystem{};
	};
}

