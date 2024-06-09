#pragma once
#include <string>
#include <vector>
#include <memory>
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

    class GameObject;
    class RoundManager : public std::enable_shared_from_this<RoundManager>
	{
    public:
        RoundManager();
        ~RoundManager();

        void LoadRoundData(const std::string& filePath,const std::string& SceneName);

        std::vector<std::shared_ptr<GameObject>> MakeUI();

        void SwitchToNextRound();
        void ResetRound();

        void SwithToNextLevel();

        void LoadLevel();

        void SetCurrentRound(int roundIdx);

        void ClearRounds();
        

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

