#ifndef _BONUS_H_
#define _BONUS_H_

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Bonus :public cocos2d::Layer
{
private:
	Sprite *BonusTexture;
	PhysicsBody *BonusBody;
public:
	Bonus(Layer *layer, Vec2 pos);
	~Bonus();
	void removeBonus();
	//void removeBonus(float dt);
};
#endif _BONUS_H_	