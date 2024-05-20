#pragma once
#include "Component.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "PyramidMovementComponent.h"
#include "LevelPyramid.h"
#include "Subject.h"
namespace dae 
{
	class SlickSam : public Component
	{
		public:
		SlickSam(GameObject* const pParent, LevelPyramid* pyramid, int StartRow, int StartingIndex);
		~SlickSam() = default;

		SlickSam(const SlickSam& other) = delete;
		SlickSam(SlickSam&& other) = delete;
		SlickSam& operator=(const SlickSam& other) = delete;
		SlickSam& operator=(SlickSam&& other) = delete;

		void Update() override;

		Subject& GetSubject() { return m_Subject; }

		private:
		PyramidMovementComponent* m_pPyramidMovementComponent;
		TextureComponent* m_pTextureComponent;
		LevelPyramid* m_pPyramid;

		glm::vec2 m_CurrentPos;

		Subject m_Subject;

		dae::TextureComponent::SpriteInfo spriteInfo;

		float m_ElapsedTime;
		float m_Delay;

		int m_StartRow;
		int m_StartingIndex;
		GameObject* m_pParent;


	};

}

