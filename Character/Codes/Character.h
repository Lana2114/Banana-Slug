#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "cocos2d.h"
#include "Definitions.h"
#include "stdlib.h"
#include "time.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

using namespace CocosDenshion;

class Character: public Layer
{
private:
	Vec2 origin;
	Size visibleSize;

	Sprite* characterTexture;
	PhysicsBody* characterBody;

	float position;


public:
	int changeDirect = 1;

	Character(Layer* layer, Size visibleSize);
	void update();
	void jumpUp();
	bool isRight();
	void update(float delta, bool &isTouched, bool &ableToJump);
};
#endif _CHARACTER_H_