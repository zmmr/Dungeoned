#include "Hero.h"
#include <string.h>

using namespace cocos2d;
using namespace std;

Hero::Hero()
	:m_curMap(NULL)
{

}
void Hero::collision(MapObject* object)
{

	object->active(this);
}

bool Hero::excute(const char* command)
{
	if(command == NULL)return true;
	char tempcommand[32] ={0};
	strcpy(tempcommand, command);
	char* sub = strtok(tempcommand,":");
	int type = atoi(sub);
	char* sign = strtok(NULL,":");
	sub = strtok(NULL,":");

	if (strcmp(sign,"+") == 0)
	{
		m_data.m_properties[type] += atoi(sub);
	}
	else if (strcmp(sign,"-") == 0)
	{
		m_data.m_properties[type] -= atoi(sub);
		return m_data.m_properties[type] >= 0;
	}
	else if (strcmp(sign,"*") == 0)
	{
		m_data.m_properties[type] *= atoi(sub);
	}
	else if (strcmp(sign,"/") == 0)
	{
		m_data.m_properties[type] /= atoi(sub);
	}

	return true;
}

bool Hero::can_fight()
{
	return true;
}

bool Hero::can_move()
{
	return true;
}

bool Hero::MoveDirction(int direction)
{
	CCPoint offset[] = {ccp(0,1),ccp(-1,0),ccp(1,0),ccp(0,-1)};
	CCPoint tileCoord = m_curMap->tileCoordForPosition(getPosition());
	//获取目的地的坐标
	CCPoint targetTileCoord = tileCoord + offset[direction];
	//当这个Floor层在对应位置没有图块时，代表无法通行
	int targetID = m_curMap->getFloorLayer()->tileGIDAt(targetTileCoord);
	if (targetID == 0)return false;
	MapObject* object = m_curMap->getMapObject(targetTileCoord.x,targetTileCoord.y);
	if(object && !object->active(this))return false;

	CCPoint movetoPoint  = m_curMap->positionForTileCoord(targetTileCoord);
	runAction(CCMoveTo::create(0.5,movetoPoint));
}

Hero* Hero::create(const char *pszFileName)
{
	Hero* hero = new Hero;
	if (hero && hero->initWithFile(pszFileName))
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return NULL;
}