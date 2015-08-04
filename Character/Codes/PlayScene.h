#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "Laser.h"
class PlayScene : public cocos2d::LayerColor
{
private:
	Character* character;
	Point GestureStartPoint;
	Point GestureEndPoint;
	float TouchStart;
	bool isTouched;
	bool ableToJump;
public:
	PhysicsWorld* m_world;

	void setPhyWorld(PhysicsWorld* world)
	{
		m_world = world;
	}
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	bool onContactBegin(PhysicsContact &contact);

	long milisecondNow();

	bool onTouchBegan(Touch* touch, Event* unusedEvent);
	void onTouchMoved(Touch* touch, Event* unusedEvent);
	void onTouchEnded(Touch* touch, Event* unusedEvent);
	
	void update(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(PlayScene);
};

#endif // __PLAY_SCENE_H__