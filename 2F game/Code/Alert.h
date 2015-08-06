#ifndef _ALERT_H_
#define _ALERT_H_

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include "Character.h"
USING_NS_CC;
using namespace cocostudio;

class Alert : public Layer
{
private:
	cocostudio::Armature* armature;
	//Sprite* laserTexture;
public:
	Alert(Layer *layer, Size visibleSize, Vec2 position);
	void removeAlert();
	void moveFinished();
};
#endif //_ALERT_H_