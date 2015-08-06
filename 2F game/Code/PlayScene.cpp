
//------------------------------------------------------------------------------------------------
// Project's name: 2F
// Developer team: Firelight VN
// Authors: Do Phu An - Nghiem Lan Anh
// Language: C++
// Platform: Android, WP 8.1, WP 8, win 32
// -----------------------------------------------------------------------------------------------

#include "PlayScene.h"


USING_NS_CC;

Scene* PlayScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = PlayScene::create();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->addChild(layer);
	return scene;
}

void PlayScene::destroy()
{
	listLasers.clear();
	listDiamond.clear();
	listAlert.clear();
	//listLightning.clear();
	removeAllChildren();
	removeFromParent();
	cleanup();
	release();
}

bool PlayScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	score = 0;
	isDead = false;


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


	//character
	character = new Character(this, visibleSize);

	//Touch Listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	/*score Label*/
	scoreLabel = Label::createWithTTF("0", "fonts/Bauhaus_.ttf", 25);
	scoreLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
	scoreLabel->setPosition(Vec2(visibleSize.width - 10.0f, visibleSize.height - scoreLabel->getContentSize().height));
	this->addChild(scoreLabel, 100);

	/*add pause button */
	pauseBtn = MenuItemImage::create("btn/PauseBtn.png", "btn/PauseBtnSelected.png", CC_CALLBACK_0(PlayScene::pauseGame, this));
	pauseBtn->setScale(0.5f);
	auto pause = Menu::create(pauseBtn, nullptr);
	pause->setPosition(Vec2(pauseBtn->getContentSize().width, visibleSize.height - pauseBtn->getContentSize().height));
	this->addChild(pause);


	/*add resum button*/
	resumeBtn = MenuItemImage::create("btn/PlayBtn.png", "btn/PlayBtnSelected.png", CC_CALLBACK_0(PlayScene::resumeGame, this));
	resumeBtn->setScale(0.5f);
	auto resume = Menu::create(resumeBtn, nullptr);
	resume->setPosition(Vec2(pauseBtn->getContentSize().width + 50, visibleSize.height / 2));
	this->addChild(resume);
	resumeBtn->setVisible(false);

	isTouch = false;
	ableToJump = true;

	this->setKeyboardEnabled(true);
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

	//if (deltaX > 0 && deltaY > -30 && deltaY <= 30) // vuot trai
	//{
	//	character->moveLeft();
	//}

	//if (deltaX < 0 && deltaY > -30 && deltaY <= 30) //vuot phai
	//{
	//	character->moveRight();
	//}

	if (deltaY < 0 && deltaY > -300 && deltaX >= -30 && deltaX < 30 && ableToJump == true) //vuot len
	{
		character->jumpUp();
	}

	if (deltaY == 0 && deltaX == 0)
		isTouch = true;
}

bool PlayScene::onContactBegin(PhysicsContact &contact)
{
	auto shapeA = contact.getShapeA();
	auto shapeB = contact.getShapeB();

	if ((shapeA->getCategoryBitmask() == objectBitmask::CHARACTER && shapeB->getCategoryBitmask() == objectBitmask::LASER) ||
		(shapeB->getCategoryBitmask() == objectBitmask::CHARACTER && shapeA->getCategoryBitmask() == objectBitmask::LASER))
	{
		// Đụng laser là chết, xử lý sau
		//isDead = true;
		isDead = true;
	}
	else
	{
		if ((shapeA->getCategoryBitmask() == objectBitmask::CHARACTER && shapeB->getCategoryBitmask() == objectBitmask::DIAMOND) ||
			(shapeB->getCategoryBitmask() == objectBitmask::CHARACTER && shapeA->getCategoryBitmask() == objectBitmask::DIAMOND))
		{
			// delete diamond
			listDiamond.back()->removeDiamond();
			listDiamond.pop_back();
		}
		if ((shapeA->getCategoryBitmask() == objectBitmask::CHARACTER && shapeB->getCategoryBitmask() == objectBitmask::BONUS) ||
			(shapeB->getCategoryBitmask() == objectBitmask::CHARACTER && shapeA->getCategoryBitmask() == objectBitmask::BONUS))
		{

			//listLightning.pop_back();
			//listLightning.clear();

			if (listLightning.empty() == false)
			{
				listLightning.back()->removeBonus();
				listLightning.clear();
			}

		}
	}
	return true;
}

void PlayScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		this->destroy();
		Director::getInstance()->end();
		exit(0);
	}
}

void PlayScene::pauseGame()
{
	//this->removeChild(scoreLabel);
	this->pauseSchedulerAndActions();
	character->pauseSchedulerAndActions();
	pauseBtn->setVisible(false);
	resumeBtn->setVisible(true);
}

void PlayScene::resumeGame()
{
	this->resumeSchedulerAndActions();
	character->resumeSchedulerAndActions();
	auto childs = this->getChildren();
	for (auto child : childs)
	{
		child->resume();
	}
	pauseBtn->setVisible(true);
	resumeBtn->setVisible(false);
}

void PlayScene::addScore(float dt)
{
	score++;
	scoreLabel->setString(__String::createWithFormat("%d", score)->getCString());
}

void PlayScene::createAlert(Node* objectSender, Vec2 position)
{
	Alert* alert = new Alert(this, visibleSize, position);
	listAlert.push_back(alert);
}

void PlayScene::createBonusAndDiamond(float dt)
{
	srand(NULL);
	int randomPosX = random(10.0f, 780.0f);

	srand(NULL);
	int randomChoice = random(1.0f, 100.0f);

	if (listDiamond.empty() == true && listLightning.empty() == true)
	{
		if (randomChoice != 2.0f)/* || randomChoice == 20.0f
								 || randomChoice == 40.0f || randomChoice == 60.0f
								 || randomChoice == 80.0f)*/
		{
			Lightning* lightning = new Lightning(this, Vec2(randomPosX, 20.0f));
			listLightning.push_back(lightning);
			//listLightning.resize(listLightning.size() + 1);
		}
		else
		{
			Diamond* diamond = new Diamond(this, Vec2(randomPosX, 20.0f));
			listDiamond.push_back(diamond);
		}
	}

}


void PlayScene::createLaser(Node *objectSender, Vec2 position)
{
	laser = new Laser(this, visibleSize, position);
	listLasers.push_back(laser);
}

void PlayScene::addLaser(float dt)
{
	srand(NULL);
	int distance = random(40, 150);

	int laserPosition;
	float x, y;

	y = visibleSize.height - 20;

	if (character->getPositionX() < visibleSize.width - (character->getContentSize().width))
	{
		laserPosition = 1;
	}
	else
	{
		laserPosition = -1;
	}

	if (character->changeDirect == 1)
	{
		x = character->getPositionX() + distance * laserPosition;
	}
	else if (character->getPositionX() - distance * laserPosition < character->getContentSize().width / 2)
	{
		x = character->getContentSize().width / 2;
	}
	else
	{
		x = character->getPositionX() - distance * laserPosition;
	}

	auto sequence = Sequence::create(CallFuncN::create(CC_CALLBACK_1(PlayScene::createAlert, this, Vec2(x, y))),
		DelayTime::create(0.5),
		CallFuncN::create(CC_CALLBACK_1(PlayScene::createLaser, this, Vec2(x, visibleSize.height / 2))),
		CallFuncN::create(CC_CALLBACK_0(PlayScene::removeLight, this)),
		DelayTime::create(0.5),
		CallFuncN::create(CC_CALLBACK_0(PlayScene::removeLaser, this)), NULL);
	this->runAction(sequence);
}

/* Remove Functions  -----------------------------------------------------------------------------------------------------------------
- Include: remove alert light function, remove lasers, remove Lightning after n seconds
- Purpose: Removing objects in game loop
-------------------------------------------------------------------------------------------------------------------------------------*/

void PlayScene::removeLight()
{
	while (listAlert.empty() != true)
	{
		listAlert.back()->removeAlert();
		listAlert.pop_back();
	}

}

void PlayScene::removeLaser()
{
	while (listLasers.empty() != true)
	{
		listLasers.back()->removeLaser();
		listLasers.pop_back();
	}
}

void PlayScene::removeBonuses()
{
	if (listLightning.empty() != true)
	{
		listLightning.back()->removeBonus();
		//listLightning.pop_back();
		listLightning.clear();
	}
}
// update function: is called automatically by scheduleUpdate macro in initialize function

void PlayScene::update(float dt)
{
	// update character's position
	character->update(dt, isTouch, ableToJump,velocity);
	//set lại vận tốc khi điểm tăng
	/*if (score % 20 == 0)
	{
		velocity -= 0.1;
	}*/

	// add Laser after a random time
	srand(NULL);
	int time = random(1.5f, 2.5f);

	// add Laser
	//this->scheduleOnce(schedule_selector(PlayScene::addLaser, this), time);

	// add Score
	this->scheduleOnce(schedule_selector(PlayScene::addScore, this), 2.0f);

	// add Diamond and bonus
	srand(NULL);
	if (listLightning.empty() == true && listDiamond.empty() == true)
		this->scheduleOnce(schedule_selector(PlayScene::createBonusAndDiamond, this), random(2.5f, 7.5f));// chưa fix đc

	// if character touch laser 
	if (isDead)
	{
		this->removeChild(scoreLabel);
		this->pauseSchedulerAndActions();

		character->pauseSchedulerAndActions();

		/*auto childs = this->getChildren();
		for (auto child : childs)
		{
		child->removeFromParentAndCleanup(true);
		}*/

		auto overlayer = OverLayer::create();
		overlayer->setScore(score);

		overlayer->setPosition(0, 0);
		this->addChild(overlayer, 110);
	}

}