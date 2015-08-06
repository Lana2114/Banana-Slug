#ifndef _DIAMOND_H_
#define _DIAMOND_H_

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Diamond :public cocos2d::Layer
{
private:
	Sprite *diamondTexture;
	PhysicsBody *diamondBody;
public:
	Diamond(Layer *layer, Vec2 pos);
	~Diamond();
	void removeDiamond();

};
#endif _DIAMOND_H_