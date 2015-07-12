#include "Pixel.h"

Pixel::Pixel(Layer* layer)
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	pixelTexture = Sprite::create("pixel.png");
	pixelTexture->setPosition(origin.x+visibleSize.width/24, origin.y+visibleSize.height/1.5);
	
	pixelBody = PhysicsBody::createCircle(pixelTexture->getContentSize().width / 2);
	pixelBody->setCategoryBitmask(eObjectBitmask::PIXEL);
	pixelBody->setCollisionBitmask(eObjectBitmask::FLOOR);
	pixelBody->setContactTestBitmask(eObjectBitmask::FLOOR);
	pixelBody->setDynamic(false);

	pixelTexture->setPhysicsBody(pixelBody);

	auto moveTo = MoveTo::create(1.5f, Vec2(origin.x+visibleSize.width/(24/23), origin.y + visibleSize.height / 1.5));
	auto moveTo2 = MoveTo::create(1.5f, Vec2(origin.x + visibleSize.width / 24, origin.y + visibleSize.height / 1.5));
	auto sequence = Sequence::create(moveTo, moveTo2, nullptr);
	pixelTexture->runAction(RepeatForever::create(sequence));
	
	layer->addChild(pixelTexture,100);

}

void Pixel::jumpUp()
{
	auto jumpTo = JumpTo::create(0.5, pixelTexture->getPosition(), visibleSize.height/(20/3), 1);
	pixelTexture->runAction(jumpTo);

}

