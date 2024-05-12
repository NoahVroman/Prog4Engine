#include "LevelPyramid.h"
#include "GameObject.h"
#include "LevelCube.h"
#include "TransfomComponent.h"

#include <cassert>
#include <algorithm>

dae::LevelPyramid::LevelPyramid(GameObject* const pParent, const PyramidSettings& settings)
	: Component{ pParent }
	, m_Settings{ settings }
	, m_AmountOfCubes{ settings.Rows * (settings.Rows + 1) / 2 }
{

	assert(m_Settings.Level >= 0 && m_Settings.Level <= 3 && "Level is out of range");
	assert(m_Settings.ColorIndex >= 0 && m_Settings.ColorIndex < 6 && "ColorIndex is out of range");
    m_pCubes.reserve(m_AmountOfCubes);
	ContstructPyramid();

    for (auto& cubes : m_pCubes)
    {
        cubes->GetComponent<dae::LevelCube>()->GetSubject().AddObserver(this);
    }

}

dae::LevelPyramid::~LevelPyramid()
{
	RemoveAllCubes();
}
void dae::LevelPyramid::NotifyObserver(Subject* const, Event)
{

    bool isComplete = std::all_of(m_pCubes.begin(), m_pCubes.end(), [&](const std::shared_ptr<GameObject>& pCube)
                                  {
                                      return pCube->GetComponent<dae::LevelCube>()->IsTurned();
                                  });

    if (isComplete)
    {
		m_Subject.Notify(Event::PyramidCompleted);
	}

}
void dae::LevelPyramid::RemoveCube(std::shared_ptr<GameObject> pCube)
{
	auto it = std::find(m_pCubes.begin(), m_pCubes.end(), pCube);
	if (it != m_pCubes.end()) {
		m_pCubes.erase(it);
	}
}
 
void dae::LevelPyramid::RemoveAllCubes()
{
	m_pCubes.clear();
}

glm::vec2 dae::LevelPyramid::GetStartPos(int index) const
{
    	return m_pCubes[index]->GetComponent<dae::LevelCube>()->GetCenter();
}

void dae::LevelPyramid::NextRound()
{
    m_Settings.ColorIndex = (m_Settings.ColorIndex + 1) % 6;

    for (auto& cube : m_pCubes)
    {
        cube->GetComponent<dae::LevelCube>()->SetColorIndex(m_Settings.ColorIndex);
        cube->GetComponent<dae::LevelCube>()->SetTurned(false);
    }
}

void dae::LevelPyramid::ContstructPyramid()
{
    const float halfCubeSize = m_Settings.CubeSize.x * 0.5f;
    const float threeQuartersCubeSize = m_Settings.CubeSize.y * 0.75f;
    auto tempX = m_Settings.StartPos.x;
    auto tempY = m_Settings.StartPos.y;
    auto nrRows = 1;
    auto nrCubes = 0;

    TextureComponent::SpriteInfo spriteInfo{};
    spriteInfo.width = m_Settings.CubeSize.x;
    spriteInfo.height = m_Settings.CubeSize.y;
    spriteInfo.SrcX = m_Settings.ColorIndex * m_Settings.SpriteSize.x;
    spriteInfo.SrcY = 0;
    spriteInfo.SrcWidth = m_Settings.SpriteSize.x;
    spriteInfo.SrcHeight = m_Settings.SpriteSize.y;

    for (auto i = 0; i < m_AmountOfCubes; ++i)
    {
        auto pCube = std::make_shared<GameObject>();
        pCube->AddComponent<dae::LevelCube>(m_Settings.Level, m_Settings.SpriteSize, m_Settings.ColorIndex);
        pCube->AddComponent<TextureComponent>("QbertCubes.png", spriteInfo);
        pCube->GetTransform()->SetLocalPosition(glm::vec2{ tempX,tempY });
        m_pCubes.emplace_back(std::move(pCube));
        ++nrCubes;

        tempX += m_Settings.CubeSize.x;

        if (nrCubes >= nrRows)
        {
            tempY += threeQuartersCubeSize;
            tempX = m_Settings.StartPos.x - halfCubeSize * nrRows;
            nrCubes = 0;
            ++nrRows;
        }
    }

}

