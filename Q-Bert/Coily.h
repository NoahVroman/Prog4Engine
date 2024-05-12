#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Qbert.h"
#include "LevelPyramid.h"
#include "TextureComponent.h"
#include "CoilyState.h"
#include <unordered_map>

#include "Subject.h"

namespace dae 
{
	class Coily final : public Component
	{
	public:

		enum class MovingDirection
		{
			UpRight,
			UpLeft,
			DownRight,
			DownLeft
		};

		Coily(GameObject* const pParent,Qbert* pQbert , LevelPyramid* pyramid,int StartingIndex, int StartRow,float jumpInterval);
		~Coily() = default; 
		Coily(const Coily& other) = delete;
		Coily(Coily&& other) = delete;
		Coily& operator=(const Coily& other) = delete;
		Coily& operator=(Coily&& other) = delete;


		void Update() override;
		void MoveUpRight();
		void MoveUpLeft();
		void MoveDownRight();
		void MoveDownLeft();


		bool IsJumping() const { return m_IsJumping; }
		Qbert* GetQbert() const { return m_pQbert; }
		glm::vec2 GetCurrentPos() const { return m_CurrentPos; }
		int GetCurrentRow() const { return m_CurrentRow; }
		LevelPyramid* GetPyramid() const { return m_pPyramid; }
		Subject& GetSubject() { return m_Subject; }


	private:

		Qbert* m_pQbert;
		LevelPyramid* m_pPyramid;
		int m_CurrentIndex;
		int m_CurrentRow;
		float m_JumpInterval;
		glm::vec2 m_ControlPoint;
		bool m_IsJumping;
		float m_JumpTimer;
		float m_JumpDuration;
		GameObject* m_pParent;
		TextureComponent* m_pTextureComponent;
		glm::vec2 m_CurrentPos;
		glm::vec2 m_TargetPos;
		MovingDirection m_CurrentDirection;
		Subject m_Subject;
		dae::TextureComponent::SpriteInfo spriteInfo;


		std::unordered_map<CoilyState::CoilyStateEnum,std::unique_ptr<CoilyState>> m_pCoilyState;

		CoilyState* m_CurrentState;

		const float cubeSizeX = m_pPyramid->GetCubeSize().x;
		const float cubeSizeY = m_pPyramid->GetCubeSize().y;
		const float threeQuartersCubeSizeY = cubeSizeY * 0.75f;



		void InitializeSpriteInfo();
		void UpdateJumping();
		void UpdateStanding();
		void UpdateTextureBasedOnState();
		void HandleJumpEnd();
		void Jump(const glm::vec2& target, glm::vec2& controlPoint, float duration);

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
			return m_CurrentIndex == GetLastCubeInRow(m_CurrentRow);
		}
		bool IsOnFirstCubeInRow()
		{
			return m_CurrentIndex == GetFirstCubeInRow(m_CurrentRow);
		}


	};
};

