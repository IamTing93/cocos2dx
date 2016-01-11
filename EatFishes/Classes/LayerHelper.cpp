#include "LayerHelper.h"
#include "GameManager.h"
#include "Global.h"


LayerHelper::LayerHelper() :
m_currentTiTle(nullptr), m_currentMenu(nullptr),
m_labelGameOver(nullptr), m_menuGameOver(nullptr),
m_labelGamePause(nullptr), m_menuGamePause(nullptr),
m_spriteGameStart(nullptr), m_menuGameStart(nullptr)
{}

LayerHelper::~LayerHelper() {

}

bool LayerHelper::init() {
	if (!Layer::init()) {
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();
	
	m_labelGameOver = Label::createWithSystemFont("Game Over", "Arial", 60);
	m_labelGameOver->setPosition(Point(winSize.width / 2,  winSize.height / 2 + 60.f));
	m_labelGameOver->setVisible(false);
	this->addChild(m_labelGameOver);

	m_labelGamePause = Label::createWithSystemFont("Game Over", "Arial", 60);
	m_labelGamePause->setPosition(Point(winSize.width / 2, winSize.height / 2 + 60.f));
	m_labelGamePause->setVisible(false);
	this->addChild(m_labelGamePause);

	m_spriteGameStart = Sprite::create("scene_start_title.png");
	m_spriteGameStart->setPosition(Point(winSize.width / 2, winSize.height / 2 + 60.f));
	m_spriteGameStart->setVisible(false);
	this->addChild(m_spriteGameStart);

	initMenuItems();

	return true;
}

void LayerHelper::show(int layerType) {
	do {
		CC_BREAK_IF(m_currentTiTle == nullptr);
		m_currentTiTle->setVisible(false);

		CC_BREAK_IF(m_currentMenu == nullptr);
		m_currentMenu->setVisible(false);

	} while (0);
	this->setVisible(true);

	checkLayerType(layerType);
	m_currentTiTle->setVisible(true);
	m_currentMenu->setVisible(true);

	showTiTle(m_currentTiTle);
	showMenuItems(m_currentMenu);
}

void LayerHelper::hide() {
	this->setVisible(false);
}

void LayerHelper::initMenuItems() {
	auto winSize = Director::getInstance()->getWinSize();

	// 退出
	auto labelGameExit1 = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "Exit");
	auto itemGameExit1 = MenuItemLabel::create(labelGameExit1, CC_CALLBACK_1(LayerHelper::menuCallbackExit, this));

	auto labelGameExit2 = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "Exit");
	auto itemGameExit2 = MenuItemLabel::create(labelGameExit2, CC_CALLBACK_1(LayerHelper::menuCallbackExit, this));

	auto labelGameExit3 = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "Exit");
	auto itemGameExit3 = MenuItemLabel::create(labelGameExit3, CC_CALLBACK_1(LayerHelper::menuCallbackExit, this));

	// 重新开始
	auto labelGameRestart1 = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "restart");
	auto itemGameRestart1 = MenuItemLabel::create(labelGameRestart1, CC_CALLBACK_1(LayerHelper::menuCallbackRestart, this));

	auto labelGameRestart2 = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "restart");
	auto itemGameRestart2 = MenuItemLabel::create(labelGameRestart2, CC_CALLBACK_1(LayerHelper::menuCallbackRestart, this));
	// 继续
	auto labelGameContinue = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "continue");
	auto itemGameContinue = MenuItemLabel::create(labelGameContinue, CC_CALLBACK_1(LayerHelper::menuCallbackResume, this));

	// 开始
	auto labelGameStart = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "start");
	auto itemGameStart = MenuItemLabel::create(labelGameStart, CC_CALLBACK_1(LayerHelper::menuCallbackStart, this));

	// --------
	m_menuGameOver = Menu::create(itemGameRestart1, itemGameExit1, NULL);
	m_menuGameOver->alignItemsVertically();
	
	m_menuGameOver->setPosition(Point(winSize.width / 2, winSize.height / 2));
	m_menuGameOver->setVisible(false);
	addChild(m_menuGameOver);

	// --------
	m_menuGamePause = Menu::create(itemGameContinue, itemGameRestart2, itemGameExit2, NULL);
	m_menuGamePause->alignItemsVertically();

	m_menuGamePause->setPosition(Point(winSize.width / 2, winSize.height / 2));
	m_menuGamePause->setVisible(false);
	addChild(m_menuGamePause);
	

	// ---------
	m_menuGameStart = Menu::create(itemGameStart, itemGameExit3, NULL);
	m_menuGameStart->alignItemsVertically();
	m_menuGameStart->setVisible(false);
	addChild(m_menuGameStart);
}

void LayerHelper::checkLayerType(int labelType) {

	switch (labelType) {
	case OVER:
		m_currentTiTle = m_labelGameOver;
		m_currentMenu = m_menuGameOver;
		break;

	case PAUSE:
		m_currentTiTle = m_labelGamePause;
		m_currentMenu = m_menuGamePause;
		break;

	case START:
		m_currentTiTle = m_spriteGameStart;
		m_currentMenu = m_menuGameStart;
		break;

	default:
		break;
	}
}

void LayerHelper::showMenuItems(Menu* menu) {
	auto winSize = Director::getInstance()->getWinSize();

	int i = 0;
	for (const auto &child : menu->getChildren()) {
		auto dstPoint = child->getPosition();
		int offset = (int)(winSize.width / 2 + 50);
		if (i % 2 == 0) {
			offset = -offset;
		}

		child->setPosition(Point(dstPoint.x + offset, dstPoint.y));
		child->runAction(
			Sequence::create(
				DelayTime::create(2.0f),
				EaseElasticOut::create(MoveBy::create(2, Point(- offset, 0)), 0.35f),
				NULL
				)
			);
		i++;
	}
}

void LayerHelper::showTiTle(Node* titleNode) {
	titleNode->setScale(0);
	titleNode->runAction(ScaleTo::create(2.0f, 1.0f));
}

void LayerHelper::menuCallbackRestart(Ref* sender) {
	GameManager::getInstance()->gameRestart();
}

void LayerHelper::menuCallbackResume(Ref* sender) {
	GameManager::getInstance()->gameResume();
}

void LayerHelper::menuCallbackExit(Ref* sender) {
	GameManager::getInstance()->gameExit();
}

void LayerHelper::menuCallbackStart(Ref* sender) {
	GameManager::getInstance()->gameStart();
}
