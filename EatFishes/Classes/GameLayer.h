#ifndef GAMELAYER_H
#define GAMELAYER_H

#include "cocos2d.h"

USING_NS_CC;

class LayerHelper;

class GameLayer : public Layer {
public:
	GameLayer();
	~GameLayer();

	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(GameLayer);

private:
	void initEventListener();

	void EventGameStart(Ref* sender);
	void EvnetGameOver(Ref* sender);
	void EventGameRestart(Ref* sender);
	void EventGamePause(Ref* sender);
	void EventGameResume(Ref* sender);

private:
	LayerHelper* m_layerHelper;
};



#endif