#include "Character.h"

Character::Character(Layer* layer, Size visibleSize)
{
	//origin = Director::getInstance()->getVisibleOrigin();
	origin.x = 0;
	origin.y = 0;

	this->visibleSize = visibleSize;

	characterTexture = Sprite::create("pixel.png");
	characterTexture->setPosition(characterTexture->getContentSize().width/2 , characterTexture->getContentSize().height / 2);

	characterBody = PhysicsBody::createCircle(characterTexture->getContentSize().width / 2);
	characterBody->setCategoryBitmask(objectBitmask::CHARACTER);
	//characterBody->setCollisionBitmask(objectBitmask::LASER);
	characterBody->setContactTestBitmask(0x1);
	//characterBody->setDynamic(true);
	characterTexture->setPhysicsBody(characterBody);
	
	layer->addChild(characterTexture, 100);

}

void Character::jumpUp()
{
	auto jumpUp = JumpBy::create(0.5f, Vec2(0,0), 250, 1);
	characterTexture->runAction(jumpUp);
}


bool Character::isRight()
{
	if (characterTexture->getPositionX() >= 800 - characterTexture->getContentSize().width / 2)
		return true;
	else 
		return false;
}
void Character::update(float delta, bool &isTouched, bool &ableToJump)
{
	position = characterTexture->getPositionX();
	position -= 300 * delta *changeDirect;

	if (characterTexture->getPositionX() < 800 - characterTexture->getContentSize().width / 2
		&& characterTexture->getPositionX() > characterTexture->getContentSize().width / 2 - 1
		&& isTouched == false)
	{
		position += 10 * changeDirect;
	}
	else
	{
		position -= 10 * changeDirect;
		if (isTouched == true)
		{
			if (changeDirect == 1)
				changeDirect = -1;
			else
				changeDirect = 1;
		}
		else if (isRight() == true)
		{
			changeDirect = -1;
		}
		else
		{
			changeDirect = 1;
		}
		isTouched = false;
	}
	characterTexture->setPositionX(position);
	if (characterTexture->getContentSize().height / 2 + 10 < characterTexture->getPositionY())
	{
		ableToJump = false;
	}
	else
	{
		ableToJump = true;
	}
}