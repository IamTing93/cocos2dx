#include "Player.h"
#include "Fish.h"
#include "GameData.h"
#include "GameManager.h"
#include "Global.h"
#include <string>

Player::Player(): m_level(9), m_energy(999), m_isAlive(true), m_direction(left), m_currentShape(1) {

}

Player::~Player() {

}

bool Player::init() {
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event) {
		auto target = static_cast<Player*>(event->getCurrentTarget());
		Point location = Director::getInstance()->convertToGL(touch->getLocationInView());
		auto rect = target->getBoundingBox();

		if (!rect.containsPoint(location)) {
			return false;
		}
		return true;
	};

	touchListener->onTouchMoved = [&](Touch* touch, Event* event) {
		auto target = static_cast<Player*>(event->getCurrentTarget());
		Point location = Director::getInstance()->convertToGL(touch->getLocationInView());
		Point oldLocation = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
		// Point oldLocation = target->getPosition();

		location = checkBorder(location);
		oldLocation = checkBorder(oldLocation);

		if (abs(location.x - oldLocation.x) >= 0.1f || abs(location.y - oldLocation.y) >= 0.1f) {

			if (location.x - oldLocation.x >= 2.0f) {
				m_direction = Direction::right;
				changeDirection(m_direction);
			} else if (oldLocation.x - location.x >= 2.0f) {
				m_direction = Direction::left;
				changeDirection(m_direction);
			}

			

			Point pos = Point(target->getPositionX() + location.x - oldLocation.x,
				target->getPositionY() + location.y - oldLocation.y);
			target->runAction(MoveTo::create(0.8f, pos));
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	initEventListener();
	reset();
	changeShape();
	return true;
}

bool Player::catchAndEatFish(Fish* fish) {
	if (fish->getFishLevel() > this->m_level) {
		m_isAlive = false;
		return false;
	}

	eat(fish);
	return true;
}

void Player::eat(Fish* fish) {
	this->m_energy += fish->getFishEnergy();
	upgrade();
}

void Player::upgrade() {
	if (this->m_level < MAX_LEVEL && this->m_energy >= LEVEL[this->m_level + 1]) {
		this->m_level++;
//		this->setScale(0.6 + this->m_level / 10.0);

		_eventDispatcher->dispatchCustomEvent(PLAYER_UPGRADE, nullptr);
		checkShape();
	}
}

bool Player::isAlive() {
	return this->m_isAlive;
}

void Player::reset() {
	m_isAlive = true;
	m_energy = 0;
	m_level = 1;
	m_currentShape = 1;
	m_playState = PLAYER_NORMAL;
	m_stateAction = nullptr;
//	this->setScale(0.6f);
	this->changeShape();
	this->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);
	this->runAction(Blink::create(2.0f, 5));
}

void Player::show() {
	this->setVisible(true);
	m_sprite->setVisible(true);
}

void Player::hide() {
	this->setVisible(false);
	m_sprite->setVisible(false);
}

Point Player::checkBorder(Point oldDestination) {
	Point tmpPoint = oldDestination;
	auto winSize = Director::getInstance()->getWinSize();
	if (oldDestination.x > winSize.width - m_size.width / 4) {
		tmpPoint.x = winSize.width - m_size.width / 4;
	}
	if (oldDestination.x < m_size.width / 4) {
		tmpPoint.x = m_size.width / 4;
	}

	if (oldDestination.y > winSize.height - m_size.height / 4) {
		tmpPoint.y = winSize.height - m_size.height / 4;
	}
	if (oldDestination.y < m_size.height / 4) {
		tmpPoint.y = m_size.height / 4;
	}

	return tmpPoint;
}

void Player::changeShape() {
	std::string name = "";
	if (m_currentShape == 1) {
		name = "playFish%d.png";
	} else if (m_currentShape == 2) {
		name = "playMFish%d.png";
	} else {
		name = "playBFish%d.png";
		if (m_level == MAX_LEVEL) {
			name = "Fish6_%d.png";
		}
	}

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Fishall.plist", "Fishall.png");
	SpriteFrame* frame = nullptr;
	Vector<SpriteFrame*> frameList;
	for (int k = 1; k < 24; ++k) {
		frame = frameCache->getSpriteFrameByName(StringUtils::format(name.c_str(), k));
		frameList.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);
	Animate* animate = Animate::create(animation);
	
	if (m_sprite != nullptr && m_sprite->getNumberOfRunningActions() > 0) {
		m_sprite->stopAllActions();
		this->removeChild(m_sprite);
	}
	auto sprite = Sprite::createWithSpriteFrame(frameList.at(0));
	sprite->runAction(animate);

	this->bindSprite(sprite);
}

void Player::checkShape() {
	int gameState = GameManager::getInstance()->getGameState();
	if (m_currentShape != gameState) {
		m_currentShape = gameState;
		changeShape();
	}
	if (m_level == MAX_LEVEL) {
		changeShape();
	}
}

void Player::changeDirection(Direction direction) {
	if (direction == Direction::left) {
		if (m_sprite->isFlippedX()) {
			m_sprite->setFlippedX(false);
		} 
	} else {
		if (!m_sprite->isFlippedX()) {
			m_sprite->setFlippedX(true);
		}
	}
}

void Player::initEventListener() {
	auto gameOverListener = EventListenerCustom::create(GAME_OVER, CC_CALLBACK_1(Player::EvnetGameOver, this));
	_eventDispatcher->addEventListenerWithFixedPriority(gameOverListener, 1);

	auto gameRestartListener = EventListenerCustom::create(GAME_RESTART, CC_CALLBACK_1(Player::EventGameRestart, this));
	_eventDispatcher->addEventListenerWithFixedPriority(gameRestartListener, 1);
}

void Player::EvnetGameOver(Ref* sender) {
	_eventDispatcher->pauseEventListenersForTarget(this);
}

void Player::EventGameRestart(Ref* sender) {
	_eventDispatcher->resumeEventListenersForTarget(this);
}
