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

//��ײ����
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
	MapZOrder_Map = 0,//��ͼ��zOrder
	MapZOrder_NPC,	//NPC
	MapZOrder_Teleport,	//���͵�
	MapZOrder_Hero,//��ʿ�����zOrder
	MapZOrder_Tip,//��ʾ��Ϣ��zOrder
};
#endif