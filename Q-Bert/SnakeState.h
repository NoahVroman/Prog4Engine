#pragma once
#include "CoilyState.h"
#include "Coily.h"
namespace dae
{

	class SnakeState : public CoilyState
	{
	public:


		SnakeState(GameObject* const pParent);
		virtual ~SnakeState();
		SnakeState(const SnakeState& other) = delete;
		SnakeState(SnakeState&& other) = delete;
		SnakeState& operator=(const SnakeState& other) = delete;
		SnakeState& operator=(SnakeState&& other) = delete;


		virtual void Update(Coily* coily) override;
		void HandleMovement(Coily* coily);

		void UpdateTexture();

		CoilyStateEnum GetNextState(Coily* coily) override;

		private:
			float m_JumpInterval;
			float m_JumpTimer;

			enum class Direction
			{
				UpRight,
				UpLeft,
				DownRight,
				DownLeft
			};


			Direction m_Direction;
	};


};
