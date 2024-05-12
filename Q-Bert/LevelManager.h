#pragma once
#include "Observer.h"
#include "LevelPyramid.h"
#include "Component.h"
#include "GameObject.h"
#include "Qbert.h"
#include "Coily.h"
#include <memory>


namespace dae
{
	class LevelManager : public Component , public Observer
	{

		public:
		LevelManager(GameObject* const pParent,LevelPyramid* pyramid,Qbert* pQbert,Coily* pCoily);
		virtual ~LevelManager() = default;
		void NotifyObserver(Subject* const gameObject, Event currentEvent) override;

		void Update() override;

	private:

		float m_AnimationTimer;
		float m_MaxAnimationTime;

		float m_FlashingTimer;
		float m_MaxFlashingTime;

		int m_CurrentColor;

		bool m_RoundWon;
		bool m_Finished;


		LevelPyramid* m_Pyramid;
		Qbert* m_pQbert;
	};


};

