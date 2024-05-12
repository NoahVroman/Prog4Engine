#pragma once
namespace dae 
{
	class Coily;

	class CoilyState
	{
		public:
		enum class CoilyStateEnum
		{
			Egg,
			Snake
		};

		CoilyState(const CoilyStateEnum& state);
		virtual ~CoilyState() = default;
		CoilyState(const CoilyState& other) = delete;
		CoilyState(CoilyState&& other) = delete;
		CoilyState& operator=(const CoilyState& other) = delete;
		CoilyState& operator=(CoilyState&& other) = delete;

		virtual CoilyStateEnum GetNextState(Coily* coily) = 0;

		const CoilyStateEnum& GetState() const { return m_State; }
		
		virtual void Update(Coily* coily) = 0;

		protected:
			CoilyStateEnum m_State;

	};

};

