#include "MapObjectDataManager.h"

using namespace tinyxml2;

void MapObjectDataManager::Config(tinyxml2::XMLDocument* doc)
{
	XMLElement*  root = doc->RootElement();

	XMLElement* lineElem = root->FirstChildElement("Line");
	while(lineElem != NULL)
	{

		 int gid= std::atoi(lineElem->FirstChildElement("GID")->GetText());

		 MapObjectData data;
		 data.Name = lineElem->FirstChildElement("name")->GetText();
		 data.Type = lineElem->FirstChildElement("type")->GetText();
		 data.Command = lineElem->FirstChildElement("command")->GetText();

		 m_MapData.insert(std::pair<int,MapObjectData>(gid,data));

		 lineElem = lineElem->NextSiblingElement("Line");
	}
}

MapObject* MapObjectDataManager::getMapObjectByGID(int gID)
{
	MapObjectDataMap::iterator it = m_MapData.find(gID);
	if (it == m_MapData.end())return NULL;

	MapObjectData data = it->second;

	MapObject* mapobj =NULL;
	if (strcmp(data.Type,"Item") == 0)
	{
		mapobj = ItemObject::create(data.Command);
	}
	else if(strcmp(data.Type,"Enemy") == 0)
	{
		char temp[64];
		strcpy(temp,data.Command);
		EnemyInfo info;
		info.HP = atoi(strtok(temp,","));
		info.Defence = atoi(strtok(NULL,","));
		info.Attack = atoi(strtok(NULL,","));

		mapobj = EnemyObject::create(info);
	}
	else if (strcmp(data.Type,"NPC") == 0)
	{
		mapobj = NPCObject::create(data.Command,NULL);
	}
	return mapobj;
}

