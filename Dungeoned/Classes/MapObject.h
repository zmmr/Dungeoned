#ifndef _MAPOBJECT_H_
#define _MAPOBJECT_H_

#include "cocos2d.h"

class Hero;
class MapObject : public cocos2d::CCObject
{
public:
	int x;
	int y;
	virtual bool active(Hero* hero) = 0;
};

class ItemObject : public MapObject
{
public:
	static ItemObject*  create(const char* command);
	bool active(Hero* hero);
private:
	const char* m_command;
};
struct EnemyInfo 
{
	int HP;
	int Defence;
	int Attack;
};
class EnemyObject : public MapObject
{
public:
	bool active(Hero* hero);
	static EnemyObject* create(EnemyInfo info);
private:
	EnemyInfo m_info;
};

class NPCObject : public MapObject
{
public:
	static NPCObject* create(const char* luaPath, const char* command); 
	bool active(Hero* hero);
private:
	const char* m_command;
	const char* m_luaPath;
};
#endif