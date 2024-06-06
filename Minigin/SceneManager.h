#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		void FixedUpdate();
		void Render();
		void CleanUp();


		std::shared_ptr<Scene> GetCurrentScene()const { return m_scenes[m_CurrentScene]; }
		int GetCurrentSceneIndex()const { return m_CurrentScene; }
		void ChangeScene(int newScene);


	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;

		int m_CurrentScene{0};

	};
}
