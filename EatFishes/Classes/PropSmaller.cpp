#include "PropSmaller.h"
#include "GameManager.h"
#include "Player.h"
#include "Global.h"


PropSmaller::PropSmaller() {
	m_name = "Smaller";
}

PropSmaller::~PropSmaller() {

}

bool PropSmaller::init() {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("props.plist", "props.png");
	auto sprite = Sprite::createWithSpriteFrameName("orbz_004.png");
	
	this->bindSprite(sprite);
	
	return true;
}

void PropSmaller::affect() {
	auto player = GameManager::getInstance()->getPlayer();
	if (!(player->getPlayerState() == PLAYER_SMALLER)) {
		if (player->getPlayerStateAction() != nullptr) {
			player->stopAction(player->getPlayerStateAction());
		}

		Action* seq = Sequence::create(
			ScaleTo::create(2.0f, 0.5f),
			DelayTime::create(10.0f),
			Blink::create(2.0f, 5),
			ScaleTo::create(2.0f, 1.0f),
			CallFunc::create([=]() {player->setPlayerState(PLAYER_NORMAL); }),
			NULL
			);
		player->setPlayerState(PLAYER_SMALLER);
		player->runAction(seq);
		player->setPlayerStateAction(seq);
	}
}
