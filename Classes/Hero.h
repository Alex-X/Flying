#ifndef _Flying_Hero_
#define _Flying_Hero_

#include "cocos2d.h"
USING_NS_CC;

class Hero : public Sprite
{
public:
	static Hero *create(const char *pszFileName);

public:
	void heroFirstJump(Point targetPoint);
	void heroJumpRight(Point targetPoint);
	void heroJumpLeft(Point targetPoint);
	void die();
};

#endif