#pragma once
#include "CoilyState.h"
namespace dae 
{

	class EggState : public CoilyState
	{

		public:
		EggState(GameObject* const pParent);
		virtual ~EggState();
		EggState(const EggState& other) = delete;
		EggState(EggState&& other) = delete;
		EggState& operator=(const EggState& other) = delete;
		EggState& operator=(EggState&& other) = delete;

		CoilyStateEnum GetNextState(Coily* coily) override;
		
		void Update(Coily* coily) override;

		private:
			float m_JumpInterval;
			float m_JumpTimer;
			float m_StateChangeDelay;
			float m_StateTimer;

			unsigned int jumpSoundId{UINT32_MAX};
		
	};

};

