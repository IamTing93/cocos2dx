#include "GameManager.h"
#include "Global.h"
#include "GameData.h"
#include "FishManager.h"
#include "Player.h"
#include "PropsManager.h"
#include "MusicManager.h"


GameManager::~GameManager() {

}

GameManager* GameManager::getInstance() {
	if (m_gameManager == nullptr) {
		m_gameManager = new GameManager();
		m_gameManager->retain();
		m_gameManager->init();
	}
	return m_gameManager;
}

void GameManager::destroy() {
	if (m_gameManager != nullptr) {
		m_gameManager->release();
	}
}

bool GameManager::init() {
	auto playerUpgradeListener = EventListenerCustom::create(PLAYER_UPGRADE, CC_CALLBACK_1(GameManager::gameGoAhead, this));
	_eventDispatcher->addEventListenerWithFixedPriority(playerUpgradeListener, 1);
	return true;
}

void GameManager::update(float delta) {
	if (m_player->isAlive()) {
		m_fishManager->run();
		m_propsManager->run();

		if (m_timeCounter > PROPS_UPDATE_TIME) {
			m_propsManager->propsAppear();
			m_timeCounter = 0;
		} else {
			m_timeCounter += delta;
		}

	} else {
		gameOver();
	}
}

void GameManager::reset() {
	m_timeCounter = 0;
	m_gameState = 1;
	m_fishManager->reset();
	m_player->reset();
	m_propsManager->reset();
}

void GameManager::gameStart() {
	if (ready()) {
		_eventDispatcher->dispatchCustomEvent(GAME_START, nullptr);
		reset();
		m_player->show();

		MusicManager::playBackgroundMusic();
		_scheduler->scheduleUpdate(this, 1, false);
	}
}

void GameManager::gameOver() {
	_eventDispatcher->dispatchCustomEvent(GAME_OVER, nullptr);
	MusicManager::stopBackgroundMusic();
	MusicManager::playGameOverEffect();
	unscheduleUpdate();
}

void GameManager::gameRestart() {
	reset();
	MusicManager::playBackgroundMusic();
	_eventDispatcher->dispatchCustomEvent(GAME_RESTART, nullptr);
	_scheduler->scheduleUpdate(this, 1, false);
}

void GameManager::gamePause() {
	_eventDispatcher->dispatchCustomEvent(GAME_PAUSE, nullptr);
	Director::getInstance()->pause();
}

void GameManager::gameResume() {
	_eventDispatcher->dispatchCustomEvent(GAME_RESUME, nullptr);
	Director::getInstance()->resume();
}

void GameManager::gameExit() {
	MusicManager::playButtonEffect();
	Director::getInstance()->end();
}

void GameManager::gameGoAhead(Ref* sender) {
	MusicManager::playPlayerUpgradeEffect();
	int playerLevel = m_player->getPlayerLevel();
	int gameState = GAME_STATE_01;
	if (playerLevel <= 3) {
		gameState = GAME_STATE_01;
	} else if (playerLevel <= 7) {
		gameState = GAME_STATE_02;
	} else {
		gameState = GAME_STATE_03;
	}

	if (m_gameState != gameState) {
		m_gameState = gameState;
		m_fishManager->changeFishes(m_gameState);
	}
	
}

GameManager::GameManager() : m_player(nullptr), m_fishManager(nullptr), m_propsManager(nullptr), 
							m_timeCounter(0), m_gameState(1){}

bool GameManager::ready() const {
	do {
		CC_BREAK_IF(m_player == nullptr);
		CC_BREAK_IF(m_fishManager == nullptr);
		CC_BREAK_IF(m_propsManager == nullptr);
		return true;
	} while (0);

	return false;
}

GameManager* GameManager::m_gameManager = nullptr;
