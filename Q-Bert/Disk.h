#pragma once
#include "Component.h"
#include "Qbert.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "LevelPyramid.h"

namespace dae
{
	class Disk : public Component
	{
    public:
        Disk(GameObject* const pParent,std::vector<std::shared_ptr<GameObject>> qberts, LevelPyramid* levelPyramid, int startRow, bool isLeft, int colorIndex);
        ~Disk() override;

        void Update() override;

        void SetColorIndex(int index) { m_ColorIndex = index; }


    private:
        void UpdateAnimation();
        void CheckQbertActivation();
        void UpdateFlight();

        GameObject* const m_pParent;
        std::vector<std::shared_ptr<GameObject>> m_QbertObj;
        LevelPyramid* const m_pLevelPyramid;

        std::vector<Qbert*> m_pQbert;
        TextureComponent* m_pTextureComponent;

        glm::vec2 m_CurrentPos;
        glm::vec2 m_TargetPos;

        float m_FloatTime;
        float m_TimeSinceLastFrameIdle;
        float m_FlightTime;

        float m_FallTime;
        float QbertFallSpeed;
        float m_MaxFallTime;

        int m_StartRow;
        int m_ColorIndex;
        int m_CurrentFrame;
        int m_MaxFramesIdle;
        int m_PreviousRow;
        int m_PreviousIndex;
        const int m_FPSIdle;

        bool m_IsLeft;
        bool m_Activated;
        bool m_FinalPositionReached;

        TextureComponent::SpriteInfo m_SpriteInfo;

        std::shared_ptr<GameObject> m_ActivatingQbert;
	};


}
