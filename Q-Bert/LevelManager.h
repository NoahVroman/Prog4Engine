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
        LevelManager(GameObject* const pParent, LevelPyramid* pyramid, GameObject* pQbert);
        void InitializeRound(bool spawnSlickSams, bool spawnUggWrongs, float slickSamsSpawnInterval, float uggWrongSpawnInterval,int gameMode);
        void NotifyObserver(GameObject* const obj, Event currentEvent) override;
        void Update() override;

    private:
        void HandleRoundWon();
        void ResetLevel();
        void UpdateFlashingAnimation(float deltaTime);
        void SpawnSlickSam();
        void SpawnUggWrongWay();
        void SpawnCoily();

        LevelPyramid* m_Pyramid;
        GameObject* m_pQbert;
        GameObject* m_pCoily;
        std::vector<GameObject*> m_UggWrongWays;
        std::vector<GameObject*> m_SlickSams;

        GameObject* m_pParent;

        int m_GameMode;
        
        bool m_SpawnSlickSams;
        bool m_SpawnUggWrongs;
        float m_SlickSamsSpawnInterval;
        float m_UggWrongSpawnInterval;

        float m_AnimationTimer;
        float m_MaxAnimationTime;
        float m_FlashingTimer;
        float m_MaxFlashingTime;
        int m_CurrentColor;
        bool m_RoundWon;

        float m_SlickSamSpawnTimer;
        float m_UggWrongWaySpawnTimer;
    };
}
