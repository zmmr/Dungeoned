#include "HelloWorldScene.h"
#include "GameMap.h"
#include <math.h>
#include "support/tinyxml2/tinyxml2.h"
#include "MapObjectDataManager.h"
#include "Hero.h"

using namespace cocos2d;
using namespace tinyxml2;

const int maprow = 11;
const int mapcolumn = 11;

CCScene* HelloWorld::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////
		tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
		doc->LoadFile("TileList.xml");

		MapObjectDataManager::getInstance()->Config(doc);

		m_tilemap = GameMap::create("魔塔序章.tmx");
		addChild(m_tilemap);

		

		

		CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage("p.png");

		for (int i = 0;i < Direction_Max;i++)
		{
			CCArray* animFrames = CCArray::create();
			CC_BREAK_IF(!animFrames);

			for (int j = 0;j<4;j++)
			{
				CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(pTexture,CCRectMake(j*32,i*31,32,31));
				animFrames->addObject(frame);
			}
			CCAnimation* animations = CCAnimation::createWithSpriteFrames(animFrames,0.125);

			CCAnimate* animate = CCAnimate::create(animations);

			action[i] = CCRepeat::create(animate,1);
			action[i]->retain();
		}

		m_hero = Hero::create("p.png");
		m_hero->m_curMap = m_tilemap;

		CC_BREAK_IF(!m_hero);

		m_heroDirection = Direction_Down;


		//CCTMXObjectGroup* objects = m_tilemap->objectGroupNamed("objects");

		//CCDictionary* heroPoint = objects->objectNamed("m_hero");

		m_hero->setAnchorPoint(ccp(0,0));

		//CCLog("x:%f y:%f",heroPoint->valueForKey("x")->floatValue(),heroPoint->valueForKey("y")->floatValue());

		//m_hero->setPosition(ccp(heroPoint->valueForKey("x")->floatValue(),heroPoint->valueForKey("y")->floatValue()));
		//m_hero->setPosition(ccp(160,32));
		m_tilemap->addChild(m_hero);
		setHeroDirection(Direction_Up);

		bRet = true;

	} while (0);

	return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* s)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

char* HelloWorld::G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP,0,gb2312,-1,NULL,0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr,0,len+1);
	MultiByteToWideChar(CP_ACP,0,gb2312,-1,wstr,len);
	len = WideCharToMultiByte(CP_UTF8,0,wstr,-1,NULL,0,NULL,NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_UTF8,0,wstr,-1,str,len,NULL,NULL);
	if ( wstr != NULL )delete[] wstr;
	return str;
}

void HelloWorld::draw()
{
	//glColor4f(1.0,1.0,1.0,1.0);
	//glLineWidth(0);

	//glLineWidth(1);
	//ccDrawColor4B(255,255,255,255);
	//ccPointSize(1);
}

void HelloWorld::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool HelloWorld::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void HelloWorld::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void HelloWorld::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (!CanTouch)return;
	CanTouch = false;
	int maxX = m_tilemap->getMapSize().width;
	int maxY = m_tilemap->getMapSize().height;


	const CCPoint mouse = m_tilemap->convertToNodeSpace(pTouch->getLocation());
	const CCPoint point = m_hero->getPosition();
	const int startx = point.x/32;
	const int starty = point.y/32;
	const int endx = mouse.x/32;
	const int endy = mouse.y/32;

	CCLog("startx:%d starty:%d",startx,starty);
	CCLog("endx:%d endy:%d",endx,endy);
	
	
	int currentx = startx;
	int currenty = starty;
	
	
	struct AStarNode
	{
		bool isOpen;
		bool isClose;
		bool isWalkable;
		int parentx;
		int parenty;
		int caozuo;
		int g;
		int f;
	};

	CCTMXLayer* wall= m_tilemap->layerNamed("wall");
	CCLog("picid:%d",wall->tileGIDAt(ccp(endx,endy)));
	AStarNode** map_node;
	map_node = new AStarNode*[maxX];
	for (int i = 0;i<maxX;i++)
	{
		map_node[i] = new AStarNode[maxY];
		for (int j = 0; j<maxY;j++)
		{
			map_node[i][j].caozuo = Direction_Max;
			map_node[i][j].isClose = false;
			map_node[i][j].isOpen = false;
			map_node[i][j].parentx = -1;
			map_node[i][j].parenty = -1;
			map_node[i][j].isWalkable = (wall->tileGIDAt(ccp(i,maxY-1-j)) == 0);
			map_node[i][j].g = 0;
			map_node[i][j].f = 0;
			
			CCLog("%d",map_node[i][j].isWalkable);
			
		}
		CCLog("huanhan");
	}
	
	while(currentx != endx || currenty != endy )
	{
		for (int nextstep = Direction_Down; nextstep < Direction_Max; nextstep++ )
		{
			int testx = currentx;
			int testy = currenty;
			switch (nextstep)
			{
			case Direction_Up:
				testy = currenty + 1 < maxY ?  currenty + 1 : currenty;
				break;
			case Direction_Left:
				testx = currentx - 1 > 0 ? currentx - 1 : 0;
				break;
			case Direction_Right:
				testx = currentx + 1 < maxX ? currentx + 1 : currentx;
				break;
			case Direction_Down:
				testy =  currenty - 1 > 0 ? currenty - 1 : 0;
				break;
			}
			if (testy == 0 )
			{
				CCLog("aaaa");
			}
			
			//如果节点是墙
			if ( !map_node[testx][testy].isWalkable || (currentx == testx && currenty == testy) )
			{
				continue;
			}

			int f = abs(endx - testx)+abs(endy - testy);

			if (map_node[testx][testy].isClose || map_node[testx][testy].isOpen)
			{
				if ( f< map_node[testx][testy].f)
				{
					map_node[testx][testy].f = f;
					map_node[testx][testy].parentx = currentx;
					map_node[testx][testy].parenty = currenty;
					map_node[testx][testy].caozuo = nextstep;
				}
			}
			else
			{
				map_node[testx][testy].f = f;
				map_node[testx][testy].parentx = currentx;
				map_node[testx][testy].parenty = currenty;
				map_node[testx][testy].caozuo = nextstep;
				map_node[testx][testy].isOpen = true;
			}
		}
		map_node[currentx][currenty].isClose =true;
		
		//获取开放节点中最小的节点
		int minx = -1,miny = -1;
		for (int i = 0;i<maxX;i++)
		{
			for (int j = 0;j<maxY; j++)
			{
				if ( minx <0 || miny<0)
				{
					if ( map_node[i][j].isOpen )
					{
						minx = i;
						miny = j;
					}
				}
				else
				{
					if ( map_node[i][j].f < map_node[minx][miny].f && map_node[i][j].isOpen)
					{
						minx = i;
						miny = j;
					}
				}
			}
		}
		CCLog(" minx:%d,miny:%d",minx,miny);
		if ( minx < 0 || miny < 0)
		{
			CCLog("no nodes");
			CanTouch = true;
			return;
		}	
		map_node[minx][miny].isOpen = false;
		currentx = minx;
		currenty = miny;
	}
	//建立路径
	while(currentx != startx || currenty !=starty )
	{
		AStarNode* nodes = &(map_node[currentx][currenty]); 
		pathqueue.push_back(nodes->caozuo);
		CCLog("direction:%d",nodes->caozuo);
		currentx = nodes->parentx;
		currenty = nodes->parenty;
		
	}
	funcN();
	
}

CCActionInterval* HelloWorld::createAction(unsigned int direction)
{
	switch(direction)
	{
	case Direction_Up:
		return CCMoveBy::create(0.5,ccp(0,32));
	case Direction_Left:
		return CCMoveBy::create(0.5,ccp(-32,0));
	case Direction_Right:
		return CCMoveBy::create(0.5,ccp(32,0));
	case Direction_Down:
		return CCMoveBy::create(0.5,ccp(0,-32));
	}
}

void HelloWorld::funcN()
{
	if (pathqueue.empty())
	{
		CanTouch = true;
		return;
	}

	m_hero->MoveDirction(pathqueue.back());
	CCFiniteTimeAction* fn = CCCallFunc::create(this,callfunc_selector(HelloWorld::funcN));
	//CCFiniteTimeAction* move = createAction(pathqueue.back());
	//CCFiniteTimeAction* sp = CCSpawn::create(move,action[pathqueue.back()],NULL);//CCSpawn::createWithTwoActions(move,action[1],N);
	//CCFiniteTimeAction* a = CCSequence::create(sp,fn,NULL);
	
	

	m_hero->runAction(fn);
	pathqueue.pop_back();
} 

bool HelloWorld::CheckDirection(unsigned int direction)
{
	int currentX = m_hero->getPositionX() / 32;
	int currentY = m_hero->getPositionY() / 31;
	
	return true;
}