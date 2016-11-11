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

	
	this->addStartLine();
	this->addNormalLine(1);
	this->addNormalLine(2);
	this->addNormalLine(3);

	// 屏幕touch事件监听
	//创建监听事件对象
	auto listener = EventListenerTouchOneByOne::create();
	//定义监听事件的回调函数
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	//在事件分发器中注册
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
	int blackIndex = rand() % 4; // 每一行有4个
	for (int i = 0; i < 4; i++){
		b = BWBlock::createWithArgs(blackIndex == i ? Color3B::BLACK : Color3B::WHITE,
			Size(visibleSize.width / 4 - 1, visibleSize.height / 4 - 1), // 中间留个溪风
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
			if (b->getColor() == Color3B::BLACK){
				b->setColor(Color3B::GRAY);//点击的黑色块变成灰色
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

}