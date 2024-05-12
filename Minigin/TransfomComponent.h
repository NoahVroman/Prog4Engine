#pragma once
#include "Component.h"
#include <glm/glm.hpp>
namespace dae
{
    class TransfomComponent final : public Component
    {
    public:
        TransfomComponent(GameObject* pParent);

        void Render() const override;
        void Update() override;
        void FixedUpdate() override;

        void SetLocalPosition(const glm::vec2& position);
        void SetWorldPosition(const glm::vec2& position);
        void SetScale(const glm::vec2& scale);

        const glm::vec2& GetLocalPosition() const;
        const glm::vec2& GetWorldPosition();

        void SetDirty();

    private:
        glm::vec2 m_LocalPosition;
        glm::vec2 m_WorldPosition;
        glm::vec2 m_Scale{ 1.0f, 1.0f };
        bool m_IsPositionDirty{ false };

        void UpdateTransform();
	};

}

