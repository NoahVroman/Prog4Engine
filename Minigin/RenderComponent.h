#pragma once
#include "Component.h"
#include <string>
#include <memory>

#include <glm/glm.hpp>

namespace dae
{
	class Texture2D;
	class RenderComponent : public Component
	{
		public:
		RenderComponent() = default;
		virtual ~RenderComponent() ;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void Update() override;

		void Render(const glm::vec3& transformPos) const;

		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& texture);

		std::shared_ptr<Texture2D> GetTexture() const { return m_Texture; }

		glm::vec2 GetTextureSize() const;

		private:
			std::shared_ptr<Texture2D> m_Texture;

	};
}


