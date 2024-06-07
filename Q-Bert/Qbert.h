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
#include "ServiceLocator.h"

namespace dae
{
	class Qbert final : public Component
	{
		public:
		Qbert(GameObject* pParent, LevelPyramid* pyramid,int startingIndex,int StartingRow,bool isPlayer2);
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

		int GetCurrentIndex() const 
		{
			if ((m_HasJustJumped || !m_isOnDisk) && m_CurrentCubeIndex >= 0)
			{
				return m_CurrentCubeIndex;
			}
			else if (m_CurrentCubeIndex == 0 && !m_HasJustJumped)
			{
				return 0;
			}
			else
			{
				return -1;
			}

		}

		int GetCurrentRow() const { return m_CurrentRow; }

		bool IsJumpedOff() const { return m_JumpedOff; }
		bool isMoving() const { return m_IsMoving; }	
		bool IsFrozen() const { return m_Frozen; }
		void SetFrozen(bool frozen) { m_Frozen = frozen; }
		bool isOnDisk() const { return m_isOnDisk; }

		bool HasJustJumped() const { return m_HasJustJumped; }
		void Reset();

		void SetToTopCube();

		void Die();
		void SetDeath(bool death) { m_IsDead = death; }
		void SetIsOnDisk(bool isOnDisk) { m_isOnDisk = isOnDisk; }
		void SetCurrentPos(const glm::vec2& pos) { m_CurrentPos = pos; }

		int GetPreviousIndex() const { return m_PreviousCubeIndex; }

		bool IsOnLastCubeInRow()
		{
			return m_CurrentCubeIndex == GetLastCubeInRow(m_CurrentRow);
		}
		bool IsOnFirstCubeInRow()
		{
			return m_CurrentCubeIndex == GetFirstCubeInRow(m_CurrentRow);
		}

		void InitializePosition(int cubeIndex, int row);

		private: //PYRAMID 
     	LevelPyramid* m_pPyramid;
		const float cubeSizeX = m_pPyramid->GetCubeSize().x;
		const float cubeSizeY = m_pPyramid->GetCubeSize().y;
		const float threeQuartersCubeSizeY = cubeSizeY * 0.75f;

		private: //MOVEMENT
		glm::vec2 m_CurrentPos;
		glm::vec2 m_ControlPoint;
		glm::vec2 m_TargetPos;
		bool m_IsMoving;
		float m_MovingDuration;
		float m_MoveTimer;

		private: //BOOLEANS

		bool m_Frozen{ false };
		bool m_PendingJumpedOff{false};
		bool m_JumpedOff{false};
		bool m_HasJustJumped{false};
		bool m_isOnDisk{ false };

		private: //CUBE INDEX
		int m_CurrentRow;
		int m_CurrentCubeIndex;
		int m_PreviousCubeIndex;

		int m_StartIndex;
		int m_StartRow;

		private: //DEATH 
		bool m_IsDead{ false };
		float m_DeathTimer;
		float m_DeathDuration;


		private: //MISC
		GameObject* Parent;
		dae::TextureComponent::SpriteInfo spriteInfo;
		TextureComponent* m_pCurseTexture{ nullptr };
		TextureComponent* m_pQbertTexture{ nullptr };

		Subject m_Subject;

		private: //FUNCTIONS
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

		void Move(const glm::vec2& target, glm::vec2& controlPoint, float duration);
	};

}

