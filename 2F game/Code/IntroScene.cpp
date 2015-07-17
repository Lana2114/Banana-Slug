#include "IntroScene.h"

USING_NS_CC;

Scene* IntroScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = IntroScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool IntroScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto label = Label::createWithTTF("Doggy & Kitten", "fonts/Marker Felt.ttf", 50);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height/2));

	// add the label as a child to this layer
	this->addChild(label, 1);

	this->scheduleOnce(schedule_selector(IntroScene::gotoMenuScene), 1.0f);

	return true;
}

void IntroScene::gotoMenuScene(float dt)
{
	auto menuScene = MenuScene::createScene();
	Director::getInstance()->replaceScene(menuScene);
}

