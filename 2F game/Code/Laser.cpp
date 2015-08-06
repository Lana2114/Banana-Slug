#include "Laser.h"
#include "cocos2d.h"
#include "cocostudio\CCArmatureDataManager.h"
#include "cocostudio\CCArmature.h"

using namespace std;
USING_NS_CC;
using namespace cocostudio;

Laser::Laser(Layer* layer, Size visibleSize, Vec2 position)
{
	origin.x = origin.y = 0;
	//isMoveFinished = false;

	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Laser/LaserReady0.png", "Laser/LaserReady0.plist", "Laser/LaserReady.ExportJson");
	armature1 = Armature::create("LaserReady");
	armature1->getAnimation()->playByIndex(0);
	armature1->setPosition(position);

	Sprite* temp = Sprite::create("Laser/Laser0.png");

	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Laser/Laser0.png", "Laser/Laser0.plist", "Laser/Laser.ExportJson");
	armature2 = Armature::create("Laser");
	armature2->getAnimation()->playByIndex(0);
	armature2->setPosition(position);
	// block code
	//laserBody = PhysicsBody::createBox(Size(armature2->getContentSize().width, armature2->getContentSize().height), PhysicsMaterial(0, 0, 0));
	laserBody = PhysicsBody::createBox(Size(temp->getContentSize().width/4, temp->getContentSize().height),
		PhysicsMaterial(0, 0, 0));
	laserBody->setCategoryBitmask(objectBitmask::LASER);
	laserBody->setCollisionBitmask(objectBitmask::CHARACTER);
	laserBody->setContactTestBitmask(objectBitmask::CHARACTER);
	laserBody->setDynamic(false);
	armature2->setPhysicsBody(laserBody);

	layer->addChild(armature1);
	layer->addChild(armature2);

	//isMoveFinished = true;
}

void Laser::isMoveFinished()
{
	laserBody->removeFromWorld();
}
void Laser::removeLaser()
{
	armature2->runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create(CC_CALLBACK_0(Laser::isMoveFinished, this)), NULL));
}