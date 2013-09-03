#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include <vector>
#include "GameConstants.h"
#include "GameMap.h"
#include "Hero.h"

class HelloWorld : public cocos2d::CCLayer
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
	void menuCloseCallback(cocos2d::CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	char* G2U(const char* gb2312);

	virtual void draw();

	GameMap* m_tilemap;

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void funcN();
private:
	void onEnter();
	void setHeroDirection(uint32 direction)
	{
		m_heroDirection = direction;
		m_hero->setTextureRect(cocos2d::CCRectMake(0,m_heroDirection*31,32,31));
	}
	void playerStop()
	{
		m_hero->stopAction(action[m_heroDirection]);
	}
	void playerMove( uint32 direction = Direction_Max )
	{
		playerStop();
		if (direction != Direction_Max)
		{
			setHeroDirection(direction);
		}

		m_hero->runAction(action[m_heroDirection]);
	}

	
	cocos2d::CCActionInterval* action[Direction_Max];

	Hero* m_hero;
	uint32 m_heroDirection;
	uint32 m_heroState;

	std::vector<uint32> pathqueue;

	bool CanTouch;

	cocos2d::CCActionInterval* createAction(unsigned int direction);

	bool CheckDirection(unsigned int direction);
};

#endif  // __HELLOWORLD_SCENE_H__