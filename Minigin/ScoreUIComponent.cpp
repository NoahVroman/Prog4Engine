#include "ScoreUIComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "ScoreComponent.h"

dae::ScoreUIComponent::ScoreUIComponent(GameObject* const pParent, int ) : Component(pParent)

{
}


void dae::ScoreUIComponent::NotifyObserver(GameObject* const , Event )
{
}

void dae::ScoreUIComponent::UpdateText(int )
{
}
