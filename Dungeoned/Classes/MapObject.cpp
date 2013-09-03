#include "MapObject.h"
#include "Hero.h"

using namespace cocos2d;

ItemObject* ItemObject::create(const char* command)
{
	ItemObject* item = new ItemObject;
	if (item)
	{
		item->m_command = command;
		item->autorelease();
	}
	return item;
}

bool ItemObject::active(Hero* hero)
{
	char commands[128] = {0};
	strcpy(commands,m_command);
	char *command; 

	HeroData data = hero->m_data;
	command = strtok(command,";");
	bool isSuccess = true;
	while (command != NULL)
	{
		if (!hero->excute(command))
		{
			isSuccess = false;
		}
		command = strtok(NULL,"");
	}
	if (isSuccess)
	{
		hero->m_curMap->clearMapObject(x,y);
		return true;
	}
	//如果失败，恢复数据
	else
	{
		hero->m_data = data;
	}
	return false;
}

EnemyObject* EnemyObject::create(EnemyInfo info)
{
	EnemyObject* enemy = new EnemyObject;
	if (enemy)
	{
		enemy->m_info = info;
		enemy->autorelease();
	}
	return enemy;
}

bool EnemyObject::active(Hero* hero)
{
	return false;
}

NPCObject* NPCObject::create(const char* luaPath, const char* command)
{
	NPCObject* npc = new NPCObject;
	if (npc)
	{
		npc->m_command = command;
		npc->m_luaPath = luaPath;
		npc->autorelease();
	}
	return npc;
}

bool NPCObject::active(Hero* hero)
{
	std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(m_luaPath);
	CCScriptEngineManager::sharedManager()->getScriptEngine()->executeScriptFile(path.c_str());
	return false;
}


