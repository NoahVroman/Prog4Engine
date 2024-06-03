#include "SDLSoundSystem.h"
#include <iostream>
#include <memory>
#include <SDL_mixer.h>
#include <queue>
#include <thread>
#include <mutex>
#include <sstream>

//i got a bit of inspiration and help from Liam Wulleart and Jonathan Menschaert for this part
class dae::SDLSoundSystem::Pimpl
{
public:
	Pimpl() 
	{

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, m_MaxChannels) < 0)
		{
			std::cerr << "Unable to initialize SDL_Mixer! " << SDL_GetError();
			return;
		}

		m_Thread = std::jthread{ [this] {HandleSound(); } };
	
	};
	~Pimpl() 
	{
		m_Thread.request_stop();
		m_ThreadCondition.notify_all();
		Mix_HaltChannel(-1);

		for (Sound& sound : m_LoadedSounds)
		{

			Mix_FreeChunk(sound.soundData);
		}

		Mix_CloseAudio();
		Mix_Quit();
	
	};

	void Play(unsigned int soundIndx, int volume) 
	{
		{
			std::lock_guard lock{ m_Lock };
			m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Play, soundIndx });
			if (!m_IsMuted)
			{
				m_SoundQueue.push(SoundEvent{ SoundEvent::Type::VolumeChange, soundIndx, volume });
			}
		}
		m_ThreadCondition.notify_one();
	};
	void Pause(unsigned int soundIndx) 
	{
		{
			std::lock_guard lock{ m_Lock };
			m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Pause, soundIndx });
		}
		m_ThreadCondition.notify_one();

	
	};
	void Resume(unsigned int soundIndx) 
	{
		{
			std::lock_guard lock{ m_Lock };
			m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Resume, soundIndx });
		}
		m_ThreadCondition.notify_one();
	
	};
	void Stop(unsigned int soundIndx) 
	{
		{
			std::lock_guard lock{ m_Lock };
			m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Stop, soundIndx });
		}
		m_ThreadCondition.notify_one();
	
	};
	void Mute(bool mute) 
	{
		m_IsMuted = mute;
		{
			std::lock_guard lock{ m_Lock };
			m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Mute, 0, (mute ? 0 : m_CurrentVolume) });
		}
		m_ThreadCondition.notify_one();
	
	};
	void SetVolume(unsigned int soundIndx, int volume) 
	{
		{
			std::lock_guard lock{ m_Lock };
			m_SoundQueue.push(SoundEvent{ SoundEvent::Type::VolumeChange, soundIndx, volume });
		}
		m_ThreadCondition.notify_one();
	};
	void AddSound(const std::string& path) 
	{
		Sound sound{};
		sound.soundName = path;
		{
			std::lock_guard lock{ m_Lock };
			m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Load, 0, 0, path });
		}
	
	};
	bool Muted() 
	{
		return m_IsMuted;
	};
	unsigned int GetSoundIndex(const std::string& name) 
	{

		auto soundIt = std::find_if(m_LoadedSounds.begin(), m_LoadedSounds.end(), [name](const Sound& element)
									{
										return element.soundName == name;
									});

		if (soundIt != m_LoadedSounds.end())
		{
			return static_cast<unsigned int>(std::distance(m_LoadedSounds.begin(), soundIt));
		}
		return UINT32_MAX;
	
	}


private:

	struct Sound
	{
		Mix_Chunk* soundData{};
		std::string soundName{};
		int channel{ INT32_MAX };
	};

	struct SoundEvent
	{
		enum class Type
		{
			Play,
			Pause,
			Resume,
			Stop,
			Load,
			VolumeChange,
			Mute
		};

		Type eventType{};
		unsigned int soundIdx{};
		int volume{};
		std::string data{};
	};


	void HandleSound()
	{
		const std::stop_token& stopToken{ m_Thread.get_stop_token() };
		while (!stopToken.stop_requested())
		{
			std::unique_lock lock{ m_Lock };
			m_ThreadCondition.wait(lock);
			while (m_SoundQueue.size() > 0 && !stopToken.stop_requested())
			{

				SoundEvent soundEvent{ m_SoundQueue.front() };
				m_SoundQueue.pop();

				lock.unlock();

				switch (soundEvent.eventType)
				{
				case SoundEvent::Type::Play:
				{
					Sound& sound{ m_LoadedSounds[soundEvent.soundIdx] };
					if (Mix_Playing(sound.channel))
					{
						break;
					}

					if (sound.channel > m_MaxChannels)
					{
						const int channel{ Mix_PlayChannel(-1, sound.soundData, 0) };
						if (channel != -1)
						{
							sound.channel = channel;
						}
						else
						{
							break;
						}
					}
					else
					{
						Mix_PlayChannel(sound.channel, sound.soundData, 0);
					}
				}
				break;
				case SoundEvent::Type::Pause:
				{
					Sound& sound{ m_LoadedSounds[soundEvent.soundIdx] };
					if (sound.channel < m_MaxChannels && !Mix_Paused(sound.channel))
					{
						Mix_Pause(sound.channel);
					}
				}
				break;
				case SoundEvent::Type::Resume:
				{
					Sound& sound{ m_LoadedSounds[soundEvent.soundIdx] };
					if (sound.channel < m_MaxChannels && Mix_Paused(sound.channel))
					{
						Mix_Resume(sound.channel);
					}
				}
				break;
				case SoundEvent::Type::Stop:
				{
					Sound& sound{ m_LoadedSounds[soundEvent.soundIdx] };
					if (sound.channel < m_MaxChannels)
					{
						Mix_HaltChannel(sound.channel);
					}
				}
				break;
				case SoundEvent::Type::Load:
				{
					Mix_Chunk* pSound{ Mix_LoadWAV(soundEvent.data.c_str()) };
					if (pSound)
					{
						Sound sound{ pSound, soundEvent.data.c_str() };
						m_LoadedSounds.emplace_back(sound);
					}
				}
				break;
				case SoundEvent::Type::VolumeChange:
				{
					Sound& sound{ m_LoadedSounds[soundEvent.soundIdx] };
					if (sound.channel < m_MaxChannels)
					{
						Mix_Volume(sound.channel, soundEvent.volume);
					}
				}
				break;
				case SoundEvent::Type::Mute:
					if (soundEvent.volume == 0)
					{
						Mix_Volume(-1, 0);
					}
					else
					{
						Mix_Volume(-1, soundEvent.volume);
					}
					break;
				}

				lock.lock();
			}
		}
	}

	std::queue<SoundEvent> m_SoundQueue{};
	std::jthread m_Thread{};
	std::condition_variable m_ThreadCondition{};
	std::mutex m_Lock{};
	std::vector<Sound> m_LoadedSounds{};
	const int m_MaxChannels{ 4096 };
	int m_CurrentVolume{ 100 };
	bool m_IsMuted{};

};



dae::SDLSoundSystem::SDLSoundSystem(): m_pPimpl(new Pimpl())
{
	

}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	delete m_pPimpl;
	m_pPimpl = nullptr;
}

void dae::SDLSoundSystem::Play(unsigned int soundIndx, int volume)
{
	m_pPimpl->Play(soundIndx, volume);
}

void dae::SDLSoundSystem::Pause(unsigned int soundIndx) 
{

	m_pPimpl->Pause(soundIndx);
	
}

void dae::SDLSoundSystem::Resume(unsigned int soundIndx) 
{

	m_pPimpl->Resume(soundIndx);

}
void dae::SDLSoundSystem::Stop(unsigned int soundIndx) 
{
	m_pPimpl->Stop(soundIndx);
}

void dae::SDLSoundSystem::Mute(bool mute)
{
	m_pPimpl->Mute(mute);

}

void dae::SDLSoundSystem::SetVolume(unsigned int soundIndx, int volume)
{
	m_pPimpl->SetVolume(soundIndx, volume);
	
}

void dae::SDLSoundSystem::AddSound(const std::string& path)
{
	m_pPimpl->AddSound(path);
	
}

bool dae::SDLSoundSystem::Muted() 
{
	return m_pPimpl->Muted();
}

unsigned int dae::SDLSoundSystem::GetSoundIndex(const std::string& name)
{

	return m_pPimpl->GetSoundIndex(name);

}
