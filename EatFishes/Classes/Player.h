#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Global.h"

class Fish;

class Player : public Entity {
public:
	Player();
	~Player();

	CREATE_FUNC(Player);
	virtual bool init();

	bool catchAndEatFish(Fish* fish);
	void eat(Fish* fish);
	void upgrade();
	bool isAlive();
	void reset();
	void show();
	void hide();

	CC_SYNTHESIZE_READONLY(Direction, m_direction, PlayerDirection);
	CC_SYNTHESIZE_READONLY(int, m_level, PlayerLevel);
	CC_SYNTHESIZE(int, m_playState, PlayerState);
	CC_SYNTHESIZE(Action*, m_stateAction, PlayerStateAction);

private:
	Point checkBorder(Point oldDestination);
	void changeShape();
	void checkShape();
	void changeDirection(Direction direction);
	void initEventListener();
	void EvnetGameOver(Ref* sender);
	void EventGameRestart(Ref* sender);

private:
	int m_energy;
	bool m_isAlive;
	int m_currentShape;

};

#endif