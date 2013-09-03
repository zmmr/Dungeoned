#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameMap.h"

//GameScene继承CCScene
class GameScene : public cocos2d::CCScene
{
public:
	GameScene(void);
	~GameScene(void);
	//初始化函数
	virtual bool init();
	//Scene的静态创建方法（2.0以后有所变化）
	CREATE_FUNC(GameScene);
	
	void onEnter();
	void onExit();
protected:
	//重置层
	void resetGameLayer();

	//删除遮罩层
	void removeFadeLayer();
private:

};

class GameLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(GameLayer);

	virtual bool init();
private:
	//切换地图
	void switchMap(GameMap* map);

	GameMap* m_curMap;
};

class ControlLayer:public cocos2d::CCLayer
{
public:
	CREATE_FUNC(ControlLayer);

	virtual bool init();

	void menuCallBackMove(CCObject* pSender);

	void menuCloseCallBack(CCObject* pSender);
};

#endif