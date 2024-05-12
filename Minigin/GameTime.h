#pragma once
#include <iostream>
class GameTime
{
public:
    static GameTime& Instance() {
        static GameTime instance; // Guaranteed to be destroyed and instantiated on first use.
        return instance;
    }

    float GetDeltaTime() const {
        return deltaTime;
    }

    void SetDeltaTime(float dt) {
        deltaTime = dt;
    }

    static GameTime& GetInstance() {
		return Instance();
	}

   

private:
    float deltaTime;


    GameTime() : deltaTime(0.0f) {} // Private constructor to prevent instantiation.
    GameTime(const GameTime&) = delete; // Delete copy constructor.
    GameTime& operator=(const GameTime&) = delete; // Delete assignment operator.

};

