#include "StartScreenSelection.h"
#include "GameObject.h"
#include "TransfomComponent.h"
#include "SceneManager.h"
#include "ServiceLocator.h"

namespace dae
{
	StartScreenSelection::StartScreenSelection(GameObject* const Parent, GameObject*selectionArrow,float buttonDistance)
		: Component(Parent)
		, m_pParent(Parent)
		, m_ButtonDistance(buttonDistance)
		, m_SelectedIndex(0)
		, m_SelectArrow(selectionArrow)
		, m_SelectionSoundId(UINT32_MAX)
	{



	}

	void StartScreenSelection::MoveUp()
	{
		if (m_SelectedIndex > 0)
		{
			

			if (SceneManager::GetInstance().GetCurrentSceneIndex() == 0)
			{
				ServiceLocator::GetSoundSystem().Play(8, 100);

			}


			--m_SelectedIndex;
			m_SelectArrow->GetTransform()->SetLocalPosition(glm::vec2{ m_SelectArrow->GetTransform()->GetLocalPosition().x ,m_SelectArrow->GetTransform()->GetLocalPosition().y - m_ButtonDistance });
		
		}
	}

	void StartScreenSelection::MoveDown()
	{
		if (m_SelectedIndex < 2)
		{
		
			if (SceneManager::GetInstance().GetCurrentSceneIndex() == 0)
			{
				ServiceLocator::GetSoundSystem().Play(8, 100);

			}


			++m_SelectedIndex;
			m_SelectArrow->GetTransform()->SetLocalPosition(glm::vec2{ m_SelectArrow->GetTransform()->GetLocalPosition().x ,m_SelectArrow->GetTransform()->GetLocalPosition().y + m_ButtonDistance });
		}
		
	}

	void StartScreenSelection::Confirm()
	{
		auto& scene = SceneManager::GetInstance();
		switch (m_SelectedIndex)
		{
			case 0:
				scene.ChangeScene(3);
		
			break;
			case 1:
				scene.ChangeScene(12);
			break;
			case 2:

				scene.ChangeScene(21);
			break;
					
		}
	}

}