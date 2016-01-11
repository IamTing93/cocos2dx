#include "GameLayer.h"
#include "FishManager.h"
#include "Player.h"
#include "LayerHelper.h"
#include "GameManager.h"
#include "Global.h"
#include "PropsManager.h"
#include "MusicManager.h"
#include "HintLayer.h"

GameLayer::GameLayer() : m_layerHelper(nullptr) {

}

GameLayer::~GameLayer() {
	GameManager::destroy();
}

Scene* GameLayer::createScene() {
	auto scene = Scene::create();
	auto layer = GameLayer::create();

	scene->addChild(layer);
	return scene;
}

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	initEventListener();

	Size winsize = Director::getInstance()->getWinSize();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto visibleOrigin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("bg01.png");
	backgroundSprite->setPosition(winsize.width / 2, winsize.height / 2);
	float scaleTimes = visibleSize.width / backgroundSprite->getContentSize().width;
	backgroundSprite->setScale(scaleTimes);
	this->addChild(backgroundSprite);


	auto player = Player::create();
	player->setAnchorPoint(Point(0.5f, 0.5f));
	player->setPosition(winsize.width / 2, winsize.height / 2);
	this->addChild(player);
	player->hide();

	auto fishManager = FishManager::create();
	this->addChild(fishManager);
	fishManager->bindPlayer(player);

	auto propsManager = PropsManager::create();
	this->addChild(propsManager);

	GameManager* manager = GameManager::getInstance();
	manager->setPlayer(player);
	manager->setFishManager(fishManager);
	manager->setPropsManager(propsManager);

	m_layerHelper = LayerHelper::create();
	this->addChild(m_layerHelper, 3);

	m_layerHelper->show(START);
	MusicManager::playGameStartEffect();

	auto hintLayer = HintLayer::create();
	this->addChild(hintLayer);

	return true;
}

void GameLayer::initEventListener() {
	auto gameStartListener = EventListenerCustom::create(GAME_START, CC_CALLBACK_1(GameLayer::EventGameStart, this));
	_eventDispatcher->addEventListenerWithFixedPriority(gameStartListener, 1);

	auto gameOverListener = EventListenerCustom::create(GAME_OVER, CC_CALLBACK_1(GameLayer::EvnetGameOver, this));
	_eventDispatcher->addEventListenerWithFixedPriority(gameOverListener, 1);

	auto gameRestartListener = EventListenerCustom::create(GAME_RESTART, CC_CALLBACK_1(GameLayer::EventGameRestart, this));
	_eventDispatcher->addEventListenerWithFixedPriority(gameRestartListener, 1);

	auto gamePauseListener = EventListenerCustom::create(GAME_OVER, CC_CALLBACK_1(GameLayer::EventGamePause, this));
	_eventDispatcher->addEventListenerWithFixedPriority(gamePauseListener, 1);

	auto gameResumeListener = EventListenerCustom::create(GAME_OVER, CC_CALLBACK_1(GameLayer::EventGameResume, this));
	_eventDispatcher->addEventListenerWithFixedPriority(gameResumeListener, 1);
}

void GameLayer::EventGameStart(Ref* sender) {
	if (m_layerHelper != nullptr && m_layerHelper->isVisible()) {
		m_layerHelper->hide();
	}
}

void GameLayer::EvnetGameOver(Ref* sender) {
	m_layerHelper->show(OVER);
}

void GameLayer::EventGameRestart(Ref* sender) {
	if (m_layerHelper != nullptr && m_layerHelper->isVisible()) {
		m_layerHelper->hide();
	}
}

void GameLayer::EventGamePause(Ref* sender) {

}

void GameLayer::EventGameResume(Ref* sender) {

}
