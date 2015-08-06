#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "cocos2d.h"
#include "Definitions.h"
#include "stdlib.h"
#include "time.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

using namespace CocosDenshion;

class Character : public cocos2d::Layer
{
private:
	Vec2 origin;


	Sprite* characterTexture;
	PhysicsBody* characterBody;

	bool _move;
public:
	Size visibleSize;
	bool isDead;
	Character(Layer* layer, Size visibleSize);
	void update(float delta, bool &isTouched, bool &ableToJump, float &velocity);
	void jumpUp();
	float getPositionX();
	void setPositionX(float position);
	float getContentSizeX();

	//hàm kt nhan vat cham goc phai man hinh
	bool isRight();
	//biến đổi hướng của nhân vật
	int changeDirect ;
};
#endif _CHARACTER_H_