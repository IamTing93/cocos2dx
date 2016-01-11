#ifndef GAMEOVERLAYER_H
#define GMAEOVERLAYER_H

#include "cocos2d.h"

USING_NS_CC;

class LayerHelper : public Layer {
public:
	LayerHelper();
	~LayerHelper();

	CREATE_FUNC(LayerHelper);
	virtual bool init();

	void show(int layerType);
	void hide();

private:
	void initMenuItems();
	void checkLayerType(int labelType);
	void showMenuItems(Menu* menu);
	void showTiTle(Node* titleNode);
	void menuCallbackRestart(Ref* sender);
	void menuCallbackResume(Ref* sender);
	void menuCallbackExit(Ref* sender);
	void menuCallbackStart(Ref* sender);

private:
	Node* m_currentTiTle;
	Menu* m_currentMenu;

	Label* m_labelGameOver;
	Menu* m_menuGameOver;
	Label* m_labelGamePause;
	Menu* m_menuGamePause;

	Sprite* m_spriteGameStart;
	Menu* m_menuGameStart;
};

#endif