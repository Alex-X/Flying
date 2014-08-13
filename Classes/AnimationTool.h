#ifndef _Flying_AnimationTool_
#define _Flying_AnimationTool_

#include <iostream>
#include <cocos2d.h>

USING_NS_CC;

class AnimationTool
{
public:
	static Animate* createAnimateBySpriteFrames(Vector<SpriteFrame*> frameArray,float delayPerUnit);
};

#endif