#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"
#include "HeroState.h"
#include "MapObject.h"
#include "GameMap.h"

class HeroStateManager;

struct HeroData
{
	union
	{
		int m_properties[9];

		struct
		{
			int m_Level;	
			int m_Hp;
			int m_Attack;
			int m_Defence;
			int m_Glod;
			int m_Exp;
			int m_keynum[3];
		};
	};
	
};
class Hero : public cocos2d::CCSprite
{
public:
	static Hero* create(const char *pszFileName);

	Hero();

	void collision(MapObject* object);
	
	bool can_move();
	bool can_fight();

	GameMap* m_curMap;

	bool excute(const char* command);

	bool MoveDirction(int direction);

	HeroData m_data;
private:
	//HeroStateManager m_curStateManager;
	//void moveEnd();
};

class HeroStateManager
{
public:
	HeroStateManager();
	~HeroStateManager();
	void change(HeroState* state);

	HeroState* getCurState();

private:
	HeroState* m_curState;
};
#endif