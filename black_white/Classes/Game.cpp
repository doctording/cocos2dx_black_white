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

	// ��Ļtouch�¼�����
	//���������¼�����
	auto listener = EventListenerTouchOneByOne::create();
	//��������¼��Ļص�����
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	//���¼��ַ�����ע��
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	timerLabel = Label::create();
	timerLabel->setColor(Color3B::BLUE);
	timerLabel->setSystemFontSize(48);
	timerLabel->setPosition(visibleSize.width / 2, visibleSize.height - 100);
	timerLabel->setString("0.000");
	this->addChild(timerLabel,1);

	startGameInit(); // �������ݣ���ʱ���ĳ�ʼ��

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
		//���¶�ʱ����ÿ֡����1�Ρ�ÿ���ڵ�ֻ����1�������ȵ�update����
		//scheduleUpdate(void);

		//ÿ��1.0fִ��һ�Σ�ʡ�Բ������ʾÿ֡��Ҫִ��
		//scheduleOnce(schedule_selector(HelloWorld::update), 1.0f); 

		//�Զ��� ������ʱ������ʱ2sִ�У�ִ��3+1�Σ�ִ�м��1s
		//this->schedule(schedule_selector(HelloWorld::update), 1, 3, 2);

		//�Զ��嶨ʱ��
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
		
		// ��������ת���洢���ݵȲ���
		// TODO
		//�������ݿ⣬������ݿ���ڵĻ����ͻ�����ݿ�
		if (DataUtil::pScore != NULL)
			free(DataUtil::pScore);
		DataUtil::initDB("ok.db");
		//���ݿ���û�б��Ļ����ȴ���һ�������
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

		// ������ת
		auto scene = GameOver::createScene();
		GameOver *overLayer = (GameOver*)scene->getChildByTag(404); // tag
		overLayer->score = lineTotalCnt;
		Director::getInstance()->replaceScene(scene);

	}
}

void GameScene::updateLabel(float dt)
{
	long offset = clock() - sTime;
	timerLabel->setString(StringUtils::format("%.2lf", ((double)offset) / 1000)); //��λ�����
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
	int blackIndex = rand() % 4; // ÿһ����4��
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
	//��ȡ����λ�ã����꣩
	Point pos = touch->getLocation();
	// CCLOG("x:%lf,y:%lf", pos.x, pos.y);
	
	//����blocks
	auto bs = BWBlock::getBlocks();
	BWBlock* b;
	for (auto it = bs->begin(); it != bs->end(); it++)
	{
		b = *it;
		if (b->getLineIndex() == 1 && b->getBoundingBox().containsPoint(pos))
		{
			if (b->getColor() == Color3B::BLACK)
			{
				b->setColor(Color3B::GRAY);//����ĺ�ɫ���ɻ�ɫ
				
				//�����һ���ڿ鿪ʼ��ʱ
				if (!timerRunning)
					this->startTimer();
			}
			break; //�˳�ѭ��
		}
	}
	return false;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	//��ȡ��ǰ�϶����Ƶ�������λ��
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

	//����blocks
	auto bs = BWBlock::getBlocks();
	BWBlock* b;
	for (auto it = bs->begin(); it != bs->end(); it++)
	{
		b = *it;
		b->moveDown();

		if (b->getLineIndex() == -1)
		{
			log("(line: %d %d %d)", b->getColor().r, b->getColor().g, b->getColor().b);
			if ((b->getColor().r + b->getColor().g + b->getColor().b) == 0) // r g b������0�Ǻ�ɫ
			{
				//unschedule(schedule_selector(GameScene::update));
				//break;
				stopTimer();
			}
		}
	}

	CCLOG("lineTotalCnt:%d,vSize:%d", lineTotalCnt,(int)bs->size());
}