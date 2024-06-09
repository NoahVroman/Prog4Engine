#include "StartScreenSelection.h"
#include "GameObject.h"
#include "TransfomComponent.h"
#include "SceneManager.h"
#include "RoundManager.h"

namespace dae
{
	StartScreenSelection::StartScreenSelection(GameObject* const Parent, GameObject*selectionArrow,float buttonDistance)
		: Component(Parent)
		, m_pParent(Parent)
		, m_ButtonDistance(buttonDistance)
		, m_SelectedIndex(0)
		, m_SelectArrow(selectionArrow)
	{
	}

	void StartScreenSelection::MoveUp()
	{
		if (m_SelectedIndex > 0)
		{
			--m_SelectedIndex;
			m_SelectArrow->GetTransform()->SetLocalPosition(glm::vec2{ m_SelectArrow->GetTransform()->GetLocalPosition().x ,m_SelectArrow->GetTransform()->GetLocalPosition().y - m_ButtonDistance });
		
		}
	}

	void StartScreenSelection::MoveDown()
	{
		if (m_SelectedIndex < 2)
		{
			++m_SelectedIndex;
			m_SelectArrow->GetTransform()->SetLocalPosition(glm::vec2{ m_SelectArrow->GetTransform()->GetLocalPosition().x ,m_SelectArrow->GetTransform()->GetLocalPosition().y + m_ButtonDistance });
		}
		
	}

	void StartScreenSelection::Confirm(RoundManager& roundmanager)
	{
		auto& scene = SceneManager::GetInstance();
		switch (m_SelectedIndex)
		{
			case 0:
				scene.ChangeScene(1);
				roundmanager.LoadLevel();

			break;
			case 1:
				 // Scene for coop
				scene.ChangeScene(3);

				roundmanager.ClearRounds();
				roundmanager.SetCurrentRound(0);
				roundmanager.LoadRoundData("Level01CoOp.txt", "CoOpLevel1");
				roundmanager.LoadLevel();

			break;
			case 2:

				 // Scene for versus
				scene.ChangeScene(3);

				roundmanager.ClearRounds();
				roundmanager.SetCurrentRound(0);
				roundmanager.LoadRoundData("Level01Versuz.txt", "VersuzLevel1");
				roundmanager.LoadLevel();
				
			break;
					
		}

	}

}