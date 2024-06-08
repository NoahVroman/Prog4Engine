// LevelManager.h
#pragma once

#include <vector>
#include <memory>
#include "Component.h"
#include "GameObject.h"
#include "Observer.h"
#include "LevelPyramid.h"
#include "Qbert.h"
#include "Coily.h"
#include "SlickSam.h"
#include "UggWrongWay.h"

namespace dae {
    class LevelManager : public Component, public Observer {
    public:
        LevelManager(GameObject* const pParent, LevelPyramid* pyramid, std::vector<std::shared_ptr<GameObject>> pQbert);

        void InitializeRound(int level, int currentRound, bool spawnSlickSams, bool spawnUggWrongs,
                             float slickSamsSpawnInterval, float uggWrongSpawnInterval, int gameMode);
        void Update() override;
        void NotifyObserver(GameObject* const obj, Event currentEvent) override;

    private:
        // Helper methods
        void HandleRoundWon();
        void UpdateFlashingAnimation(float deltaTime);
        void ResetLevel();
        void SpawnSlickSam();
        void SpawnUggWrongWay();
        void SpawnCoily();

        // Member variables
        LevelPyramid* m_Pyramid;
        std::vector<std::shared_ptr<GameObject>> m_pQbert;

        std::vector<GameObject*> m_SlickSams;
        std::vector<GameObject*> m_UggWrongWays;
        GameObject* m_pCoily;
        std::shared_ptr<GameObject> m_pCoilyshared;

        GameObject* m_pParent;

        int m_CurrentLevel;
        int m_CurrentRound;
        int m_GameMode;

        bool m_RoundWon;
        bool m_SpawnSlickSams;
        bool m_SpawnUggWrongs;
        bool m_SpawnCoily;

        float m_AnimationTimer;
        float m_MaxAnimationTime;
        float m_FlashingTimer;
        float m_MaxFlashingTime;
        float m_SlickSamSpawnTimer;
        float m_SlickSamsSpawnInterval;
        float m_UggWrongWaySpawnTimer;
        float m_UggWrongSpawnInterval;
        float m_CoilySpawnTimer;
        float m_CoilySpawnMaxTime;

        int m_CurrentColor;
    };
}
