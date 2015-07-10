#include "Pixel.h"

Pixel::Pixel(Layer* layer)
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	pixelTexture = Sprite::create("pixel.png");
	pixelTexture->setPosition(20, origin.y+visibleSize.height/1.5);
	
	pixelBody = PhysicsBody::createCircle(pixelTexture->getContentSize().width / 2);
	pixelBody->setCategoryBitmask(eObjectBitmask::PIXEL);
	pixelBody->setCollisionBitmask(eObjectBitmask::FLOOR);
	pixelBody->setContactTestBitmask(eObjectBitmask::FLOOR);
	pixelBody->setDynamic(false);

	pixelTexture->setPhysicsBody(pixelBody);

	auto moveTo = MoveTo::create(1.5f, Vec2(460, origin.y + visibleSize.height / 1.5));
	auto moveTo2 = MoveTo::create(1.5f, Vec2(20, origin.y + visibleSize.height / 1.5));
	auto sequence = Sequence::create(moveTo, moveTo2, nullptr);
	pixelTexture->runAction(RepeatForever::create(sequence));
	layer->addChild(pixelTexture,100);

	isContact = true;
}

void Pixel::update()
{
	if (isContact == true)
	{
		
	}
}
