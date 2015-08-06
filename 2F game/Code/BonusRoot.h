#ifndef _BONUS_ROOT_H_
#define _BONUS_ROOT_H_

#include "cocos2d.h"

USING_NS_CC;

class BonusRoot :public cocos2d::Layer
{
public:
	BonusRoot();
	virtual ~BonusRoot() = 0;
	virtual void removeBonus() = 0;
};
#endif _BONUS_H_	