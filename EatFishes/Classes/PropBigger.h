#ifndef PROPBIGGER_H
#define PROPBIGGER_H

#include "Props.h"

class PropBigger : public Props {
public:
	PropBigger();
	~PropBigger();

	CREATE_FUNC(PropBigger);
	virtual bool init() override;
	virtual void affect() override;
};

#endif