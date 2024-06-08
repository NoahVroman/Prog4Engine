#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "Component.h"
#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"
namespace dae 
{
	class GameObject;
	class LevelPyramid final : public Component, public Observer
	{
	public:

	

		struct PyramidSettings
		{

			glm::vec2 StartPos;
			int Rows;
			glm::vec2 CubeSize;
			int Level;
			int ColorIndex;
			glm::vec2 SpriteSize;

		};

		LevelPyramid(GameObject* const pParent,const PyramidSettings& settings);
		~LevelPyramid();


		virtual void NotifyObserver(GameObject* const gameObject, Event currentEvent);

		LevelPyramid(const LevelPyramid& other) = delete;
		LevelPyramid(LevelPyramid&& other) = delete;
		LevelPyramid& operator=(const LevelPyramid& other) = delete;
		LevelPyramid& operator=(LevelPyramid&& other) = delete;

		const std::vector<std::shared_ptr<GameObject>>& GetCubes() const { return m_pCubes; }

		void SetSettings(const PyramidSettings& settings) { m_Settings = settings; }

		void Update() override {}
		void Render() const override {};

		void RemoveCube(std::shared_ptr<GameObject> pCube);
		void RemoveAllCubes();

		glm::vec2 GetCubeSize() const { return m_Settings.CubeSize; }
		glm::vec2 GetStartPos(int index) const;
		int GetRows() const { return m_Settings.Rows; }
		Subject& GetSubject() { return m_Subject; }

		glm::vec2 GetPosFirstCubeInRow(int row) const;
		glm::vec2 GetPosLastCubeInRow(int row) const;

		float GetCubeHeight() const { return m_Settings.CubeSize.y; }
		float GetCubeWidth() const { return m_Settings.CubeSize.x; }
		float GetHalfCubeWidth() const { return m_Settings.CubeSize.x * 0.5f; }
		float GetHalfCubeHeight() const { return m_Settings.CubeSize.y * 0.5f; }
		float GetQuarterCubeHeight() const { return m_Settings.CubeSize.y * 0.25f; }
		float GetQuarterCubeWidth() const { return m_Settings.CubeSize.x * 0.25f; }
		float GetThreeQuartersCubeHeight() const { return m_Settings.CubeSize.y * 0.75f; }
		float GetThreeQuartersCubeWidth() const { return m_Settings.CubeSize.x * 0.75f; }

		int GetFirstCubeInRow(int row) const;
		int GetLastCubeInRow(int row) const;

		void NextRound();
		void ContstructPyramid();
		void DestroyPyramid();

		

	private:
		const int m_AmountOfCubes;
		

		PyramidSettings m_Settings;
		GameObject* m_pParent;

		std::vector<std::shared_ptr<GameObject>> m_pCubes;

		Subject m_Subject;



	};
}
