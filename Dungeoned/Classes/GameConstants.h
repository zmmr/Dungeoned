#ifndef _GAME_CONSTRANTS_H_
#define _GAME_CONSTRANTS_H_

enum Direction
{
	Direction_Down,
	Direction_Left,
	Direction_Right,
	Direction_Up,
	Direction_Max
};

enum EnumHeroState
{
	State_IDLE,
	State_Move,
	State_Fight
};

//碰撞类型
enum CollisionType
{
	CollisionType_None,
	CollisionType_Wall,
	CollisionType_Enemy,
	CollisionType_Item,
	CollisionType_Door,
	CollisionType_NPC,
	CollisionType_Teleport
};

enum MapZOrder
{
	MapZOrder_Map = 0,//地图的zOrder
	MapZOrder_NPC,	//NPC
	MapZOrder_Teleport,	//传送点
	MapZOrder_Hero,//勇士精灵的zOrder
	MapZOrder_Tip,//提示信息的zOrder
};
#endif