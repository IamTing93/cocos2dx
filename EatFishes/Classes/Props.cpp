#include "Props.h"
#include "GameManager.h"
#include "Player.h"



Props::Props() :m_isAppeared(false) {

}

Props::~Props() {

}

void Props::appear() {
	m_isAppeared = true;
	srand((unsigned int)time(0));
	float duration = rand() % 40 + 5.0f;
	this->runAction(Sequence::create(
		MoveTo::create(duration, m_destination),
		CallFunc::create([&]() { m_isAppeared = false; }),
		NULL));
}

void Props::reset() {
	if (this->getNumberOfRunningActions() > 0) {
		this->stopAllActions();
	}
	m_isAppeared = false;
	getStartPoint();
	getDestination();
	this->setPosition(m_startPoint);
}

bool Props::isAppeared() const {
	return m_isAppeared;
}

Point Props::getStartPoint() {
	srand((unsigned int)time(0));
	m_direction = rand() % 2 == 0 ? Direction::up : Direction::down;

	auto winSize = Director::getInstance()->getWinSize();

	int startX = rand() % ((int)winSize.width);

	int startY = winSize.height + 50.0f;

	if (m_direction == Direction::down) {
		startY = -50.0f;
	}

	m_startPoint = Point(startX, startY);

	return m_startPoint;
}

Point Props::getDestination() {
	auto winSize = Director::getInstance()->getWinSize();

	int endY = (m_direction == Direction::up) ? -50.0f : winSize.height + 50.0f;

	m_destination = Point(m_startPoint.x, endY);

	return m_destination;
}


bool Props::isCollidedWithPlayer() {
	Player* player = GameManager::getInstance()->getPlayer();
	auto playerRect = player->getBoundingBox();
	return playerRect.containsPoint(this->getPosition());
}
