#pragma once
#include "Component.h"
#include "GameObject.h"
#include <glm/glm.hpp>
#include "TextureComponent.h"
#include "TransfomComponent.h"
#include "Subject.h"


namespace dae
{
	class LevelCube final : public Component
	{
	public:
		LevelCube(GameObject* pParent, int level, const glm::vec2& size , int colorIndex);
		~LevelCube() = default;

		LevelCube(const LevelCube& other) = delete;
		LevelCube(LevelCube&& other) noexcept = delete;
		LevelCube& operator=(const LevelCube& other) = delete;
		LevelCube& operator=(LevelCube&& other) noexcept = delete;

		void Update() override {};
		void Render() const override{};
		void FixedUpdate() override {};

		glm::vec2 GetCenter() const;

		Subject& GetSubject() { return m_Subject; }

		void ChangeColor();

		bool IsTurned() const { return m_Turned; }

		void ChangeToFirstColor();
		void ChangeToSecondColor();
		void ChangeToThirdColor();

		void SetColorIndex(int index) { m_ColorIndex = index; }

		void SetTurned(bool turned) { m_Turned = turned; }
		void SetHalfTurned(bool halfTurned) { m_HalfTurned = halfTurned; }

	private:
		int m_Level;  
		glm::vec2 m_Size;
		int m_ColorIndex;

		bool m_Turned;
		bool m_HalfTurned;

		Subject m_Subject;

	};

}

