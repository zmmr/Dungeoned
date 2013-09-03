#include "GameMap.h"
#include "MapObjectDataManager.h"

using namespace cocos2d;

GameMap::GameMap()
{

}

GameMap* GameMap::create(const char *tmxFile)
{
	GameMap* pRet = new GameMap;
	if (pRet && pRet->initWithTMXFile(tmxFile))
	{
		pRet->extraInit();
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CCTMXLayer* GameMap::getFloorLayer()
{
	return floorLayer;
}

CCTMXLayer* GameMap::getDoorLayer()
{
	return doorLayer;
}

void GameMap::extraInit()
{
	int col = getMapSize().width;
	int row = getMapSize().height;

	m_objects = new MapObject* *[row];
	for (int i = 0; i< row; i++)
	{
		m_objects[i] = new MapObject* [col];
		for (int j = 0; j < col; j++)
		{
			m_objects[i][j] = NULL;
		}
	}

	floorLayer = layerNamed("floor");
	const char* possibleLayer[] = {
		"glost",
		"glost2",
		"3",
		"key",
	};
	for (int i = 0; i<4;i++)
	{
		CCTMXLayer* layer = layerNamed(possibleLayer[i]);
		if (layer)
		{
			for (int col = 0; col< getMapSize().width;col++)
			{
				for (int row = 0; row < getMapSize().height;row++)
				{
					int gid = layer->tileGIDAt(ccp(col,row));

					if (gid != 0)
					{
						m_objects[row][col] = MapObjectDataManager::getInstance()->getMapObjectByGID(gid);
						if (m_objects[row][col])
						{
							m_objects[row][col]->retain();
							m_objects[row][col]->x = col;
							m_objects[row][col]->y = row;
						}
						
					}
				}//end for
			}//end for
		}//end if
	}
}//end function 
	
	//CCTMXObjectGroup* objects = objectGroupNamed("objects");

	//CCArray* objArray = objects->getObjects();

	//if (objArray && objArray->count() > 0)
	//{
	//	CCObject* pObj = NULL;
	//	CCARRAY_FOREACH(objArray,pObj)
	//	{
	//		CCDictionary* mapObject = (CCDictionary*)pObj;
	//		int x = mapObject->valueForKey("x")->floatValue() / getTileSize().width;
	//		int y = mapObject->valueForKey("y")->floatValue() / getTileSize().height;

	//		m_objects[y][x] = mapObject;
	//	}
	//}

MapObject* GameMap::getMapObject(int x, int y)
{
	return m_objects[y][x];
}

void GameMap::clearMapObject(int x, int y)
{
	CC_SAFE_RELEASE(m_objects[y][x]);
	m_objects[y][x] = NULL;
}

//从tilemap坐标转换为cocos2dx坐标
CCPoint GameMap::positionForTileCoord(cocos2d::CCPoint tileCoord)
{
	int x=this->getTileSize().width;
	int y=this->getTileSize().height;
	CCPoint pos=ccp((tileCoord.x*this->getTileSize().width),
		((this->getMapSize().height-tileCoord.y-1)*this->getTileSize().height));
	return pos;
}

//从cocos2dx坐标转换为Tilemap坐标
cocos2d::CCPoint GameMap::tileCoordForPosition(cocos2d::CCPoint position)
{
	int x=position.x/this->getTileSize().width;
	int y=(((this->getMapSize().height-1)*this->getTileSize().height)-position.y)/this->getTileSize().height;
	return ccp(x,y);
}

