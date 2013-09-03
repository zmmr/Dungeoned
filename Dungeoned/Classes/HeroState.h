#ifndef _HEROSTATE_H_
#define _HEROSTATE_H_

#include "GameConstants.h"

class HeroState
{
	virtual void enter(int previous);
	virtual void exit(int next);

	virtual bool is_moveable() = 0;

	virtual bool is_fightable() = 0;
};
#endif