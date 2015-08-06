#include "Lightning.h"
#include "MyBodyParser.h"

Lightning::Lightning(Layer* layer, Vec2 position)
{
	LightningTexture = Sprite::create("Bonus2.png");
	LightningTexture->setPosition(position);

	MyBodyParser::getInstance()->parseJsonFile("2Fgame.json");
	LightningBody = MyBodyParser::getInstance()->bodyFormJson(LightningTexture, "lightning", PhysicsMaterial(0, 0, 0));
	LightningBody->setDynamic(false);
	LightningBody->setCategoryBitmask(objectBitmask::BONUS);
	LightningBody->setCollisionBitmask(0);
	LightningBody->setContactTestBitmask(objectBitmask::CHARACTER);

	LightningTexture->setPhysicsBody(LightningBody);

	layer->addChild(LightningTexture);
}

Lightning::~Lightning()
{

}

void Lightning::removeBonus()
{
	//LightningTexture->removeAllChildrenWithCleanup(true);
	LightningTexture->removeFromParent();
	LightningBody->removeFromWorld();
}