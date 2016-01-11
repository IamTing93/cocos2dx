#ifndef PROPSMALLER_H
#define PROPSMALLER_H

#include "Props.h"

class PropSmaller : public Props {
public:
	PropSmaller();
	~PropSmaller();

	CREATE_FUNC(PropSmaller);
	virtual bool init() override;
	virtual void affect() override;
};

#endif