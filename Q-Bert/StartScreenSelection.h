#pragma once
#include "Component.h"
namespace dae
{
	class StartScreenSelection : public Component
	{
	public:
		StartScreenSelection(GameObject* const Parent, GameObject* selectionArrow, float buttonDistance);
		virtual ~StartScreenSelection() = default;
		StartScreenSelection(const StartScreenSelection& other) = delete;
		StartScreenSelection(StartScreenSelection&& other) = delete;
		StartScreenSelection& operator=(const StartScreenSelection& other) = delete;
		StartScreenSelection& operator=(StartScreenSelection&& other) = delete;

		void MoveUp();
		void MoveDown();
		void Confirm();

	private:
		int m_SelectedIndex;
		float m_ButtonDistance;
		GameObject* m_pParent;
		GameObject* m_SelectArrow;

		unsigned int m_SelectionSoundId;
	};
};
