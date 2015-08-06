#include "Alert.h"
#include "cocos2d.h"
#include "cocostudio\CCArmatureDataManager.h"
#include "cocostudio\CCArmature.h"

using namespace std;
USING_NS_CC;
using namespace cocostudio;

Alert::Alert(Layer* layer, Size visibleSize, Vec2 position)
{
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Alert/Alert0.png", "Alert/Alert0.plist", "Alert/Alert.ExportJson");
	armature = Armature::create("Alert");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(position);
	layer->addChild(armature);
}

void Alert::removeAlert()
{
	//armature2->runAction(Sequence::create(DelayTime::create(0.1),CallFunc::create(CC_CALLBACK_0(Alert::isMoveFinished, this)), NULL));
	armature->removeFromParent();
}