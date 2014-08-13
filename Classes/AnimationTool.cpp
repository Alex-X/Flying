#include "AnimationTool.h"

Animate* AnimationTool::createAnimateBySpriteFrames(Vector<SpriteFrame*> frameArray,float delayPerUnit)
{
	/* ʹ��SpriteFrame�б����������� */
	auto animation = Animation::createWithSpriteFrames(frameArray);

	animation->setLoops(1);

	animation->setDelayPerUnit(delayPerUnit);

	/* ��������װ��һ������ */
	return Animate::create(animation);

}