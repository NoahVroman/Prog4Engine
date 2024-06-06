#pragma once
#include "Observer.h"
#include <vector>
#include <unordered_map>
namespace dae
{
    class GameObject;
	class Subject
	{
		public:
            Subject() = default;
            virtual ~Subject() = default;
            void AddObserver(Observer* const pObserver)
            {
                m_Observers.push_back(pObserver);
            }

            void RemoveObserver(Observer* const pObserver)
            {
              
                m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), pObserver), m_Observers.end());
            }

            void Notify(Event currentEvent,GameObject* gameobject)
            {
                
                for (auto& observer : m_Observers)
                {
                    observer->NotifyObserver(gameobject, currentEvent);
                }
            }
	private:
        std::vector<Observer*> m_Observers;

	};

}

