#pragma once
#include "LevelPyramid.h"
#include <memory>
#include "TextureComponent.h"
#include <glm/glm.hpp>
#include "TransfomComponent.h"
#include "GameObject.h"
#include "Component.h"
#include "LevelCube.h"
#include "Subject.h"

namespace dae
{
	class Qbert final : public Component
	{
		public:
		Qbert(GameObject* pParent, LevelPyramid* pyramid);
		~Qbert();
		Qbert(const Qbert& other) = delete;
		Qbert(Qbert&& other) = delete;
		Qbert& operator=(const Qbert& other) = delete;
		Qbert& operator=(Qbert&& other) = delete;

		void Update() override;

		void MoveUpRight();
		void MoveUpLeft();
		void MoveDownRight();
		void MoveDownLeft();

		Subject& GetSubject() { return m_Subject; }

		glm::vec2 GetCurrentPos() const { return m_CurrentPos; }
		int GetCurrentIndex() const { return m_CurrentCubeIndex; }
		int GetCurrentRow() const { return m_CurrentRow; }

		void Reset();

		private:
     	LevelPyramid* m_pPyramid;
		const float cubeSizeX = m_pPyramid->GetCubeSize().x;
		const float cubeSizeY = m_pPyramid->GetCubeSize().y;
		const float threeQuartersCubeSizeY = cubeSizeY * 0.75f;
		glm::vec2 m_CurrentPos;

		glm::vec2 m_ControlPoint;

		glm::vec2 m_TargetPos;
		bool m_IsMoving;

		float m_MovingDuration;
		float m_MoveTimer;

		


		bool m_PendingJumpedOff{false};
		bool m_JumpedOff{false};

		int m_CurrentRow;
		int m_CurrentCubeIndex;

		GameObject* Parent;

		dae::TextureComponent::SpriteInfo spriteInfo;
		TextureComponent* m_pTextureComponent{ nullptr };
		
		Subject m_Subject;


		unsigned int Factorial(unsigned int n)
		{
			if (n == 0)
				return 0;
			else
				return n + Factorial(n - 1);
		}

		int GetFirstCubeInRow(int row)
		{
			return Factorial(row);
		}
		int GetLastCubeInRow(int row)
		{
			return GetFirstCubeInRow(row) + row;
		}
		bool IsOnLastCubeInRow()
		{
			return m_CurrentCubeIndex == GetLastCubeInRow(m_CurrentRow);
		}
		bool IsOnFirstCubeInRow()
		{
			return m_CurrentCubeIndex == GetFirstCubeInRow(m_CurrentRow);
		}

		void Move(const glm::vec2& target, glm::vec2& controlPoint, float duration);
	};

}

