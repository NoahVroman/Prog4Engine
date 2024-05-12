#include "TransfomComponent.h"
#include "GameObject.h"
#include "TransfomComponent.h"

namespace dae
{
    TransfomComponent::TransfomComponent(GameObject* const pParent) :
        Component(pParent),
        m_LocalPosition{0.0f},
        m_WorldPosition{0.0f}

    {
    
    }

    void TransfomComponent::Render() const {}
    void TransfomComponent::Update() {}
    void TransfomComponent::FixedUpdate() {}

    void TransfomComponent::SetLocalPosition(const glm::vec2& position) {
        m_LocalPosition = position;
        SetDirty();
    }

    void TransfomComponent::SetWorldPosition(const glm::vec2& position) {
        m_WorldPosition = position;
        SetDirty();
    }

    void TransfomComponent::SetScale(const glm::vec2& scale)
    {
        m_Scale = scale;
        SetDirty();
    }


    void TransfomComponent::UpdateTransform() {
        m_IsPositionDirty = false;

        if (GetOwnerObject()->GetParent() == nullptr) {
            m_WorldPosition = m_LocalPosition;
        }
        else {
            auto& parentPos = GetOwnerObject()->GetParent() ? GetOwnerObject()->GetParent()->GetTransform()->GetWorldPosition() : glm::vec2(0.0f);
            m_WorldPosition = parentPos + m_LocalPosition;
        }

        for (auto& child : GetOwnerObject()->GetChildren()) {
            if (child->GetTransform())
                child->GetTransform()->UpdateTransform();
        }
    }


    const glm::vec2& TransfomComponent::GetLocalPosition() const {
        return m_LocalPosition;
    }

    const glm::vec2& TransfomComponent::GetWorldPosition() {
        if (m_IsPositionDirty)
            UpdateTransform();
        return m_WorldPosition;
    }

    void TransfomComponent::SetDirty()
    {
         m_IsPositionDirty = true;
         for (auto& child : GetOwnerObject()->GetChildren()) 
         {
                 child->GetTransform()->SetDirty();
		 }

    }
}
