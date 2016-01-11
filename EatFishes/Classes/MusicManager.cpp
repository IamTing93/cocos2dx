#include "MusicManager.h"
#include "GameData.h"



void MusicManager::init() {
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGMUSIC);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_BUTTON_CLICK);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_GAME_OVER);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_GAME_START);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_PLAYER_UPGRADE);
}

void MusicManager::playBackgroundMusic() {
	SimpleAudioEngine::getInstance()->playBackgroundMusic(BGMUSIC, true);
}

void MusicManager::playButtonEffect() {
	SimpleAudioEngine::getInstance()->playEffect(EFFECT_BUTTON_CLICK);
}

void MusicManager::playGameStartEffect() {
	SimpleAudioEngine::getInstance()->playEffect(EFFECT_GAME_START);
}

void MusicManager::playGameOverEffect() {
	SimpleAudioEngine::getInstance()->playEffect(EFFECT_GAME_OVER);
}

void MusicManager::playPlayerUpgradeEffect() {
	SimpleAudioEngine::getInstance()->playEffect(EFFECT_PLAYER_UPGRADE);
}

void MusicManager::stopBackgroundMusic() {
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
