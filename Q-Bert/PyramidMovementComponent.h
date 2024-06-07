#pragma once
#include "Component.h"
#include "GameObject.h"
#include "glm/glm.hpp"
#include "LevelPyramid.h"

namespace dae 
{
	class PyramidMovementComponent : public Component
	{
	public:
		PyramidMovementComponent(GameObject* const pParrent,LevelPyramid* pPyramid, const glm::vec2& startPos,float movingDuration,int& startIndex,int& startRow);
		~PyramidMovementComponent();

		void MoveDownRight();
		void MoveDownLeft();
		void MoveUpRight();
		void MoveUpLeft();

		void JumpOffRight();
		void JumpOffLeft();

		void MoveUpRIghtUgg();
		void MoveUpLeftUgg();

		void Update() override;

		int GetRows() const { return m_pPyramid->GetRows(); }
		glm::vec2 GetCurrentPos() const { return m_CurrentPos; }
		glm::vec2 GetTargetPos() const { return m_TargetPos; }
		glm::vec2 GetControlPoint() const { return m_ControlPoint; }
		bool IsMoving() const { return m_IsMoving; }
		int GetCurrentRow() const { return m_CurrentRow; }
		int GetCurrentIndex() const { return m_CurrentIndex; }


		void SetCurrentPos(const glm::vec2& pos) { m_CurrentPos = pos; }
		void SetCurrentRow(int row) { m_CurrentRow = row; }
		void SetCurrentIndex(int index) { m_CurrentIndex = index; }

		bool IsOnLastCubeInRow() { return m_CurrentIndex == GetLastCubeInRow(m_CurrentRow); }
		bool IsOnFirstCubeInRow() { return m_CurrentIndex == GetFirstCubeInRow(m_CurrentRow); }

		bool HasJustJumped() const;
		bool HasJumpedOff() const;



		private:

			GameObject* m_pParent;

			int m_CurrentRow;
			int m_CurrentIndex;

			glm::vec2 m_CurrentPos;
			glm::vec2 m_TargetPos;
			glm::vec2 m_ControlPoint;
			float m_MovingDuration;
			float m_MoveTimer;
			bool m_IsMoving;

			bool JumpedOff;

		
			bool m_HasJustJumped;

			LevelPyramid* m_pPyramid;

			const float cubeSizeX;
			const float cubeSizeY;
			const float threeQuartersCubeSizeY;

			void Jump(const glm::vec2& targetPos, const glm::vec2& controlPoint, float duration);

			unsigned int Factorial(unsigned int n)
			{
				return (n * (n + 1)) / 2;
			}
			int GetFirstCubeInRow(int row)
			{
				return Factorial(row);
			}
			int GetLastCubeInRow(int row)
			{
				return GetFirstCubeInRow(row) + row;
			}

			void HandleEndOfJump();

	};


};

