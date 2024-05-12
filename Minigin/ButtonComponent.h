#pragma once
#include "Component.h"
#include "Subject.h"
#include "TextComponent.h"
#include <memory>
#include "GameObject.h"
namespace dae 
{
	class ButtonComponent final : public Component, public Subject
	{
	public:
		ButtonComponent(GameObject* const pParent,const std::string& text, std::shared_ptr<Font> font);
 		~ButtonComponent();
		void Update() override;
		void Render() const override;
		void FixedUpdate() override;


		void Selected();
		void Deselected();
		void Press();


		

	private:

		bool m_IsSelected{false};

		TextComponent* m_pTextComponent;

	};

};

