#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class MusicManager {
public:
	static void init();
	static void playBackgroundMusic();
	static void playButtonEffect();
	static void playGameStartEffect();
	static void playGameOverEffect();
	static void playPlayerUpgradeEffect();

	static void stopBackgroundMusic();
private:
};

#endif