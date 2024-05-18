#include "CoilyState.h"
#include "Coily.h"

dae::CoilyState::CoilyState(const CoilyStateEnum& state, GameObject* const pParent)
	:m_State{state}
{
	m_pPyramidMovementComponent = pParent->GetComponent<PyramidMovementComponent>();
	m_pTextureComponent = pParent->GetComponent<TextureComponent>();

}
