#ifndef _PIXEL_H_
#define _PIXEL_H_

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Pixel
{
public:
	Pixel(Layer* layer);
	void update();
	bool isContact;

private:
	Sprite* pixelTexture;
	PhysicsBody* pixelBody;

	Size visibleSize;
	Vec2 origin;
	
};
#endif //_PIXEL_H_