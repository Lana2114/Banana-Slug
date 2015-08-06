#include "Character.h"

Character::Character(Layer* layer, Size visibleSize)
{
	//origin = Director::getInstance()->getVisibleOrigin();
	origin.x = 0;
	origin.y = 0;
	changeDirect = 1;
	this->visibleSize = visibleSize;

	characterTexture = Sprite::create("pixel.png");
	characterTexture->setPosition(origin.x + visibleSize.width / 2, characterTexture->getContentSize().height / 2);

	characterBody = PhysicsBody::createCircle(characterTexture->getContentSize().width / 2);
	characterBody->setCategoryBitmask(objectBitmask::CHARACTER);
	//characterBody->setCollisionBitmask(objectBitmask::LASER|objectBitmask::DIAMOND);
	characterBody->setContactTestBitmask(objectBitmask::LASER | objectBitmask::DIAMOND | objectBitmask::BONUS);
	//characterBody->setDynamic(false);
	characterTexture->setPhysicsBody(characterBody);

	layer->addChild(characterTexture, 100);

	isDead = false;
}

void Character::jumpUp()
{
	auto jumpUp = JumpBy::create(0.5f, Vec2(0, 0), visibleSize.height / 2, 1);
	characterTexture->runAction(jumpUp);
}

float Character::getPositionX()
{
	return characterTexture->getPositionX();
}
void Character::setPositionX(float position)
{
	characterTexture->setPositionX(position);
}
float Character::getContentSizeX()
{
	return characterTexture->getContentSize().width;
}
bool Character::isRight()
{
	if (characterTexture->getPositionX() >= visibleSize.width - characterTexture->getContentSize().width / 2)
		return true;
	else false;
}

void Character::update(float delta, bool &isTouched, bool &ableToJump, float &velocity)
{
	auto position = characterTexture->getPositionX();
	if (velocity > 0)
	{
		position -= velocity * delta *changeDirect;
	}
	else
	{
		position -= delta *changeDirect;

	}
	if (characterTexture->getPositionX() < visibleSize.width - characterTexture->getContentSize().width / 2
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

	if (characterTexture->getContentSize().height / 2 + 3 < characterTexture->getPositionY())
	{
		ableToJump = false;
	}
	else
	{
		ableToJump = true;
	}
}
