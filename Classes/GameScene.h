#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameScene : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();  
 
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(GameScene);

	//初始化背景
	void initBackground();
	//初始化能量条
	void initEnergyBar();
	//移动左右树跟背景图片
	void moveBar(float dt);
	//左右跳跃结束
	void jumpEnd();
	//做出准备起跳的准备
	void ready();
	//计算跳跃的角度
	void timer(float dt);

public:
	//将移动左右树跟背景封装的一个方法
	void moveRightOrLeftBar(int speed,Sprite* bar1,Sprite* bar2);

public:
	//第一次起跳
	void heroFirstJump();
	//向右跳
	void heroJumpRight();
	//向左跳
	void heroJumpLeft();


public:
	//左树
	Sprite * leftBar;
	//右树
	Sprite * rightBar;
	//背景
	Sprite * background;
	//以下两个是为了背景滚动
	//背景2
	Sprite * background2;
	//左树2
	Sprite* leftBar2;
	//右树2
	Sprite* rightBar2;
	//y英雄
	Sprite * hero;
	//屏幕大小
	Size size;
	//素材缩小放大倍数
	float scale;
	//是否是第一次起跳
	bool isFirst;
	//at left = 1 or right =2
	int flag;

	SpriteFrameCache* frameCache;
	//跳跃中
	bool isFlying;

	//背景滚动速度
	float speed;
	//显示当前速度（临时）
	Label *speedLabel;
	
	//跳跃时间
	float flyTime;
	//准备时间
	float readyTime;
};

#endif // __HELLOWORLD_SCENE_H__
