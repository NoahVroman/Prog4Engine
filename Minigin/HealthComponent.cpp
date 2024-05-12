#include "HealthComponent.h"
#include "GameObject.h"

dae::HealthComponent::HealthComponent(GameObject* const pParent, int lives)
	: Component(pParent)
	, m_MaxLives( lives )
{
	m_Lives = m_MaxLives;
}




void dae::HealthComponent::TakeLives(int damage)
{
	if (GetOwnerObject()->IsDestroyed())
	{
				return;
	}

	SetLives(m_Lives - damage);

	if (m_Lives <= 0)
	{

	}
	else if (m_Lives > m_MaxLives)
	{
		SetLives(m_MaxLives);
	}



}
