#include "PropClearUp.h"
#include "GameManager.h"
#include "FishManager.h"



PropClearUp::PropClearUp() {
	m_name = "ClearUp";
}

PropClearUp::~PropClearUp() {

}

bool PropClearUp::init() {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("props.plist", "props.png");
	auto sprite = Sprite::createWithSpriteFrameName("orbz_001.png");

	this->bindSprite(sprite);
	return true;
}

void PropClearUp::affect() {
	GameManager::getInstance()->getFishManager()->reset();
}
