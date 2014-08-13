#ifndef _EnumHeroState_H_
#define _EnumHeroState_H_

/**
人物状态
**/
enum  EnumHeroState
{
	hero_State_Stand,		/*游戏开始以后静止不动*/
	hero_State_Stand2Jump,	/*第一次跳跃 从静止不动跳到左侧树*/
	hero_State_LeftReady,	/*左侧准备动作*/
	hero_State_Left2Right,	/*从左侧移动到右侧*/
	hero_State_RightReady,	/*右侧准备动作*/
	hero_State_Right2Left,	/*从右侧移动到左侧*/
	hero_State_Die			/*死亡*/
};

#endif 