#include "LevelManager.h"
#include <iostream>
#include "GameTime.h"
#include "LevelCube.h"
#include "SceneManager.h"
#include "Qbert.h"
#include "Coily.h"
#include "UggWrongWay.h"
#include "SlickSam.h"
#include "LevelPyramid.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "CoilyCommands.h"
#include "QbertCommands.h"

dae::LevelManager::LevelManager(GameObject* const pParent, LevelPyramid* pyramid, std::vector<std::shared_ptr<GameObject>> pQbert)
    : Component(pParent)
    , m_Pyramid{ pyramid }
    , m_pQbert{ pQbert }
    , m_AnimationTimer{ 0 }
    , m_MaxAnimationTime{ 2.f }
    , m_FlashingTimer{ 0 }
    , m_MaxFlashingTime{ 0.07f }
    , m_CurrentColor{ 1 }
    , m_RoundWon{ false }
    , m_SlickSamSpawnTimer{ 0 }
    , m_UggWrongWaySpawnTimer{ 0 }
    , m_SpawnSlickSams{ false }
    , m_SpawnUggWrongs{ false }
    , m_SlickSamsSpawnInterval{ 0 }
    , m_UggWrongSpawnInterval{ 0 }
    ,m_pParent{pParent}
    ,m_GameMode{0}
    ,m_CurrentRound{0}
    ,m_SpawnCoily{false}
    , m_CoilySpawnMaxTime{ 5.f }
    ,m_CoilySpawnTimer{0}
    ,m_pCoily{nullptr}


{

    m_Pyramid->GetSubject().AddObserver(this);

    for (auto& qbert : m_pQbert)
    {
        qbert->GetComponent<Qbert>()->GetSubject().AddObserver(this);

    }

    ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/QBertJump.wav");


}

void dae::LevelManager::InitializeRound(int level,int currentRound ,bool spawnSlickSams, bool spawnUggWrongs, float slickSamsSpawnInterval, float uggWrongSpawnInterval, int gameMode)
{
    m_CurrentLevel = level;
    m_CurrentRound = currentRound;
    m_SpawnSlickSams = spawnSlickSams;
    m_SpawnUggWrongs = spawnUggWrongs;
    m_SlickSamsSpawnInterval = slickSamsSpawnInterval;
    m_UggWrongSpawnInterval = uggWrongSpawnInterval;
    m_SlickSamSpawnTimer = 0;
    m_UggWrongWaySpawnTimer = 0;
    m_GameMode = gameMode;
}

void dae::LevelManager::NotifyObserver(GameObject* const obj, Event currentEvent)
{
    switch (currentEvent) {
    case Event::CubeChanged:
        // Handle CubeChanged event if necessary
        break;
    case Event::PyramidCompleted:
        m_RoundWon = true;
        break;
    case Event::RoundWon:
        HandleRoundWon();
        break;
    case Event::QbertDied:
        if (auto qbertComponent = obj->GetComponent<Qbert>()) {
            qbertComponent->SetDeath(true);
        }
        else {
            for (auto& qbert : m_pQbert) {
                if (auto qbertComp = qbert->GetComponent<Qbert>()) {
                    qbertComp->SetDeath(true);
                }
            }
        }

        // Clear enemies upon Qbert's death
        for (auto& slicksams : m_SlickSams) {
            slicksams->Destroy();
        }
        m_SlickSams.clear();

        for (auto& uggWrongWay : m_UggWrongWays) {
            uggWrongWay->Destroy();
        }
        m_UggWrongWays.clear();

        if (m_pCoily) {
            m_pCoily->Destroy();
        }
        m_SpawnCoily = false;
        m_CoilySpawnTimer = 0;
        m_UggWrongWaySpawnTimer = 0;
        m_SlickSamSpawnTimer = 0;
        break;

    case Event::UggWrongWayDied:
    case Event::CoilyDied:
    case Event::SlickSamDied:
        obj->Destroy();
        break;

    case Event::QbertJumped: {
        unsigned int JumpSoundIndex{};
        if (JumpSoundIndex == UINT32_MAX) {
            JumpSoundIndex = ServiceLocator::GetSoundSystem().GetSoundIndex("../Data/Sounds/QBertJump.wav");
        }
        ServiceLocator::GetSoundSystem().Play(JumpSoundIndex, 10);
        break;
    }

    default:
        break;
    }
}

void dae::LevelManager::Update()
{
    float deltaTime = GameTime::GetInstance().GetDeltaTime();

 


    if (!m_SpawnCoily)
    {
		m_CoilySpawnTimer += deltaTime;
        if (m_CoilySpawnTimer >= m_CoilySpawnMaxTime)
        {
			SpawnCoily();
			m_CoilySpawnTimer = 0;
            m_SpawnCoily = true;
		}
	}

    //SPAWNING DISKS ON A RANDOM ROW BUT NOT ON THE LAST ROW

    if (m_RoundWon)
    {
        for (auto& qbert : m_pQbert)
        {
            qbert->GetComponent<Qbert>()->SetFrozen(true);

        }
        UpdateFlashingAnimation(deltaTime);
    }

    if (m_SpawnSlickSams)
    {
        m_SlickSamSpawnTimer += deltaTime;
        if (m_SlickSamSpawnTimer >= m_SlickSamsSpawnInterval)
        {
            SpawnSlickSam();
            m_SlickSamSpawnTimer = 0;
        }

    }

    if (m_SpawnUggWrongs)
    {
        m_UggWrongWaySpawnTimer += deltaTime;
        if (m_UggWrongWaySpawnTimer >= m_UggWrongSpawnInterval)
        {
            SpawnUggWrongWay();
            m_UggWrongWaySpawnTimer = 0;
        }
    }
}

void dae::LevelManager::HandleRoundWon()
{
    m_RoundWon = false;
    m_AnimationTimer = 0;
    m_FlashingTimer = 0;
    m_CurrentColor = 1;
    ResetLevel();

    SceneManager::GetInstance().ChangeScene(SceneManager::GetInstance().GetCurrentSceneIndex() + 1);
}



void dae::LevelManager::UpdateFlashingAnimation(float deltaTime)
{
    m_AnimationTimer += deltaTime;
    m_FlashingTimer += deltaTime;

    if (m_AnimationTimer < m_MaxAnimationTime)
    {
        if (m_FlashingTimer >= m_MaxFlashingTime)
        {
            for (auto& cube : m_Pyramid->GetCubes())
            {
                if (m_CurrentColor == 1)
                    cube->GetComponent<LevelCube>()->ChangeToSecondColor();
                else if (m_CurrentColor == 2)
                    cube->GetComponent<LevelCube>()->ChangeToThirdColor();
                else
                    cube->GetComponent<LevelCube>()->ChangeToFirstColor();
            }
            m_CurrentColor = (m_CurrentColor % 3) + 1;
            m_FlashingTimer = 0.f;
        }
    }
    else
    {
        m_Pyramid->GetSubject().Notify(Event::RoundWon,m_pParent);
    }
}

void dae::LevelManager::ResetLevel()
{
   

    for (auto& uggWrongWay : m_UggWrongWays)
    {
        uggWrongWay->Destroy();
    }
    m_UggWrongWays.clear();

    for (auto& slickSam : m_SlickSams)
    {
        slickSam->Destroy();
    }
    m_SlickSams.clear();

    for (auto& qberts : m_pQbert)
    {

        qberts->GetComponent<Qbert>()->SetFrozen(false);
        qberts->GetComponent<Qbert>()->Reset();

    }


}

void dae::LevelManager::SpawnSlickSam()
{


    auto slickSam = std::make_shared<GameObject>();
    slickSam->AddComponent<SlickSam>(m_Pyramid, m_pQbert[0]->GetComponent<Qbert>(), 1, 1);
    dae::SceneManager::GetInstance().GetCurrentScene()->Add(slickSam);
    slickSam->GetComponent<SlickSam>()->GetSubject().AddObserver(this);
    m_SlickSams.push_back(slickSam.get());
}

void dae::LevelManager::SpawnUggWrongWay()
{
    auto uggWrongWay = std::make_shared<GameObject>();
    uggWrongWay->AddComponent<UggWrongWay>(m_pQbert, m_Pyramid ,6, true);
    dae::SceneManager::GetInstance().GetCurrentScene()->Add(uggWrongWay);
    uggWrongWay->GetComponent<UggWrongWay>()->GetSubject().AddObserver(this);
    m_UggWrongWays.push_back(uggWrongWay.get());
}

void dae::LevelManager::SpawnCoily()
{
    if (m_GameMode == 3)
    {
        auto coily = std::make_shared<GameObject>();
        coily->AddComponent<Coily>(m_pQbert, m_Pyramid, 2, 1,true);
        coily->GetComponent<Coily>()->GetSubject().AddObserver(this);
        dae::SceneManager::GetInstance().GetCurrentScene()->Add(coily);
        m_pCoily = coily.get();

        InputManager::GetInstance().ClearBindings();

        InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_D, InputType::DownThisFrame, MoveDownRightCommand(m_pQbert[0]));
        InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_S, InputType::DownThisFrame, MoveDownLeftCommand(m_pQbert[0]));
        InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_A, InputType::DownThisFrame, MoveUpLeftCommand(m_pQbert[0]));
        InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_W, InputType::DownThisFrame, MoveUpRightCommand(m_pQbert[0]));


        InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_RIGHT, InputType::DownThisFrame, MoveDownRightCommandCoily(coily));
        InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_DOWN, InputType::DownThisFrame, MoveDownLeftCommandCoily(coily));
        InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_LEFT, InputType::DownThisFrame, MoveUpLeftCommandCoily(coily));
        InputManager::GetInstance().BindKeyboardAction(SDL_SCANCODE_UP, InputType::DownThisFrame, MoveUpRightCommandCoily(coily));



    }
    else
    {
        auto coily = std::make_shared<GameObject>();
        coily->AddComponent<Coily>(m_pQbert, m_Pyramid, 2, 1,false);
        coily->GetComponent<Coily>()->GetSubject().AddObserver(this);
        dae::SceneManager::GetInstance().GetCurrentScene()->Add(coily);
        m_pCoily = coily.get();

    }

}

