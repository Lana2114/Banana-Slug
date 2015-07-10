#include "HelloWorldScene.h"
#include "Pixel.h"
#include "Floor.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, -1000.0f));

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	pixel = new Pixel(this);

	Pixel* pixel2 = new Pixel(this);

	floor = new Floor(this);

	auto edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeSp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(boundBody);
	this->addChild(edgeSp);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

bool HelloWorld::onContactBegin(PhysicsContact &contact)
{
	auto shapeA = contact.getShapeA();
	auto shapeB = contact.getShapeB();

	if ((shapeA->getCategoryBitmask() == eObjectBitmask::FLOOR && shapeB->getCategoryBitmask() == eObjectBitmask::PIXEL)
		|| (shapeA->getCategoryBitmask() == eObjectBitmask::PIXEL && shapeB->getCategoryBitmask() == eObjectBitmask::FLOOR))
	{
		pixel->isContact == true;
		pixel->update();
	}
	return true;
}


