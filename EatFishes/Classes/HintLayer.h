#ifndef HINTLAYER_H
#define HINTLAYER_H

#include "cocos2d.h"

USING_NS_CC;

class HintLayer : public Layer {
public:
	HintLayer();
	~HintLayer();

	CREATE_FUNC(HintLayer);
	virtual bool init();
	void reset();

	void show();
	void hide();

private:
	void updateHint(Ref* sender);

	void gameRestart(Ref* sender);
	void gameStart(Ref* sender);
	void gameOver(Ref* sender);

private:
	Vector<Sprite*> m_fishesHint;
	Label* m_labelHint;
};

#endif