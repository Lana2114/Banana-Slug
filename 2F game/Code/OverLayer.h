#ifndef __OVER_LAYER_H__
#define __OVER_LAYER_H__

#include "cocos2d.h"
#include "MenuScene.h"
#include "PlayScene.h"

USING_NS_CC;

class OverLayer : public cocos2d::Layer
{
public:
    virtual bool init();
	CREATE_FUNC(OverLayer);

	void setScore(int _score);
	//void setHighScore(int _score);

private:
	void gotoMenuScene(); 
	void gotoPlayScene();
	int score;
	int highScore;
	Label *scoreLabel;
	Label *highScoreLabel;
};

#endif // __OVER_LAYER_H__
