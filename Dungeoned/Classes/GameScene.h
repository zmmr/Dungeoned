#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameMap.h"

//GameScene�̳�CCScene
class GameScene : public cocos2d::CCScene
{
public:
	GameScene(void);
	~GameScene(void);
	//��ʼ������
	virtual bool init();
	//Scene�ľ�̬����������2.0�Ժ������仯��
	CREATE_FUNC(GameScene);
	
	void onEnter();
	void onExit();
protected:
	//���ò�
	void resetGameLayer();

	//ɾ�����ֲ�
	void removeFadeLayer();
private:

};

class GameLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(GameLayer);

	virtual bool init();
private:
	//�л���ͼ
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