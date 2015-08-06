#ifndef _LASER_H_
#define _LASER_H_

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include "Character.h"
USING_NS_CC;
using namespace cocostudio;

class Laser : public Layer
{
private:
	cocostudio::Armature* armature1;
	cocostudio::Armature* armature2;
	Vec2 origin;
	Sprite* laserTexture;
	Sprite* laserTop;
	PhysicsBody* laserBody;
	int laserPosition;
public:
	Laser(Layer *layer, Size visibleSize, Vec2 position);
	void removeLaser();
	void isMoveFinished();
};
#endif //_LASER_H_