#ifndef _LIGHTNING_H_
#define _LIGHTNING_H_

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Lightning :public cocos2d::Layer
{
private:
	Sprite *LightningTexture;
	PhysicsBody *LightningBody;
public:
	Lightning(Layer *layer, Vec2 pos);
	~Lightning();
	void removeBonus();

};
#endif _LIGHTNING_H_