#include "RotatorComponent.h"
#include "TransfomComponent.h"
#include "TextureComponent.h"
dae::RotatorComponent::RotatorComponent(GameObject* parent)
	: Component(parent)
{
	//add a texture component
	//GetOwnerObject()->AddComponent<TextureComponent>("pacman.png");
}

void dae::RotatorComponent::Update()
{
	//auto texture = GetOwnerObject()->GetComponent<TextureComponent>();
	//if (texture != nullptr)
	//{
	//	std::string newTexturePath = "pacman.png";

	//	if (texture->GetFilename() != newTexturePath)
	//	{
	//		texture->SetTexture(newTexturePath);
	//	}
	//}

	//auto transform = GetOwnerObject()->GetComponent<TransfomComponent>();
	//if (transform != nullptr)
	//{


	//}
}

void dae::RotatorComponent::FixedUpdate()
{
}

void dae::RotatorComponent::Render() const
{

}

