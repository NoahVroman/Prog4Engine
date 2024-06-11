#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include <string>

namespace dae 
{
	class Font;
	class GameObject;
	class Texture2D;
	class TextComponent final : public Component
	{
		public:

		TextComponent(GameObject* const pParent,const std::string text,std::shared_ptr<Font> font);
		virtual ~TextComponent();

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Render() const override;
		void Update() override;
		void FixedUpdate() override; 

		void SetText(const std::string& text);
     	void SetFont(std::shared_ptr<Font> font);

		std::shared_ptr<Font> GetFont() const { return m_Font; }

		private:
			std::string m_Text{};
			std::shared_ptr<Font> m_Font{};

			std::shared_ptr<Texture2D> m_TextTexture{};

			bool m_NeedsUpdate{true};
	};

}

