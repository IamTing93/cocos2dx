#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "cocos2d.h"
USING_NS_CC;

class Player;
class FishManager;
class PropsManager;

class GameManager : public Node {
public:
	~GameManager();

	static GameManager* getInstance();
	static void destroy();
	virtual bool init();
	virtual void update(float delta);
	void reset();

	void gameStart();
	void gameOver();
	void gameRestart();
	void gamePause();
	void gameResume();
	void gameExit();


	CC_SYNTHESIZE(Player*, m_player, Player);
	CC_SYNTHESIZE(FishManager*, m_fishManager, FishManager);
	CC_SYNTHESIZE(PropsManager*, m_propsManager, PropsManager);
	CC_SYNTHESIZE(int, m_gameState, GameState);

private:
	GameManager();
	bool ready() const;
	void gameGoAhead(Ref* sender);

private:
	static GameManager* m_gameManager;
	float m_timeCounter;
};

#endif