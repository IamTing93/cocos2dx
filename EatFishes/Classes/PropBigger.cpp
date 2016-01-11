#include "PropBigger.h"
#include "GameManager.h"
#include "Player.h"


PropBigger::PropBigger() {
	m_name = "Bigger";
}

PropBigger::~PropBigger() {

}

bool PropBigger::init() {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("props.plist", "props.png");
	auto sprite = Sprite::createWithSpriteFrameName("orbz_012.png");

	this->bindSprite(sprite);
	
	return true;
}

void PropBigger::affect() {
	auto player = GameManager::getInstance()->getPlayer();
	if (!(player->getPlayerState() == PLAYER_BIGGER)) {
		player->setPlayerState(PLAYER_BIGGER);
		if (player->getPlayerStateAction() != nullptr) {
			player->stopAction(player->getPlayerStateAction());

		}
		Action* seq = Sequence::create(
			ScaleTo::create(2.0f, 1.5f),
			DelayTime::create(10.0f),
			Blink::create(2.0f, 5),
			ScaleTo::create(2.0f, 1.0f),
			CallFunc::create([=]() {player->setPlayerState(PLAYER_NORMAL); }),
			NULL
			);
		player->runAction(seq);
		player->setPlayerStateAction(seq);
	}
}
