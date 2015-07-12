#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Pixel.h"
#include "Floor.h"

USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
	Sprite* ball;

	PhysicsWorld* m_world;

	void setPhyWorld(PhysicsWorld* world){ m_world = world; };

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//virtual void onAcceleration(Acceleration* acc, Event* unused_event);

	bool onContactBegin(PhysicsContact &contact);

	Pixel* pixel;

	Floor* floor;

	float _TouchStart;
	Point _GestureStartPoint;
	Point _GestureEndPoint;
	long milisecondNow();
	bool onTouchBegan(Touch *touch, Event *unsuedEvent);
	void onTouchMoved(Touch *touch, Event *unusedEvent);
	void onTouchEnded(Touch *touch, Event *unusedEvent);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__


