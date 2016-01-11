#include "Fish.h"
#include "Global.h"
#include "GameData.h"


Fish::Fish(): m_direction(0), m_speed(0), m_level(0), m_finishSwimming(false), m_escaping(false) {

}

Fish::~Fish() {

}

Fish* Fish::create(Sprite* sprite, int level) {
	Fish* pRet = new Fish();
	if (pRet && pRet->init()) {
		pRet->setFishLevel(level);
		pRet->bindSprite(sprite);

		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return nullptr;
}

bool Fish::init() {
	return true;
}

void Fish::swim() {
	Size winSize = Director::getInstance()->getWinSize();
	int endX = 0;
	if (this->m_direction == Direction::left) {
		endX = winSize.width + this->m_size.width;
	} else {
		endX = -this->m_size.width;
	}

	Point tartgetPoint = Point(endX, this->getPosition().y);
	m_destination = tartgetPoint;

	this->runAction(Sequence::create(DelayTime::create(0.5f),
		MoveTo::create(this->m_speed, tartgetPoint), 
		CallFunc::create([&]() {this->m_finishSwimming = true; }), NULL));
}

bool Fish::escape(Player* player, float speed) {
	if (player->getPlayerLevel() > m_level && !m_escaping) {
		m_escaping = true;
		stopSwimming();
		float distance = m_destination.distance(m_startPoint);
		float speedtmp = distance / m_speed;

		// 是否需要改变方向
		Point curPoint = this->getPosition();
		Point tmpPoint1 = Point(curPoint.x + 1.0f, curPoint.y);
		if (curPoint.distance(player->getPosition()) > tmpPoint1.distance(player->getPosition())) {
			m_direction = -m_direction;
			changeDirection();
		}

		Point tmpPoint2 = Point(curPoint.x - 1.0f, curPoint.y);
		if (curPoint.distance(player->getPosition()) > tmpPoint2.distance(player->getPosition())) {
			m_direction = -m_direction;
			changeDirection();
		}


		m_destination = m_startPoint;
		m_startPoint = this->getPosition();

		float _speed = (m_destination.distance(m_startPoint) / speedtmp);

		m_speed = _speed / (2 - 2 / (player->getPlayerLevel() - m_level));

		this->runAction(Sequence::create(
			MoveTo::create(this->m_speed, m_destination),
			CallFunc::create([&]() {this->m_finishSwimming = true; }), NULL));
		return true;
	}
	return false;
}

bool Fish::isFinishSwimming() {
	return m_finishSwimming;
}

void Fish::stopSwimming() {
	if (this->getNumberOfRunningActions() > 0) {
		this->stopAllActions();
	}
	this->m_finishSwimming = false;
}

void Fish::reset() {
	m_escaping = false;
	srand((unsigned int)time(0) / m_randomKey);
	this->m_speed = rand() % 20 + 5.0f;
	m_startPoint = getStartPosition();
	this->setPosition(m_startPoint);
	changeDirection();

	stopSwimming();
	this->swim();
}

bool Fish::isCollideWithPlayer(Player* player) {
	Rect playerRect = player->getBoundingBox();

	//Rect fishRect = this->getBoundingBox();

	//return playerRect.intersectsRect(fishRect);
	return playerRect.containsPoint(this->getPosition());
}

bool Fish::isColsedToPlayer(Player* player) {
	auto fishPosition = this->getPosition();
	return (fishPosition.distance(player->getPosition()) < FISH_ESCAPING_DISTANCE * (player->getPlayerLevel() - m_level));
}

Point Fish::getStartPosition() {
	int startX = 0, startY = 0;
	Size winSize = Director::getInstance()->getWinSize();

	srand((unsigned int)time(0) / m_randomKey);
	m_direction = rand() % 2 ? Direction::left : Direction::right;
	if (m_direction == Direction::left) {
		startX = 0 - this->m_size.width * 2;
	} else {
		startX = winSize.width + this->m_size.width * 2;
	}
	startY = rand() % (int)winSize.height;
	return Point(startX, startY);
}

void Fish::changeDirection() {
	if (this->m_direction == Direction::left) {
		if (!this->m_sprite->isFlippedX()) {
			this->m_sprite->setFlippedX(true);
		}
	} else {
		if (this->m_sprite->isFlippedX()) {
			this->m_sprite->setFlippedX(false);
		}
	}
}
