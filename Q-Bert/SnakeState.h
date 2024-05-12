#pragma once
#include "CoilyState.h"
#include "Coily.h"
namespace dae
{

	class SnakeState : public CoilyState
	{
	public:
		SnakeState();
		virtual ~SnakeState();
		SnakeState(const SnakeState& other) = delete;
		SnakeState(SnakeState&& other) = delete;
		SnakeState& operator=(const SnakeState& other) = delete;
		SnakeState& operator=(SnakeState&& other) = delete;


		virtual void Update(Coily* coily) override;

		CoilyStateEnum GetNextState(Coily* coily) override;
	};


};

