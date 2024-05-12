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
	//const auto& pos = m_transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);

}


void dae::GameObject::SetParent(GameObject* pParent)
{

	if (m_pParent)
	{
		//Set local position relative to the new parent position
		auto parentTransfrom = m_pParent->GetTransform();
		if (parentTransfrom)
		{
			GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() - parentTransfrom->GetWorldPosition());
		}
	}
	else
	{
		//Local position becomes world position
		GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
	}

	m_pParent = pParent;
}

dae::GameObject::GameObject()
{
	m_pTransformComponent = AddComponent<TransfomComponent>();
}

dae::GameObject::~GameObject()
{

}
