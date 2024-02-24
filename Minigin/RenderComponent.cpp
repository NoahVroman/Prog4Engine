#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"

dae::RenderComponent::~RenderComponent()
{
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::Render(const glm::vec3& /*transformPos*/) const
{
	if (!m_Texture)
	{
		return;
	}


}

void dae::RenderComponent::SetTexture(const std::string& /*filename*/)
{
}

void dae::RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& /*texture*/)
{
}

glm::vec2 dae::RenderComponent::GetTextureSize() const
{
	return glm::vec2();
}
