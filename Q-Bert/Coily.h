#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Qbert.h"
#include "LevelPyramid.h"
#include "TextureComponent.h"
#include "CoilyState.h"
#include <unordered_map>
#include "PyramidMovementComponent.h"
#include <iostream>
#include "Subject.h"

namespace dae 
{
	class Coily final : public Component
	{
	public:



		Coily(GameObject* const pParent,Qbert* pQbert , LevelPyramid* pyramid,int StartingIndex, int StartRow,float jumpInterval);
		~Coily() = default; 
		Coily(const Coily& other) = delete;
		Coily(Coily&& other) = delete;
		Coily& operator=(const Coily& other) = delete;
		Coily& operator=(Coily&& other) = delete;


		void Update() override;


		Qbert* GetQbert() const { return m_pQbert; }
		LevelPyramid* GetPyramid() const { return m_pPyramid; }
		Subject& GetSubject() { return m_Subject; }


	private:

		PyramidMovementComponent* m_pPyramidMovementComponent;


		Qbert* m_pQbert;
		LevelPyramid* m_pPyramid;
		float m_JumpInterval;
		GameObject* m_pParent;
		glm::vec2 m_CurrentPos;
		glm::vec2 m_TargetPos;
		Subject m_Subject;


		int m_StartingIndex;
		int m_StartRow;
	

		TextureComponent* m_pTextureComponent;
		dae::TextureComponent::SpriteInfo spriteInfo;


		std::unordered_map<CoilyState::CoilyStateEnum,std::unique_ptr<CoilyState>> m_pCoilyState;
		CoilyState* m_CurrentState;



		void InitializeSpriteInfo();


	};
};

