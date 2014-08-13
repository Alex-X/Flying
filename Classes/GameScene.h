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

	//��ʼ������
	void initBackground();
	//��ʼ��������
	void initEnergyBar();
	//�ƶ�������������ͼƬ
	void moveBar(float dt);
	//������Ծ����
	void jumpEnd();
	//����׼��������׼��
	void ready();
	//������Ծ�ĽǶ�
	void timer(float dt);

public:
	//���ƶ���������������װ��һ������
	void moveRightOrLeftBar(int speed,Sprite* bar1,Sprite* bar2);

public:
	//��һ������
	void heroFirstJump();
	//������
	void heroJumpRight();
	//������
	void heroJumpLeft();


public:
	//����
	Sprite * leftBar;
	//����
	Sprite * rightBar;
	//����
	Sprite * background;
	//����������Ϊ�˱�������
	//����2
	Sprite * background2;
	//����2
	Sprite* leftBar2;
	//����2
	Sprite* rightBar2;
	//yӢ��
	Sprite * hero;
	//��Ļ��С
	Size size;
	//�ز���С�Ŵ���
	float scale;
	//�Ƿ��ǵ�һ������
	bool isFirst;
	//at left = 1 or right =2
	int flag;

	SpriteFrameCache* frameCache;
	//��Ծ��
	bool isFlying;

	//���������ٶ�
	float speed;
	//��ʾ��ǰ�ٶȣ���ʱ��
	Label *speedLabel;
	
	//��Ծʱ��
	float flyTime;
	//׼��ʱ��
	float readyTime;
};

#endif // __HELLOWORLD_SCENE_H__
