#ifndef PROPSMANAGER_H
#define PROPSMANAGER_H

#include "cocos2d.h"
#include <string>
#include <vector>

USING_NS_CC;

class Props;

class PropsManager : public Node {
public:
	PropsManager();
	~PropsManager();

	CREATE_FUNC(PropsManager);
	virtual bool init();
	void run();
	void reset();
	void addProps(Props* prop);
	void propsAppear();

private:

private:
	std::vector<std::string> m_propsNameVec;
	Map<std::string, Props*> m_map;
};

#endif