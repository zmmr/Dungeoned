#ifndef _MAPOBJECTDATAMANAGER_H_
#define _MAPOBJECTDATAMANAGER_H_

#include "support/tinyxml2/tinyxml2.h"
#include "MapObject.h"

struct MapObjectData
{
	const char* Type;
	const char* Name;
	const char* Command;
};
typedef std::map<int,MapObjectData> MapObjectDataMap;

class MapObjectDataManager
{
public:
	static MapObjectDataManager* getInstance()
	{
		static MapObjectDataManager s_instance;
		return &s_instance;
	}

	void Config(tinyxml2::XMLDocument* doc);

	MapObject* getMapObjectByGID(int gID);
private:
	MapObjectDataManager(){}
	MapObjectDataMap m_MapData;
};
#endif