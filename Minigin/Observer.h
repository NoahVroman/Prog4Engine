#pragma once
namespace dae
{
	class Subject;
	enum class Event
	{
		CubeChanged,
		PyramidCompleted,
		RoundWon,
		LevelCompleted,
		QbertDied,
		ScoreUpdated,
		LivesChanged
	
	};


	class Observer
	{

		public:
		virtual ~Observer() = default;
		virtual void NotifyObserver(Subject* const gameObject, Event currentEvent) = 0;
	};
}

