#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "cocos2d.h"
#include "Definitions.h"
#include "stdlib.h"
#include "time.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

using namespace CocosDenshion;

class Character
{
private:
	Vec2 origin;
	Size visibleSize;

	Sprite* characterTexture;
	PhysicsBody* characterBody;

	bool _move;
public:
	Character(Layer* layer, Size visibleSize);
	void update();
	void moveRight();
	void moveLeft();
	void jumpUp();
	bool isMoved();
};
#endif _CHARACTER_H_