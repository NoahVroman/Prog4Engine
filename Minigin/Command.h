#pragma once

#include <memory>
#include "GameObject.h"
#include "glm/glm.hpp"
#include "MovementComponent.h"
#include <iostream>
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "ButtonComponent.h"

namespace dae 
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand(std::shared_ptr<GameObject> pGameObject) : m_pGameObject(pGameObject) {}
		virtual ~GameObjectCommand() = default;
		virtual void Execute() = 0;

	protected:
		std::shared_ptr<GameObject> GetGameObject() const { return m_pGameObject; }

	private:
		std::shared_ptr<GameObject> m_pGameObject;
	};

	class MoveCommand : public GameObjectCommand
	{
	public:
		MoveCommand(std::shared_ptr<GameObject> pGameObject, const glm::vec2& direction, const float speed) 
			: GameObjectCommand(pGameObject)
			, m_Direction(direction)
			, m_Speed(speed)
		{
		}
		virtual void Execute() override
		{
			if (auto movementComponent = GetGameObject()->GetComponent<MovementComponent>())
			{
				movementComponent->MoveTo(m_Direction, m_Speed);
			}

			std::cout << "MoveCommand executed" << std::endl;
		}

	private:
		glm::vec2 m_Direction;
		float m_Speed;
	};

	class LivesCommand : public GameObjectCommand
	{
	public:
		LivesCommand(std::shared_ptr<GameObject> pGameObject)
			: GameObjectCommand(pGameObject)
		{
		}
		virtual void Execute() override
		{
			if (auto healthComponent = GetGameObject()->GetComponent<HealthComponent>())
			{
				healthComponent->TakeLives(1);
			}

			std::cout << "LivesCommand executed" << std::endl;
		}
	};

	class ScoreCommand : public GameObjectCommand
	{
	public:
		ScoreCommand(std::shared_ptr<GameObject> pGameObject, int score)
			: GameObjectCommand(pGameObject)
			, m_Score(score)
		{
		}
		virtual void Execute() override
		{
			if (auto scoreComponent = GetGameObject()->GetComponent<ScoreComponent>())
			{
				scoreComponent->AddScore(m_Score);
			}
		}

	private:
		int m_Score;
	};

	class Selected : public GameObjectCommand
	{
	public:
		Selected(std::shared_ptr<GameObject> pGameObject)
			: GameObjectCommand(pGameObject)
		{
			m_pButtonComponent = pGameObject->GetComponent<ButtonComponent>();
		}
		virtual void Execute() override
		{
			m_pButtonComponent->Press();
		}

	private:
		ButtonComponent* m_pButtonComponent;
	};

};
