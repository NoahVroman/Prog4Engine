#pragma once

#include "Component.h"
#include "Observer.h"
#include "Subject.h"
#include "GameObject.h"
#include <vector>

namespace dae
{
    class LevelPyramid;
    class Qbert;
    class Coily;
    class UggWrongWay;
    class SlickSam;

    class LevelManager : public Component, public Observer
    {
    public:
        LevelManager(GameObject* const pParent, LevelPyramid* pyramid, std::vector<std::shared_ptr<GameObject>> pQbert);
        void InitializeRound(int level,int currentRound,bool spawnSlickSams, bool spawnUggWrongs, float slickSamsSpawnInterval, float uggWrongSpawnInterval,int gameMode);
        void NotifyObserver(GameObject* const obj, Event currentEvent) override;
        void Update() override;
        void SpawnCoily();


    private:
        void HandleRoundWon();
        void ResetLevel();
        void UpdateFlashingAnimation(float deltaTime);
        void SpawnSlickSam();
        void SpawnUggWrongWay();

        LevelPyramid* m_Pyramid;
        std::vector<std::shared_ptr<GameObject>> m_pQbert;
        GameObject* m_pCoily;
        std::vector<GameObject*> m_UggWrongWays;
        std::vector<GameObject*> m_SlickSams;

        GameObject* m_pParent;

        int m_GameMode;
        int m_CurrentLevel;
        
        int m_CurrentRound;
        bool m_SpawnSlickSams;
        bool m_SpawnUggWrongs;
        bool m_SpawnCoily;

        float m_CoilySpawnMaxTime;
        float m_SlickSamsSpawnInterval;
        float m_UggWrongSpawnInterval;

        float m_AnimationTimer;
        float m_MaxAnimationTime;
        float m_FlashingTimer;
        float m_MaxFlashingTime;
        int m_CurrentColor;
        bool m_RoundWon;

        float m_CoilySpawnTimer;
        float m_UggWrongWaySpawnTimer;
        float m_SlickSamSpawnTimer;

    };
}
