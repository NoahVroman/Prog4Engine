#pragma once
#include "Component.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "PyramidMovementComponent.h"
#include "LevelPyramid.h"
#include "Subject.h"
namespace dae
{
	class UggWrongWay : public Component
	{
	public:
		UggWrongWay(GameObject* const pParent, LevelPyramid* pyramid, int StartRow, bool isStartingLeft);
		~UggWrongWay() = default;

		UggWrongWay(const UggWrongWay& other) = delete;
		UggWrongWay(UggWrongWay&& other) = delete;
		UggWrongWay& operator=(const UggWrongWay& other) = delete;
		UggWrongWay& operator=(UggWrongWay&& other) = delete;

		void SetFreeze(bool freeze) { m_Freeze = freeze; }

		void Update() override;

		Subject& GetSubject() { return m_Subject; }



		private:
		PyramidMovementComponent* m_pPyramidMovementComponent;
		TextureComponent* m_pTextureComponent;
		LevelPyramid* m_pPyramid;

		bool m_Freeze;

		glm::vec2 m_CurrentPos;

		Subject m_Subject;

		dae::TextureComponent::SpriteInfo spriteInfo;

		float m_ElapsedTime;
		float m_Delay;

		int m_StartRow;
		bool m_IsStartingLeft;
		GameObject* m_pParent;

	};

}
