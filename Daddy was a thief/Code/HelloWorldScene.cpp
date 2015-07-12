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
	
	//PIXEL
	pixel = new Pixel(this);

	//FLOOR
	floor = new Floor(this);

	//WALL
	auto edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeSp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(boundBody);
	this->addChild(edgeSp);

	//CONTACT
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//TOUCH
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

bool HelloWorld::onContactBegin(PhysicsContact &contact)
{
	auto shapeA = contact.getShapeA();
	auto shapeB = contact.getShapeB();

	if ((shapeA->getCategoryBitmask() == eObjectBitmask::FLOOR && shapeB->getCategoryBitmask() == eObjectBitmask::PIXEL)
		|| (shapeA->getCategoryBitmask() == eObjectBitmask::PIXEL && shapeB->getCategoryBitmask() == eObjectBitmask::FLOOR))
	{
		pixel->isContact = true;
		//pixel->update();
	}
	return true;
}

long HelloWorld::milisecondNow()
{
	struct timeval now;
	gettimeofday(&now, nullptr);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

bool HelloWorld::onTouchBegan(Touch *touch, Event* unusedEvent)
{
	Point location = touch->getLocation();

	//ghi nhận thời điểm bắt đầu chạm vào biến _TouchStart
	this->_TouchStart = this->milisecondNow();

	//ghi nhận điểm bắt đầu chạm vào biến _GestureStartPoint
	this->_GestureStartPoint = location;
	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event* unusedEvent)
{

}

void HelloWorld::onTouchEnded(Touch* touch, Event* unusedEvent)
{
	Point location = touch->getLocation();

	//ghi nhận điểm kết thúc chạm vào biến _GestureEndPoint
	this->_GestureEndPoint = location;

	//ghi nhận thời điểm kết thúc chạm
	long endTime = this->milisecondNow();

	//tính khoảng thời gian từ lúc chạm đến lúc kết thúc chạm
	float deltaX = this->_GestureStartPoint.x - this->_GestureEndPoint.x;
	float deltaY = this->_GestureStartPoint.y - this->_GestureEndPoint.y;

	float speed = 0;

	if (deltaY > 0)//vuốt xuống
	{

	}
	if (deltaY < 0)//vuốt lên
	{
		pixel->jumpUp();
	}

	//tính tốc độ quẹt
	//speed = fabs(deltaX) / deltaTime;
	//Với tốc độ quẹt và hướng quẹt ==> dễ dàng cho ScrollLayer trôi thêm một khoảng
	//float dx = speed * Con_số_nào_đó_tuỳ bạn_để_trớn_nhiều_hay_ít.
	

}
