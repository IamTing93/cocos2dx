#ifndef PROPCLEARUP_H
#define PROPCLEARUP_H

#include "Props.h"

class PropClearUp : public Props {
public:
	PropClearUp();
	~PropClearUp();

	CREATE_FUNC(PropClearUp);
	virtual bool init() override;
	virtual void affect() override;
};

#endif