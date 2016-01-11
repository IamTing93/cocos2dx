#include "FishManager.h"
#include "GameData.h"
#include "Fish.h"
#include "Player.h"
#include "Global.h"

const int* FISHES_LISTS[] = {nullptr, FISHES_LIST_01, FISHES_LIST_02, FISHES_LIST_03 };


FishManager::FishManager() : m_player(nullptr), m_fishesTotalNum(0), m_fishesListId(1) {

}

FishManager::~FishManager() {

}

void FishManager::bindPlayer(Player* player) {
	this->m_player = player;
}

bool FishManager::init() {
	m_fishesTotalNum = 0;
	for (int i = 0; i <= MAX_LEVEL; ++i) {
		m_fishesTotalNum += FISHES_LISTS[m_fishesListId][i];
	}

	createFishes();
	fishSwim(0);
	return true;
}



void FishManager::updateFunc(float delta) {
	bool allOldFishesStop = true;
	for (auto fish : m_fishesOld) {
		if (!fish->isFinishSwimming()) {
			allOldFishesStop = false;
			break;
		}
	}

	if (allOldFishesStop) {
		for (auto fish : m_fishesOld) {
			this->removeChild(fish);
		}
		m_fishesOld.clear();
		unscheduleAllCallbacks();
	}
}

void FishManager::run() {
	checkFishesState(m_fishes, 1);
	if (!m_fishesOld.empty()) {
		checkFishesState(m_fishesOld, 2);
	}
}

void FishManager::reset() {
	if (this->getNumberOfRunningActions() > 0) {
		this->stopAllActions();
	}

	for (auto fish : m_fishes) {
		fish->stopSwimming();
		fish->setPosition(-(fish->getContentSize().width + 10), -(fish->getContentSize().height + 10));
	}
	if (!m_fishesOld.empty()) {
		for (auto fish : m_fishesOld) {
			fish->stopSwimming();
			fish->setPosition(-(fish->getContentSize().width + 10), -(fish->getContentSize().height + 10));
			this->removeChild(fish);
		}
		m_fishesOld.clear();
	}
	fishSwim(0);
}

void FishManager::changeFishes(int gameState) {
	m_fishesListId = gameState;
	m_fishesTotalNum = 0;
	for (int i = 0; i <= MAX_LEVEL; ++i) {
		m_fishesTotalNum += FISHES_LISTS[m_fishesListId][i];
	}
	copyFishes();
	createFishes();
	schedule(schedule_selector(FishManager::updateFunc));
	fishSwim(0);
}

void FishManager::createFishes() {
	if (m_fishes.empty()) {
		SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile("fish.plist", "fish.png");

		int counter = 1;
		for (int i = 1; i <= MAX_LEVEL; ++i) {
			SpriteFrame* frame = nullptr;
			Vector<SpriteFrame*> frameList;

			for (int k = 1; k < 10; ++k) {
				frame = frameCache->getSpriteFrameByName(StringUtils::format("fish0%d_0%d.png", i, k));
				frameList.pushBack(frame);
			}
			frame = frameCache->getSpriteFrameByName(StringUtils::format("fish0%d_10.png", i));
			frameList.pushBack(frame);
			Animation* animation = Animation::createWithSpriteFrames(frameList);
			animation->setLoops(-1);
			animation->setDelayPerUnit(0.1f);
			Animate* animate = Animate::create(animation);

			for (int j = 0; j < FISHES_LISTS[m_fishesListId][i]; ++j) {
				auto fs = Sprite::createWithSpriteFrame(frameList.at(0));
				fs->runAction(animate->clone());
				auto fish = Fish::create(fs, i);
				fish->setFishEnergy(FISH_ENERGY[i]);
				fish->setPosition(-(fish->getContentSize().width + 10), -(fish->getContentSize().height + 10));
				fish->setAnchorPoint(Point(0.5f, 0.5f));
				fish->setScale(1.3f);
				this->addChild(fish);
				fish->setRandomKey(counter++);
				m_fishes.pushBack(fish);
			}
		}
	}
}

void FishManager::destoryFishes() {
	
}

void FishManager::copyFishes() {
	for (auto fish : m_fishes) {
		m_fishesOld.pushBack(fish);
	}
	m_fishes.clear();
}

void FishManager::checkFishesState(Vector<Fish*> fishes, int flag) {
	if (this->m_player->isAlive()) {
		for (int i = 0; i < fishes.size(); ++i) {
			auto fish = fishes.at(i);
			if (fish->isCollideWithPlayer(this->m_player) && this->m_player->catchAndEatFish(fish)) {
				if (flag != 2) {
					fish->reset();
				}
			} else if (fish->isColsedToPlayer(m_player)) {
				fish->escape(m_player, 2.0f);
			} else if (fish->isFinishSwimming()) {
				if (flag != 2) {
					fish->reset();
				}
			}
		}
	}
}

void FishManager::fishSwim(int num) {
	if (num < m_fishesTotalNum) {
		auto func = [&, num]() {
			this->m_fishes.at(num)->reset();
			fishSwim(num + 1);
		};
		CallFunc* callbackFunc = CallFunc::create(func);
		auto seq = Sequence::create(DelayTime::create(0.5f), 
			callbackFunc, NULL);
		this->runAction(seq);
	}
}
