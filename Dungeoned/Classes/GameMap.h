#ifndef _GAMEMAP_H_
#define _GAMEMAP_H_

#include "cocos2d.h"
#include "MapObject.h"

class GameMap : public cocos2d::CCTMXTiledMap
{
	//ֻ����������ȡ�ذ�㡢ǽ�ڲ㡢�����...
	CC_PROPERTY_READONLY(cocos2d::CCTMXLayer*,floorLayer,FloorLayer);
	//CC_PROPERTY_READONLY(cocos2d::CCTMXLayer*,wallLayer,WallLayer);
	//CC_PROPERTY_READONLY(cocos2d::CCTMXLayer*,enemyLayer,EnemyLayer);
	//CC_PROPERTY_READONLY(cocos2d::CCTMXLayer*,itemLayer,ItemLayer);
	CC_PROPERTY_READONLY(cocos2d::CCTMXLayer*,doorLayer,DoorLayer);
public:
	GameMap();

	static GameMap* create(const char *tmxFile);
	//TiledMap��cocos2d-x����ϵ�໥ת���ķ���
	cocos2d::CCPoint tileCoordForPosition(cocos2d::CCPoint position);
	cocos2d::CCPoint positionForTileCoord(cocos2d::CCPoint tileCoord);

	MapObject* getMapObject(int x, int y);

	void clearMapObject(int x, int y);
protected:
	//TiledMap����ĳ�ʼ������
	void extraInit();
private:
	
	MapObject* **m_objects;
};
#endif