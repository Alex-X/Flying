#include "GameScene.h"
#include "Hero.h"
#include "PlistLoader.h"
#include "AnimationTool.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	size = Director::getInstance()->getVisibleSize();
	scale = size.height/960;
	isFirst = true;
	flag = 0;
	flyTime = 0.8f;
	readyTime = 0.4f;

	initBackground();
	isFlying = false;

	//TouchEventListener
	auto touchEventListener = EventListenerTouchOneByOne::create();
	touchEventListener->onTouchBegan = [this](Touch* t, Event* e)
	{
		if(isFlying)
			return false;
		isFlying = true;
		//触发背景滚动  给人一种hero往上跳跃的感觉
		schedule(schedule_selector(GameScene::moveBar),0.01f);
		if(isFirst){
			heroFirstJump();
			speed = 10;
		}
		else
		{
			//如果不是第一次跳的话  在人物起跳前有个计算跳跃高度的计时器，在这需要停止 计算出speed
			unschedule(schedule_selector(GameScene::timer));
			log("%f",speed);
			if(flag == 1)
			{
				heroJumpRight();
			}
			else if(flag == 2)
			{
				heroJumpLeft();
			}
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEventListener,this);
	return true;
}


void GameScene::jumpEnd()
{
	//跳跃结束表现形式：背景停止滚动
	unschedule(schedule_selector(GameScene::moveBar));
	speed = 0;
}

void GameScene::ready()
{
	isFlying = false;
	//做完准备动作以后开始触发 计算speed的计时器 ，在用户下一次点击屏幕的时候 停止当前计时器
	schedule(schedule_selector(GameScene::timer),0.01f);
}

void GameScene::timer(float dt)
{
	if(speed < 90)
	{
		speed = speed+1;
		speedLabel->setString(StringUtils::format("%0.2f",speed));
	}
}

void GameScene::moveBar(float dt)
{
	moveRightOrLeftBar(speed,leftBar,leftBar2);
	moveRightOrLeftBar(speed,rightBar,rightBar2);
	moveRightOrLeftBar(speed/4,background,background2);
}

//背景滚动
void GameScene::moveRightOrLeftBar(int speed,Sprite* bar1,Sprite* bar2)
{
	int y1 = bar1->getPositionY();
	int y2 = bar2->getPositionY();
	y1 -= speed;
	y2 -= speed;
	Size barSize = bar1->getContentSize();
	if(y1 < -barSize.height*scale)
	{
		y2 = 0;
		y1 = barSize.height*scale;
	}
	if(y2 < -barSize.height*scale)
	{
		y1 = 0;
		y2 = barSize.height*scale;
	}
	bar1->setPositionY(y1);
	bar2->setPositionY(y2);
}


void GameScene::initBackground()
{

	speedLabel = Label::create();
	speedLabel->setSystemFontSize(20);
	speedLabel->setColor(Color3B::BLACK);
	speedLabel->setPosition(size.width/2,size.height/2);
	addChild(speedLabel,1);

	leftBar = Sprite::create("leftBar.png");
	leftBar->setScale(scale);
	leftBar->setAnchorPoint(Vec2(0,0));
	leftBar->setPosition(Vec2(0,0));
	this->addChild(leftBar,1);

	leftBar2 = Sprite::create("leftBar.png");
	leftBar2->setScale(scale);
	leftBar2->setAnchorPoint(Vec2(0,0));
	leftBar2->setFlipY(true);
	leftBar2->setPosition(Vec2(0,leftBar2->getContentSize().height*scale));
	this->addChild(leftBar2,1);

	rightBar = Sprite::create("rightBar.png");
	rightBar->setScale(scale);
	rightBar->setAnchorPoint(Vec2(0,0));
	rightBar->setPosition(Vec2(size.width-(rightBar->getContentSize().width*scale),0));
	this->addChild(rightBar,1);

	rightBar2 = Sprite::create("rightBar.png");
	rightBar2->setScale(scale);
	rightBar2->setFlipY(true);
	rightBar2->setAnchorPoint(Vec2(0,0));
	rightBar2->setPosition(Vec2(size.width-(rightBar->getContentSize().width*scale),leftBar2->getContentSize().height*scale));
	this->addChild(rightBar2,1);

	background = Sprite::create("background.png");
	background->setScale(scale);
	background->setAnchorPoint(Vec2(0,0));
	background->setPosition(Vec2(0,0));
	this->addChild(background,0);

	background2 = Sprite::create("background.png");
	background2->setScale(scale);
	background2->setAnchorPoint(Vec2(0,0));
	background2->setPosition(Vec2(0,background2->getContentSize().height*scale));
	this->addChild(background2,0);


	hero = Sprite::create("Hero.png");
	hero->setScale(scale);
	Size heroSize = hero->getContentSize();
	hero->setAnchorPoint(Vec2(0,0));
	hero->setPosition(Vec2(size.width/2-(heroSize.width/2*scale),0));
	this->addChild(hero,1);
}

//第一次跳  跳到左边柱子上
void GameScene::heroFirstJump()
{
	Point targetPoint= Point(leftBar->getContentSize().width*scale-(hero->getContentSize().width*scale/2),(size.height-hero->getContentSize().height*scale)/2);
	isFirst = false;
	flag =1;

	Vector<SpriteFrame*> frameArray;
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("fly"));
	Animate* flyAnimation = AnimationTool::createAnimateBySpriteFrames(frameArray,flyTime);
	frameArray.clear();
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("left1"));
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("left2"));
	Animate* animation = AnimationTool::createAnimateBySpriteFrames(frameArray,readyTime);
	hero->runAction(Sequence::create(Spawn::create(MoveTo::create(flyTime,targetPoint),flyAnimation,NULL),CallFunc::create(this,callfunc_selector(GameScene::jumpEnd)),animation,CallFunc::create(this,callfunc_selector(GameScene::ready)),NULL));

}

void GameScene::heroJumpRight()
{
	Point targetPoint = Point(size.width-(rightBar->getContentSize().width*scale)-(hero->getContentSize().width*scale/2),(size.height-hero->getContentSize().height*scale)/2);
	flag = 2;


	Vector<SpriteFrame*> frameArray;
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("fly2"));
	Animate* flyAnimation = AnimationTool::createAnimateBySpriteFrames(frameArray,flyTime);
	frameArray.clear();
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("right1"));
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("right2"));
	Animate* animation = AnimationTool::createAnimateBySpriteFrames(frameArray,readyTime);

	hero->runAction(Sequence::create(Spawn::create(MoveTo::create(flyTime,targetPoint),flyAnimation,NULL),CallFunc::create(this,callfunc_selector(GameScene::jumpEnd)),animation,CallFunc::create(this,callfunc_selector(GameScene::ready)),NULL));
}

void GameScene::heroJumpLeft()
{
	Point targetPoint =Point(leftBar->getContentSize().width*scale-(hero->getContentSize().width*scale/2),(size.height-hero->getContentSize().height*scale)/2);
	flag = 1;

	Vector<SpriteFrame*> frameArray;
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("fly"));
	Animate* flyAnimation = AnimationTool::createAnimateBySpriteFrames(frameArray,flyTime);
	frameArray.clear();
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("left1"));
	frameArray.pushBack(PlistLoader::getInstance()->getSpriteFrameByName("left2"));
	Animate* animation = AnimationTool::createAnimateBySpriteFrames(frameArray,readyTime);

	hero->runAction(Sequence::create(Spawn::create(MoveTo::create(flyTime,targetPoint),flyAnimation,NULL),CallFunc::create(this,callfunc_selector(GameScene::jumpEnd)),animation,CallFunc::create(this,callfunc_selector(GameScene::ready)),NULL));

}

