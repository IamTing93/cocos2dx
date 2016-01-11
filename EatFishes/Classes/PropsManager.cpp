#include "PropsManager.h"
#include "Props.h"
#include "PropsHeader.h"


PropsManager::PropsManager() {

}

PropsManager::~PropsManager() {

}

bool PropsManager::init() {
	this->addProps(PropClearUp::create());
	this->addProps(PropBigger::create());
	this->addProps(PropSmaller::create());
	return true;
}



void PropsManager::run() {
	auto keys = m_map.keys();
	for (auto key : keys) {
		auto prop = m_map.at(key);
		if (prop->isCollidedWithPlayer()) {
			prop->affect();
			prop->reset();
		}
	}
}

void PropsManager::reset() {
	if (!m_propsNameVec.empty()) {
		auto keys = m_map.keys();
		for (auto key : keys) {
			auto prop = m_map.at(key);
			prop->reset();
		}
	}
}

void PropsManager::propsAppear() {
	if (!m_propsNameVec.empty()) {
		int num = m_propsNameVec.size();
		srand((unsigned int)time(0));

		int choose = 0;
		int randNum = rand() % 100;
		if (randNum >= 80) {
			choose = num - 1;
		} else if (randNum >= 60) {
			choose = num - 2;
		}

		auto prop = m_map.at(m_propsNameVec.at(choose));
		if (!prop->isAppeared()) {
			prop->reset();
			prop->appear();
		}
	}
}

void PropsManager::addProps(Props* prop) {
	prop->setScale(0.2);
	prop->setAnchorPoint(Point(0.5f, 0.5f));
	prop->setPosition(Point(-70.0f, -70.0f));
	this->addChild(prop);
	m_propsNameVec.push_back(prop->getPropName());
	m_map.insert(prop->getPropName(), prop);
}
