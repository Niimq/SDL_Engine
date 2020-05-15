#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	delete m_pBackButton;
	m_pBackButton = nullptr;

	delete m_pNextButton;
	m_pNextButton = nullptr;

	
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();


	// handle player movement
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
		m_playerFacingRight = false;
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
		m_playerFacingRight = true;
	}
	else
	{
		if(m_playerFacingRight)
		{
			m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
		}
		else
		{
			m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
		}
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Plane Sprite
	m_pPlaneSprite = new PlaneSprite();
	addChild(m_pPlaneSprite);

	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_playerFacingRight = true;

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(300.0f, 400.0f);
	m_pBackButton->addEventListener(CLICK, [&](Button* button)-> void
	{
		button->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&](Button* button)->void
	{
		button->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&](Button* button)->void
	{
		button->setAlpha(255);
	});
	addChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(500.0f, 400.0f);
	m_pNextButton->addEventListener(CLICK, [&](Button* button)-> void
	{
		button->setActive(false);
		TheGame::Instance()->changeSceneState(END_SCENE);
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&](Button* button)->void
	{
		button->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&](Button* button)->void
	{
		button->setAlpha(255);
	});

	addChild(m_pNextButton);
}
