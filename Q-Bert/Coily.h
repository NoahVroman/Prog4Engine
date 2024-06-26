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



		Coily(GameObject* const pParent,std::vector<std::shared_ptr<GameObject>> qberts , LevelPyramid* pyramid,int StartingIndex, int StartRow,bool isPlayer);
		~Coily() = default; 
		Coily(const Coily& other) = delete;
		Coily(Coily&& other) = delete;
		Coily& operator=(const Coily& other) = delete;
		Coily& operator=(Coily&& other) = delete;


		void Update() override;

		void Reset();

		void SetFreeze(bool freeze) { m_Freeze = freeze; }

		PyramidMovementComponent* GetPyramidMovementComponent() const;

		Qbert* GetQbert() const;
		LevelPyramid* GetPyramid() const { return m_pPyramid; }
		Subject& GetSubject() { return m_Subject; }


	private:

		PyramidMovementComponent* m_pPyramidMovementComponent;

		bool m_Freeze;

		std::vector<std::shared_ptr<GameObject>> m_pQbert;
		LevelPyramid* m_pPyramid;
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


	};
};

