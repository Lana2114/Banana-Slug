#include "Floor.h"
#include "Pixel.h"

Floor::Floor(Layer* layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0; i < 192; i++)
	{
		floorTexture = cocos2d::Sprite::create("_floor.png");
		
		if (i < 24)
		{
			floorTexture->setPosition(CCPoint((20*i+10), visibleSize.height/80));
		}
		else if (i >= 24 && i < 48)
		{
			floorTexture->setPosition(CCPoint(20 * (i - 24)+10, visibleSize.height/26.7));
		}
		else if (i >= 48 && i < 72)
		{
			floorTexture->setPosition(CCPoint(20 * (i - 48) + 10, visibleSize.height/3.29));
		}
		else if (i >= 72 && i < 96)
		{
			floorTexture->setPosition(CCPoint(20 * (i - 72) + 10, visibleSize.height / 3.04));
		}
		else if (i >= 96 && i < 120)
		{
			floorTexture->setPosition(CCPoint(20 * (i - 96) + 10, visibleSize.height / 1.646));
		}
		else if (i >= 120 && i < 144)
		{
			floorTexture->setPosition(CCPoint(20 * (i - 120) + 10, visibleSize.height / 1.581));
		}
		else if (i >= 144 && i < 168)
		{
			floorTexture->setPosition(CCPoint(20 * (i - 144) + 10, visibleSize.height / 1.097));
		}
		else
		{
			floorTexture->setPosition(CCPoint(20 * (i - 168) + 10, visibleSize.height / 1.068));
		}
		//floor->setTag(i);

		floorBody = cocos2d::PhysicsBody::createBox(floorTexture->getContentSize(), PhysicsMaterial(0, 0, 0));
		floorBody->setDynamic(false);
		floorBody->setCategoryBitmask(eObjectBitmask::FLOOR);
		floorBody->setCollisionBitmask(eObjectBitmask::PIXEL);
		floorBody->setContactTestBitmask(eObjectBitmask::PIXEL);

		floorTexture->setPhysicsBody(floorBody);

		MyFloor.push_back(floorTexture);

		layer->addChild(floorTexture,1);
	}
	
}

//void Floor::removeFloor()
//{
//	floorTexture->removeFromParent();
//}

