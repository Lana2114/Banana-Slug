#ifndef _FLOOR_H_
#define _FLOOR_H_

#include "Definitions.h"
#include "cocos2d.h"
#include "Pixel.h"
USING_NS_CC;

class Floor
{
public:
	Floor(Layer* layer);
	void removeFloor();
private:
	std::vector<Sprite*> MyFloor;
	cocos2d::Sprite* floorTexture;
	cocos2d::PhysicsBody* floorBody;

	float xCoordinate = 0;
	Size visibleSize;
	Vec2 origin;
};
#endif //_FLOOR_H_

