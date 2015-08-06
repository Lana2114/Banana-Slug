#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "Laser.h"
#include "Diamond.h"
#include "Lightning.h"
//#include "Lightning2.h"
#include "Alert.h"
#include "OverLayer.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;
USING_NS_CC;

typedef Laser* lasers;
typedef Diamond* diamonds;
typedef Character* characters;
typedef Lightning* lightnings;
//typedef Lightning* lightnings;
typedef Alert* alerts;

class PlayScene : public cocos2d::LayerColor
{
private:
	Size visibleSize;

	characters character;
	lasers laser;
	diamonds diamond;

	Point GestureStartPoint;
	Point GestureEndPoint;


	vector<lasers> listLasers;
	vector<diamonds> listDiamond;
	vector<lightnings> listLightning;
	//vector<Lightning*> listLightning;
	vector<alerts> listAlert;

	alerts alert;

	MenuItemImage* pauseBtn;
	MenuItemImage* resumeBtn;

	int score;
	float TouchStart;
	bool isTouch;
	bool ableToJump;
	bool isDead;
	float velocity = 300;

	void checkGameOver();
	void destroy();

public:
	PhysicsWorld* m_world;
	Label *scoreLabel;
	void setPhyWorld(PhysicsWorld* world){ m_world = world; }
	static cocos2d::Scene* createScene();

	virtual bool init();
	long milisecondNow();

	bool onContactBegin(PhysicsContact &contact);
	bool onTouchBegan(Touch* touch, Event* unusedEvent);
	void onTouchMoved(Touch* touch, Event* unusedEvent);
	void onTouchEnded(Touch* touch, Event* unusedEvent);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

	void createAlert(Node* objectSender, Vec2 position);
	void createLaser(Node* objectSender, Vec2 position);
	//void createDiamond(float dt);
	void createBonusAndDiamond(float dt);


	void pauseGame();
	void resumeGame();

	/* - auto function to create alert light anh laser
	- use schedule_selector to use this function */
	void addLaser(float dt);
	/* - auto remove laser after add
	- use CC_CALLBACK_# to call this function */
	void removeLaser();
	void removeBonuses();
	void removeLight();

	void update(float dt);

	void addScore(float dt);


	CREATE_FUNC(PlayScene);
};

#endif // __PLAY_SCENE_H__