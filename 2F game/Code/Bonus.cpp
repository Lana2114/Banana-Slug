#include "Bonus.h"

Bonus::Bonus(Layer* layer, Vec2 position)
{
	BonusTexture = Sprite::create("Bonus2.png");
	BonusTexture->setPosition(position);

	BonusBody = PhysicsBody::createCircle(BonusTexture->getContentSize().width / 2, PhysicsMaterial(0, 0, 0));
	BonusBody->setDynamic(false);
	BonusBody->setCategoryBitmask(objectBitmask::BONUS);
	BonusBody->setCollisionBitmask(0);
	BonusBody->setContactTestBitmask(objectBitmask::CHARACTER);

	BonusTexture->setPhysicsBody(BonusBody);

	layer->addChild(BonusTexture);
}

Bonus::~Bonus()
{

}

void Bonus::removeBonus()
{
	//BonusTexture->removeAllChildrenWithCleanup(true);
	BonusTexture->removeFromParent();
	BonusBody->removeFromWorld();
}

//void Bonus::removeBonus(float dt)
//{
//	//BonusTexture->removeAllChildrenWithCleanup(true);
//	if (BonusTexture != NULL && BonusBody != NULL)
//	{
//		BonusTexture->removeFromParent();
//		BonusBody->removeFromWorld();
//	}
//}