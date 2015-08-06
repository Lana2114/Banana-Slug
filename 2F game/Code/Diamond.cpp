#include "Diamond.h"
#include "MyBodyParser.h"

Diamond::Diamond(Layer* layer, Vec2 position)
{
	diamondTexture = Sprite::create("Diamond2.png");
	diamondTexture->setPosition(position);

	MyBodyParser::getInstance()->parseJsonFile("2Fgame.json");
	diamondBody = MyBodyParser::getInstance()->bodyFormJson(diamondTexture, "diamond", PhysicsMaterial(0, 0, 0));
	diamondBody->setDynamic(false);
	diamondBody->setCategoryBitmask(objectBitmask::DIAMOND);
	diamondBody->setCollisionBitmask(0);
	diamondBody->setContactTestBitmask(objectBitmask::CHARACTER);

	diamondTexture->setPhysicsBody(diamondBody);

	layer->addChild(diamondTexture);
}

Diamond::~Diamond()
{

}

void Diamond::removeDiamond()
{
	//diamondTexture->removeAllChildrenWithCleanup(true);
	diamondTexture->removeFromParent();
	diamondBody->removeFromWorld();
}