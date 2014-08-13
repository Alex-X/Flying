#include "Hero.h"
#include "PlistLoader.h"
#include "AnimationTool.h"
#include "GameScene.h"


Hero* Hero::create(const char *filename)
{
	Hero* hero = new Hero();
	if(hero&&hero->initWithFile(filename))
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}


void Hero::heroFirstJump(Point targetPoint)
{
	Vector<SpriteFrame*> frameArray;
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("fly"));
	Animate* flyAnimation = AnimationTool::createAnimateBySpriteFrames(frameArray,0.4);
	
	frameArray.clear();
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("left1"));
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("left2"));
	Animate* animation = AnimationTool::createAnimateBySpriteFrames(frameArray,0.3);
	this->runAction(Sequence::create(Spawn::create(MoveTo::create(0.4,targetPoint),flyAnimation,NULL),CallFunc::create(this,callfunc_selector(GameScene::jumpEnd)),animation,CallFunc::create(this,callfunc_selector(GameScene::ready)),NULL));

}

void Hero::heroJumpLeft(Point targetPoint)
{
	Vector<SpriteFrame*> frameArray;
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("fly2"));
	Animate* flyAnimation = AnimationTool::createAnimateBySpriteFrames(frameArray,0.4);
	
	frameArray.clear();
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("right1"));
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("right2"));
	Animate* animation = AnimationTool::createAnimateBySpriteFrames(frameArray,0.3);

	this->runAction(Sequence::create(Spawn::create(MoveTo::create(0.4,targetPoint),flyAnimation,NULL),CallFunc::create(this,callfunc_selector(GameScene::jumpEnd)),animation,CallFunc::create(this,callfunc_selector(GameScene::ready)),NULL));

}

void Hero::heroJumpRight(Point targetPoint)
{
	Vector<SpriteFrame*> frameArray;
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("fly"));
	Animate* flyAnimation = AnimationTool::createAnimateBySpriteFrames(frameArray,0.4);
	
	frameArray.clear();
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("left1"));
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("left2"));
	Animate* animation = AnimationTool::createAnimateBySpriteFrames(frameArray,0.3);

	this->runAction(Sequence::create(Spawn::create(MoveTo::create(0.4,targetPoint),flyAnimation,NULL),CallFunc::create(this,callfunc_selector(GameScene::jumpEnd)),animation,CallFunc::create(this,callfunc_selector(GameScene::ready)),NULL));

}

void Hero::die()
{
	Vector<SpriteFrame*> frameArray;
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("Hero"));
	Animate* animate = AnimationTool::createAnimateBySpriteFrames(frameArray,0.4);
	this->runAction(animate);
}