#include "GameOver.h"
#include "GameMenu.h"

Scene * GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();

	layer->setTag(404);

	scene->addChild(layer);

	return scene;
}

bool GameOver::init()
{
	if (!Layer::init())
		return false;

	//得到窗口的大小
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	//原点坐标
	Point origin = Director::sharedDirector()->getVisibleOrigin();

	auto ui = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("GameOver/GameOver_1.ExportJson");
	ui->setPosition(Point(0, 0));
	this->addChild(ui);


	txtScore = (TextField*)Helper::seekWidgetByName(ui, "textField_score");
	txtScore->setColor(Color3B::RED);
	txtScore->setText("0");

	// back
	Button* btnBack = (Button*)Helper::seekWidgetByName(ui, "btn_back");
	btnBack->addTouchEventListener(this, toucheventselector(GameOver::menuCallback));

	// 
	Button* btnAgin = (Button*)Helper::seekWidgetByName(ui, "btn_again");
	btnAgin->addTouchEventListener(this, toucheventselector(GameOver::againCallback));

	// back
	Button* btnHighScore = (Button*)Helper::seekWidgetByName(ui, "btn_HighScore");
	btnHighScore->addTouchEventListener(this, toucheventselector(GameOver::highScoreCallback));

	return true;
}

void GameOver::onEnter()
{
	Layer::onEnter(); // 这个不能够漏掉
	//CCLOG("get score: %d", score_int);
	auto score_str = __String::createWithFormat("%d", score);
	txtScore->setText(score_str->getCString());
}

void GameOver::menuCallback(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN: // 单机时间开始时触发（按下的时候）
		break;
	case TouchEventType::TOUCH_EVENT_MOVED: // 按下之后，进行移动操作时触发
		break;
	case TouchEventType::TOUCH_EVENT_ENDED: // 按下之后，然后松开触发
	{
		Director::getInstance()->replaceScene(Gamemenu::createScene());
	}
	break;
	case TouchEventType::TOUCH_EVENT_CANCELED: // 中断触发
		break;
	default:
		break;
	}
}


void GameOver::highScoreCallback(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
{
}



void GameOver::againCallback(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
{
}