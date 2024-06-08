#include "HealthUIComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "HealthComponent.h"
#include "Subject.h"
dae::HealthUIComponent::HealthUIComponent(GameObject* const pParent, int )
	: Component(pParent)
{
}


void dae::HealthUIComponent::Render() const
{

}

void dae::HealthUIComponent::Update()
{
}

void dae::HealthUIComponent::FixedUpdate()
{
}

void dae::HealthUIComponent::NotifyObserver(GameObject* const  , Event )
{

}

void dae::HealthUIComponent::UpdateText(int )
{
}
