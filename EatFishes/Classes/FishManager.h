#ifndef FISHMANAGER_H
#define FISHMANAGER_H

#include "cocos2d.h"


USING_NS_CC;
class Fish;
class Player;

class FishManager: public Node {
public:
	FishManager();
	~FishManager();

	void bindPlayer(Player* player);

	CREATE_FUNC(FishManager);
	virtual bool init();
	void updateFunc(float delta);

	void run();
	void reset();
	void changeFishes(int gameState);


private:
	void createFishes();
	void destoryFishes();
	void copyFishes();
	void checkFishesState(Vector<Fish*> fishes, int flag);
	void fishSwim(int id);

private:
	Vector<Fish*> m_fishes;
	Vector<Fish*> m_fishesOld;
	Player* m_player;
	int m_fishesTotalNum;
	int m_fishesListId;
};



#endif