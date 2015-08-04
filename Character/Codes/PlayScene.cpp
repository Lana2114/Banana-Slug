#include "PlayScene.h"

USING_NS_CC;

Scene* PlayScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0,0));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	// 'layer' is an autorelease object
	auto layer = PlayScene::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->getPhysicsWorld();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(255,255,255,255)))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//character
	character = new Character(this,visibleSize);

	//Boundary
	auto edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeSp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(boundBody);
	this->addChild(edgeSp);

	//Contact Listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//Touch Listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	isTouched = false;
	ableToJump = true;
	this->scheduleUpdate();
	return true;
}

long PlayScene::milisecondNow()
{
	struct timeval now;
	gettimeofday(&now, nullptr);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}
bool PlayScene::onTouchBegan(Touch* touch, Event* unusedEvent)
{
	Point location = touch->getLocation();
	this->TouchStart = this->milisecondNow();
	this->GestureStartPoint = location;
	return true;
}

void PlayScene::onTouchMoved(Touch* touch, Event* unusedEvent)
{

}

void PlayScene::onTouchEnded(Touch* touch, Event* unusedEvent)
{
	Point location = touch->getLocation();
	this->GestureEndPoint = location;

	long endTime = this->milisecondNow();

	float deltaX = GestureStartPoint.x - GestureEndPoint.x;
	float deltaY = GestureStartPoint.y - GestureEndPoint.y;

	//if (deltaX > 0 && deltaY > -100 && deltaY <= 50) // vuot trai
	//{
	//	character->moveLeft();
	//}
	//if (deltaX < 0 && deltaY > -50 && deltaY <= 50) //vuot phai
	//{
	//	character->moveRight();
	//}

	if (deltaY < 0 && deltaX > -80 && deltaX <= 80 && ableToJump == true) //vuot len
	{
		character->jumpUp();
	}

	if (deltaY ==0 && deltaX ==0)
		isTouched = true;

	/*long deltaTime = endTime - this->TouchStart;
	float speed = fabs(deltaX) / deltaTime;
	float dx = speed * 2;*/
}
bool PlayScene::onContactBegin(PhysicsContact &contact)
{
	//auto shapeA = contact.getShapeA();
	//auto shapeB = contact.getShapeB();

	//if ((shapeA->getCategoryBitmask() == objectBitmask::CHARACTER && shapeB->getCategoryBitmask() == objectBitmask::BOUNDARY) ||
	//	(shapeB->getCategoryBitmask() == objectBitmask::CHARACTER && shapeA->getCategoryBitmask() == objectBitmask::BOUNDARY))
	//{
	//	ableToJump = true;
	//}
	//else 
	//	ableToJump = false;

	return true;
}

void PlayScene::update(float dt)
{
	character->update(dt, isTouched,ableToJump);
	
}