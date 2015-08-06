#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "PlayScene.h"

class MenuScene : public cocos2d::LayerColor
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void gotoPlayScene();

	// implement the "static create()" method manually
	CREATE_FUNC(MenuScene);
};

#endif // __MENU_SCENE_H__