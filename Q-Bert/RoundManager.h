#pragma once
#include <string>
#include <vector>
struct Round {
    int roundNumber;
    int level;
    int colorIdx;
    bool spawnSlickSams;
    bool spawnUggWrongs;
    float slickSamsSpawnInterval;
    float uggWrongSpawnInterval;
    int gameMode;
};

namespace dae
{
	class LevelPyramid;
	class LevelManager;
	class Disk;
	class RoundManager
	{
    public:
        RoundManager();
        ~RoundManager();

        void LoadRoundData(const std::string& filePath,const std::string& SceneName);


        void SwitchToNextRound();
        void ResetRound();

        void SwithToNextLevel();

        void LoadLevel();

        

        Round& GetRound(size_t index)
        {
            return m_Rounds[index];
        }

        private:
            std::vector<Round> m_Rounds;
            int m_CurrentRoundIdx;
            int m_CurrentLevelIdx;

            LevelPyramid* m_pLevelPyramid{nullptr};
            LevelManager* m_pLevelManager{ nullptr };

            Disk* m_pDisk{ nullptr };
            Disk* m_pDisk2{ nullptr };
        



	};


};

