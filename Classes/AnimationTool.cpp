#include "AnimationTool.h"

Animate* AnimationTool::createAnimateBySpriteFrames(Vector<SpriteFrame*> frameArray,float delayPerUnit)
{
	/* 使用SpriteFrame列表创建动画对象 */
	auto animation = Animation::createWithSpriteFrames(frameArray);

	animation->setLoops(1);

	animation->setDelayPerUnit(delayPerUnit);

	/* 将动画包装成一个动作 */
	return Animate::create(animation);

}