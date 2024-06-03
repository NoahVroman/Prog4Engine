#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameTime.h"
#include "Component.h"
#include "TransfomComponent.h"


void dae::GameObject::Update()
{
	for (auto& component : components)
	{
		component->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (auto& component : components)
	{
		component->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : components)
	{
		component->Render();
	}

}


void dae::GameObject::AddChild(GameObject* pChild)
{
    if (!pChild || pChild == this || pChild->m_pParent == this)
    {
        // Invalid child, return early
        return;
    }

    // 2. Update position, rotation, and scale if needed
     pChild->GetTransform()->SetLocalPosition(pChild->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition());

    // 3. Remove the given child from the child's previous parent
    if (pChild->m_pParent)
    {
        pChild->m_pParent->RemoveChild(pChild);
    }

    // 4. Set itself as parent of the child
    pChild->m_pParent = this;

    // 5. Add the child to its children list
    m_pChildren.push_back(pChild);
}

void dae::GameObject::RemoveChild(GameObject* pChild)
{
    // 1. Check if the child is valid (not null) and not one of its parents
    if (!pChild || pChild == this || pChild->m_pParent != this)
    {
        // Invalid child or not a child of this GameObject, return early
        return;
    }

    // 2. Update position, rotation, and scale if needed
    pChild->GetTransform()->SetLocalPosition(pChild->GetTransform()->GetWorldPosition() + GetTransform()->GetWorldPosition());

    // 3. Set the parent of the child to nullptr
    pChild->m_pParent = nullptr;

    // 4. Remove the child from its previous parent's children list
    auto& siblings = m_pChildren;
    siblings.erase(std::remove(siblings.begin(), siblings.end(), pChild), siblings.end());
}

void dae::GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{

    if (pParent == this || IsDescendantOf(pParent) || m_pParent == pParent)
    {
        return;
    }

    if (keepWorldPosition)
    {
        if (pParent)
        {
            GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() - pParent->GetTransform()->GetWorldPosition());
        }
        else
        {
			GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
		}

    }

    if (m_pParent)
    {
        m_pParent->RemoveChild(this);
    }

    m_pParent = pParent;

    if (m_pParent)
    {
        m_pParent->AddChild(this);
    }

}

dae::GameObject::GameObject()
{
	m_pTransformComponent = AddComponent<TransfomComponent>();
}

dae::GameObject::~GameObject()
{


}

bool dae::GameObject::IsDescendantOf(GameObject* potentialAncestor) const
{
	GameObject* current = m_pParent;
	while (current)
	{
		if (current == potentialAncestor)
			return true;
		current = current->m_pParent;
	}
	return false;
}
