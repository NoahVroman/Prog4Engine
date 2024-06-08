#include "LevelCube.h"

dae::LevelCube::LevelCube(GameObject* pParent, int level, const glm::vec2& size, int colorIndex)
	: Component(pParent)
	, m_Level(level)
	, m_Size(size)
	, m_ColorIndex(colorIndex)
	, m_Turned(false)
	, m_HalfTurned(false)
	,m_pParent(pParent)
{
}

glm::vec2 dae::LevelCube::GetCenter() const
{
	return glm::vec2{ GetOwnerObject()->GetTransform()->GetLocalPosition().x + m_Size.x * 0.5f,
					  GetOwnerObject()->GetTransform()->GetLocalPosition().y - m_Size.y * 0.5f };
}

void dae::LevelCube::ChangeColor()
{
	if (!m_Turned)
	{
		if (m_Level == 1)
		{
			ChangeToSecondColor();
			m_Turned = true;
		}
		else if (m_Level == 2)
		{
			if (m_HalfTurned)
			{
				ChangeToThirdColor();
				m_Turned = true;
			}
			else
			{
				ChangeToSecondColor();
				m_HalfTurned = true;
			}
		}
		else if (m_Level == 3 )
		{
			ChangeToFirstColor();
			m_HalfTurned = false;
			m_Turned = false;

		}
		else
		{
			ChangeToSecondColor();
			m_Turned = true;

		}

	}
	m_Subject.Notify(Event::CubeChanged,m_pParent);

}

void dae::LevelCube::RevertColor()
{
	if (m_Turned)
	{
		if (m_Level == 1)
		{
			ChangeToFirstColor();
		}
		else if (m_Level == 2)
		{
			if (m_HalfTurned)
			{
				ChangeToFirstColor();
				m_HalfTurned = false;
			}
			else
			{
				ChangeToSecondColor();
			}

			ChangeToSecondColor();
			m_HalfTurned = true;
		}

		m_Turned = false;
	}
	else
	{
		if (m_Level == 2)
		{
			if (m_HalfTurned)
			{
				ChangeToFirstColor();
				m_HalfTurned = false;
			}
		}
	}
	m_Subject.Notify(Event::CubeChanged,m_pParent);
}

void dae::LevelCube::ChangeToFirstColor()
{
	GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(float(m_ColorIndex)* m_Size.x,0,m_Size.x,m_Size.y);
}

void dae::LevelCube::ChangeToSecondColor()
{
	GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(float(m_ColorIndex) * m_Size.x, m_Size.y, m_Size.x, m_Size.y);

}

void dae::LevelCube::ChangeToThirdColor()
{
	GetOwnerObject()->GetComponent<TextureComponent>()->SetSourceInfo(float(m_ColorIndex) * m_Size.x, m_Size.y * 2, m_Size.x, m_Size.y);

}

