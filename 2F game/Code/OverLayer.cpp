#include "OverLayer.h"

void OverLayer::setScore(int _score)
{
	score = _score;
	scoreLabel->setString(String::createWithFormat("SCORE: %d", score)->getCString());

	auto userdefault = UserDefault::getInstance();
	auto highscore = userdefault->getIntegerForKey("HIGHSCORE", 0);
	//So sánh điểm mới với highscore
	if (_score > highscore)
	{
		//nếu mà lớn hơn thì mình sẽ set nó lại
		highscore = _score;
		userdefault->setIntegerForKey("HIGHSCORE", highscore);
	}
	//Xong mình save nó
	userdefault->flush();
	highScoreLabel->setString(__String::createWithFormat("HIGH SCORE: %d", highscore)->getCString());
}

bool OverLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
    /////////////////////////////

	auto overBG = Sprite::create("Images/OverLayerBG.png");
	overBG->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->addChild(overBG,0);

	auto overPanel = Sprite::create("Scenes/GameOverPanel.png");
	overPanel->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 60 * visibleSize.width / visibleSize.height));

	this->addChild(overPanel);
	
	Label *gameOverLabel;
	gameOverLabel = Label::createWithTTF("GAME OVER", "fonts/icielpanton-light.otf", 60);
	gameOverLabel->setPosition(0 + visibleSize.width / 2, visibleSize.height - 2 * gameOverLabel->getContentSize().height);
	this->addChild(gameOverLabel);

	//Score
	scoreLabel = Label::createWithTTF("0", "fonts/icielpanton-light.otf", 35);
	scoreLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	scoreLabel->setPosition(origin.x + visibleSize.width / 4, overPanel->getPositionY() + 60 * visibleSize.width / visibleSize.height);
	this->addChild(scoreLabel);
	
	highScoreLabel = Label::createWithTTF("0", "fonts/icielpanton-light.otf", 35);
	highScoreLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	highScoreLabel->setPosition(origin.x + visibleSize.width / 4, overPanel->getPositionY() - 60 * visibleSize.width / visibleSize.height);
	this->addChild(highScoreLabel);
	
	//Button
	auto menuBtn = MenuItemImage::create("btn/MenuBtn.png", "btn/MenuBtnSelected.png", CC_CALLBACK_0(OverLayer::gotoMenuScene, this));
	auto scaleTo = ScaleTo::create(0.0f, 1.5f);
	menuBtn->runAction(scaleTo);
	auto replayBtn = MenuItemImage::create("btn/ReplayBtn.png", "btn/ReplayBtnSelected.png", CC_CALLBACK_0(OverLayer::gotoPlayScene, this));
	auto scaleTo2 = ScaleTo::create(0.0f, 1.5f);
	replayBtn->runAction(scaleTo2);
	auto menu = Menu::create(menuBtn, replayBtn, nullptr);
	menu->alignItemsHorizontallyWithPadding(50);

	menu->setPosition(origin.x + visibleSize.width / 2, overPanel->getPositionY() - 400 * visibleSize.width / visibleSize.height);

	this->addChild(menu);

    return true;
}

void OverLayer::gotoMenuScene()
{
	auto menuscene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInT::create(0.25f, menuscene));
	
}

void OverLayer::gotoPlayScene()
{
	auto playscene = PlayScene::createScene();
	Director::getInstance()->replaceScene(playscene);
}
