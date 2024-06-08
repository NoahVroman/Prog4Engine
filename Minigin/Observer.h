#pragma once
namespace dae
{
	class Subject;
	class GameObject;
	enum class Event
	{
		CubeChanged,
		PyramidCompleted,
		RoundWon,
		LevelCompleted,
		QbertDied,
		UggWrongWayDied,
		CoilyDied,
		SlickSamDied,
		ScoreUpdated,
		LivesChanged,
		QbertJumped,
		JumpedOnDisk,
		Qbert2Died,
		ScoreGainedP1,
		ScoreGainedP2
	
	};


	class Observer
	{

		public:
		virtual ~Observer() = default;
		virtual void NotifyObserver(GameObject* const gameObject, Event currentEvent) = 0;
	};
}

