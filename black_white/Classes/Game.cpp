#include "Game.h"

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

	lineTotalCnt = 0;
	
	this->addStartLine();
	this->addNormalLine(1);
	this->addNormalLine(2);
	this->addNormalLine(3);

	// ��Ļtouch�¼�����
	//���������¼�����
	auto listener = EventListenerTouchOneByOne::create();
	//��������¼��Ļص�����
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	//���¼��ַ�����ע��
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
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
				
				//�Զ��嶨ʱ��
				schedule(schedule_selector(GameScene::update), 0.8);
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
				break;
			}
		}
	}

	CCLOG("lineTotalCnt:%d,vSize:%d", lineTotalCnt,(int)bs->size());
}