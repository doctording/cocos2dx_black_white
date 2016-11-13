#include "Game.h"
#include "DataUtil.h"
#include "GameOver.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	// 屏幕touch事件监听
	//创建监听事件对象
	auto listener = EventListenerTouchOneByOne::create();
	//定义监听事件的回调函数
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	//在事件分发器中注册
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	timerLabel = Label::create();
	timerLabel->setColor(Color3B::BLUE);
	timerLabel->setSystemFontSize(48);
	timerLabel->setPosition(visibleSize.width / 2, visibleSize.height - 100);
	timerLabel->setString("0.000");
	this->addChild(timerLabel,1);

	startGameInit(); // 各种数据，定时器的初始化

	return true;
}

void GameScene::startGameInit()
{
	lineTotalCnt = 0;
	addStartLine();
	addNormalLine(1);
	addNormalLine(2);
	addNormalLine(3);
	timerRunning = false;
	sTime = clock();
}

void GameScene::startTimer()
{
	if (!timerRunning)
	{
		//更新定时器，每帧调用1次。每个节点只能有1个被调度的update函数
		//scheduleUpdate(void);

		//每隔1.0f执行一次，省略参数则表示每帧都要执行
		//scheduleOnce(schedule_selector(HelloWorld::update), 1.0f); 

		//自定义 开启定时器，延时2s执行，执行3+1次，执行间隔1s
		//this->schedule(schedule_selector(HelloWorld::update), 1, 3, 2);

		//自定义定时器
		schedule(schedule_selector(GameScene::update), 0.8);

		schedule(schedule_selector(GameScene::updateLabel), 0.2);

		sTime = clock();

		timerRunning = true;
	}
}

void GameScene::stopTimer()
{
	if (timerRunning)
	{
		unschedule(schedule_selector(GameScene::update));
		unschedule(schedule_selector(GameScene::updateLabel));
		timerRunning = false;
		
		// 这里做跳转，存储数据等操作
		// TODO
		//创建数据库，如果数据库存在的话，就会打开数据库
		if (DataUtil::pScore != NULL)
			free(DataUtil::pScore);
		DataUtil::initDB("ok.db");
		//数据库中没有表格的话就先创建一个表格先
		//string sqlsss = "create table user(id integer,score integer)";
		//DataUtil::createTable(sqlsss, "user");

		//char sql[256] = { 0 };
		//sprintf(sql, "update user set score=%d where id=1", lineTotalCnt);

		//char sql[256] = { 0 };
		//sprintf(sql, "insert into user values(1,%d)", lineTotalCnt);
		//string sqlss(sql);
		//DataUtil::insertData(sqlss);
		string sqls = "select max(id) from user";
		DataUtil::getDataInfo(sqls, NULL);
		DataUtil::closeDB();

		int cnt = atoi(DataUtil::pScore);
		if (DataUtil::pScore != NULL)
			free(DataUtil::pScore);

		DataUtil::initDB("ok.db");
		//int cnt = DataUtil::getDataCount("select count(*) from user");
		char sql[256] = { 0 };
		sprintf(sql, "insert into user values(%d,%d)", cnt+1,lineTotalCnt);
		string sqlss(sql);
		DataUtil::insertData(sqlss);

		DataUtil::closeDB();

		// 场景跳转
		auto scene = GameOver::createScene();
		GameOver *overLayer = (GameOver*)scene->getChildByTag(404); // tag
		overLayer->score = lineTotalCnt;
		Director::getInstance()->replaceScene(scene);

	}
}

void GameScene::updateLabel(float dt)
{
	long offset = clock() - sTime;
	timerLabel->setString(StringUtils::format("%.2lf", ((double)offset) / 1000)); //单位变成秒
}


void GameScene::addStartLine()
{
	auto b = BWBlock::createWithArgs(Color3B::YELLOW, Size(visibleSize.width,
		visibleSize.height / 4), "", 20, Color4B::YELLOW);

	b->setLineIndex(1);
	this->addChild(b);
}

void GameScene::addEndLine()
{
	auto b = BWBlock::createWithArgs(Color3B::GREEN, visibleSize, "Game Over", 32, Color4B::BLACK);
	b->setLineIndex(4);
	this->addChild(b);
}

void GameScene::addNormalLine(int lineindex)
{
	BWBlock* b;
	int blackIndex = rand() % 4; // 每一行有4个
	for (int i = 0; i < 4; i++){
		b = BWBlock::createWithArgs(blackIndex == i ? Color3B::BLACK : Color3B::WHITE,
			Size(visibleSize.width / 4 - 1, visibleSize.height / 4 - 1),
			"", 20, Color4B::YELLOW);

		b->setPosition(i*visibleSize.width / 4, lineindex*visibleSize.height / 4);
		b->setLineIndex(lineindex);
		this->addChild(b);
	}
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	//获取触屏位置（坐标）
	Point pos = touch->getLocation();
	// CCLOG("x:%lf,y:%lf", pos.x, pos.y);
	
	//遍历blocks
	auto bs = BWBlock::getBlocks();
	BWBlock* b;
	for (auto it = bs->begin(); it != bs->end(); it++)
	{
		b = *it;
		if (b->getLineIndex() == 1 && b->getBoundingBox().containsPoint(pos))
		{
			if (b->getColor() == Color3B::BLACK)
			{
				b->setColor(Color3B::GRAY);//点击的黑色块变成灰色
				
				//点击第一个黑块开始计时
				if (!timerRunning)
					this->startTimer();
			}
			break; //退出循环
		}
	}
	return false;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	//获取当前拖动手势的坐标与位置
	//Point pos = touch->getLocation();
	//CCLOG("TouchMoved");
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	
}

void GameScene::update(float delta)
{
	addNormalLine(4);
	lineTotalCnt++;

	//遍历blocks
	auto bs = BWBlock::getBlocks();
	BWBlock* b;
	for (auto it = bs->begin(); it != bs->end(); it++)
	{
		b = *it;
		b->moveDown();

		if (b->getLineIndex() == -1)
		{
			log("(line: %d %d %d)", b->getColor().r, b->getColor().g, b->getColor().b);
			if ((b->getColor().r + b->getColor().g + b->getColor().b) == 0) // r g b都等于0是黑色
			{
				//unschedule(schedule_selector(GameScene::update));
				//break;
				stopTimer();
			}
		}
	}

	CCLOG("lineTotalCnt:%d,vSize:%d", lineTotalCnt,(int)bs->size());
}