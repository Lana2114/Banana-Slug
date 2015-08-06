#include "MenuScene.h"
#include "PlayScene.h"
USING_NS_CC;

Scene* MenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Background

	auto gameTitle = Sprite::create("DoubleF.png");
	gameTitle->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 1.5 + origin.y);
	this->addChild(gameTitle);

	//Button

	auto playBtn = MenuItemImage::create("PlayBtn.png", "PlayBtnSelected.png", CC_CALLBACK_0(MenuScene::gotoPlayScene, this));
	auto menu = Menu::create(playBtn, nullptr);
	menu->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y);
	this->addChild(menu);

	return true;
}

void MenuScene::gotoPlayScene()
{
	auto playScene = PlayScene::createScene();
	Director::getInstance()->replaceScene(playScene);
}

