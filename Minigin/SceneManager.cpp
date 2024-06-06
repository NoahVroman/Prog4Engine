#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Update()
{
	
	m_scenes[m_CurrentScene]->Update();

}

void dae::SceneManager::FixedUpdate()
{

	m_scenes[m_CurrentScene]->FixedUpdate();

}

void dae::SceneManager::Render()
{

	m_scenes[m_CurrentScene]->Render();

}

void dae::SceneManager::CleanUp()
{

	m_scenes[m_CurrentScene]->DeleteDestroyedObjects();

}

void dae::SceneManager::ChangeScene(int newScene)
{

	if (newScene < int(m_scenes.size()))
	{
		m_CurrentScene = newScene;
	}

}


dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
