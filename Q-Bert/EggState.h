#pragma once
#include "CoilyState.h"
namespace dae 
{

	class EggState : public CoilyState
	{

		public:
		EggState();
		virtual ~EggState();
		EggState(const EggState& other) = delete;
		EggState(EggState&& other) = delete;
		EggState& operator=(const EggState& other) = delete;
		EggState& operator=(EggState&& other) = delete;

		CoilyStateEnum GetNextState(Coily* coily) override;
		
		void Update(Coily* coily) override;

		
	};

};

