#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include <string>

namespace dae 
{
	class Font;
	class RenderComponent;

	class TextComponent : public Component
	{
		public:
		TextComponent();




		virtual ~TextComponent();

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override; 

		void SetText(const std::string& text);
		//void SetPosition(float x, float y);

		void SetFont(std::shared_ptr<Font> font);
		std::shared_ptr<Font> GetFont() const { return m_Font; }

		private:
			RenderComponent* m_RenderComponent{nullptr};
			std::string m_Text{};
			std::shared_ptr<Font> m_Font{};

			bool m_NeedsUpdate;
	};

}

