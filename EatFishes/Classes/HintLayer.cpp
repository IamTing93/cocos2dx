#include "HintLayer.h"
#include "GameData.h"
#include "Global.h"
#include "GameManager.h"
#include "Player.h"


HintLayer::HintLayer() {

}

HintLayer::~HintLayer() {

}

bool HintLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();
	Point startPoint = Point(20, winSize.height - 50.0f);
	float width = 10.0f;
	float gap = width + 30.0f;
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("fish.plist", "fish.png");

	for (int i = 1; i <= MAX_LEVEL; ++i) {
		auto frame = frameCache->getSpriteFrameByName(StringUtils::format("fish0%d_10.png", i));
		auto sprite = Sprite::createWithSpriteFrame(frame);
		sprite->setScale(1 - i / 10.0f + 0.2f);
		sprite->setPosition(startPoint.x + (width + gap) * (i - 1), startPoint.y);
		this->addChild(sprite);
		m_fishesHint.pushBack(sprite);
	}

	m_labelHint = Label::createWithSystemFont("can eat: ", "Arial", 20);
	m_labelHint->setAnchorPoint(Point(0.5f, 0.5f));
	m_labelHint->setPosition(Point(40.0f, winSize.height - 30.0f));
	this->addChild(m_labelHint);

	_eventDispatcher->addCustomEventListener(PLAYER_UPGRADE, CC_CALLBACK_1(HintLayer::updateHint, this));
	_eventDispatcher->addCustomEventListener(GAME_RESTART, CC_CALLBACK_1(HintLayer::gameRestart, this));
	_eventDispatcher->addCustomEventListener(GAME_START, CC_CALLBACK_1(HintLayer::gameStart, this));
	_eventDispatcher->addCustomEventListener(GAME_OVER, CC_CALLBACK_1(HintLayer::gameOver, this));

	hide();
	return true;
}

void HintLayer::reset() {
	for (auto sprite : m_fishesHint) {
		sprite->setVisible(false);
	}
	m_fishesHint.at(0)->setVisible(true);
}

void HintLayer::show() {
	this->setVisible(true);
}

void HintLayer::hide() {
	this->setVisible(false);
}

void HintLayer::gameRestart(Ref* sender) {
	this->show();
	reset();
}

void HintLayer::updateHint(Ref* sender) {
	int playerLevel = GameManager::getInstance()->getPlayer()->getPlayerLevel();
	for (int i = 1; i < playerLevel; ++i) {
		m_fishesHint.at(i)->setVisible(true);
	}
}

void HintLayer::gameStart(Ref* sender) {
	this->show();
	reset();
}

void HintLayer::gameOver(Ref* sender) {
	hide();
}
