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
		LivesChanged
	
	};


	class Observer
	{

		public:
		virtual ~Observer() = default;
		virtual void NotifyObserver(GameObject* const gameObject, Event currentEvent) = 0;
	};
}

