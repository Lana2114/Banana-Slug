#include "Character.h"

Character::Character(Layer* layer, Size visibleSize)
{
	//origin = Director::getInstance()->getVisibleOrigin();
	origin.x = 0;
	origin.y = 0;

	this->visibleSize = visibleSize;

	characterTexture = Sprite::create("pixel.png");
	characterTexture->setPosition(origin.x + visibleSize.width/2, characterTexture->getContentSize().height / 2);

	characterBody = PhysicsBody::createCircle(characterTexture->getContentSize().width / 2);
	characterBody->setCategoryBitmask(objectBitmask::CHARACTER);
	characterBody->setCollisionBitmask(objectBitmask::LAZER);
	characterBody->setContactTestBitmask(0x1);
	//characterBody->setDynamic(true);
	characterTexture->setPhysicsBody(characterBody);
	
	layer->addChild(characterTexture, 100);

	_move = false;
}

bool Character::isMoved()
{
	if (characterTexture->getPositionX() >= characterTexture->getContentSize().width
		|| characterTexture->getPositionX() <= characterTexture->getContentSize().width)
		_move = true;
	else
		_move = false;
	return _move;
}
void Character::moveLeft()
{
	auto moveLeft = MoveBy::create(0.8f,Vec2( -200, 0));
	auto easeOut = EaseOut::create(moveLeft, 2.0f);
	//if (characterTexture->getPositionX() <= characterTexture->getContentSize().width) // add Code
	//if (characterTexture->getPositionX() >= (characterTexture->getContentSize().width/2) + 400 )
	if (characterTexture->getPositionX() - 100 >= (characterTexture->getContentSize().width / 2))
	characterTexture->runAction(easeOut);
}

void Character::moveRight()
{
	auto moveRight = MoveBy::create(0.8f, Vec2(200, 0));
	auto easeOut = EaseOut::create(moveRight, 2.0f);
	if (characterTexture->getPositionX() + 100 <= visibleSize.width - (characterTexture->getContentSize().width / 2))
	characterTexture->runAction(easeOut);
}

void Character::jumpUp()
{
	auto jumpUp = JumpBy::create(0.5f, Vec2(0,0), 250, 1);
	characterTexture->runAction(jumpUp);
}