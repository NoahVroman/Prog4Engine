#include "Component.h"
#include "GameObject.h"
#include "GameTime.h"
dae::Component::Component(GameObject* const pParent)
	: m_Owner{ pParent }
{
}

dae::Component::~Component()
{

}

