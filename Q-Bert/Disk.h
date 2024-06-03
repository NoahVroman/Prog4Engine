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

		Disk(GameObject* const pParent,GameObject* qbert,LevelPyramid* levelPyramid ,int startRow,bool isLeft,int colorindex);
		~Disk();

		Disk(const Disk& other) = delete;
		Disk(Disk&& other) = delete;
		Disk& operator=(const Disk& other) = delete;
		Disk& operator=(Disk&& other) = delete;

		virtual void Update() override;


	private:
		bool m_Activated;
		GameObject* m_pParent;
		GameObject* m_QbertObj;
		Qbert* m_pQbert;

		glm::vec2 m_CurrentPos;
		glm::vec2 m_TargetPos;

		LevelPyramid* m_pLevelPyramid;


		float m_FlightTime;
		bool m_FinalPositionReached;


		float m_FloatTime;
		float QbertFallSpeed;


		int m_StartRow;
		bool m_IsLeft;
		int m_ColorIndex;



		TextureComponent::SpriteInfo spriteInfo{};


		TextureComponent* m_pTextureComponent;

		float m_TimeSinceLastFrameIdle;
		int m_FPSIdle;
		int m_CurrentFrame;
		int m_MaxFramesIdle;



		int m_PreviousRow;
		int m_PreviousIndex;



	};


}
