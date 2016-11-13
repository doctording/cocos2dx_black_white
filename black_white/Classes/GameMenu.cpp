#include "GameMenu.h"
#include "Game.h"
#include "HighScore.h"

#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CCSGUIReader.h"

using namespace cocos2d::ui;
using namespace cocostudio;

//传入一个CCrenderTexture 
//相当于一个正在运行的游戏的截图作为这个暂停对话框的背景 
//这样就看起来像是对话框在游戏界面之上，一般游戏当中都是这样子写的。
Scene* Gamemenu::createScene()
{
    auto *scene = Scene::create();
    auto *layer = Gamemenu::create();

	layer->setTag(100);

	scene->addChild(layer);

    return scene;
}

bool Gamemenu::init()
{

    if ( !CCLayer::init() )
    {
        return false;
    }
	//得到窗口的大小
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	//原点坐标
	Point origin = Director::sharedDirector()->getVisibleOrigin();

	auto ui = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("GameMenu_2/GameMenu_1.ExportJson");
	ui->setPosition(Point(0, 0));
	this->addChild(ui);

	// 游戏中等
	Button* btnMiddle = (Button*)Helper::seekWidgetByName(ui, "btnMiddle");
	btnMiddle->addTouchEventListener(this, toucheventselector(Gamemenu::midCallback));
	
	// 游戏难
	Button* btnHard = (Button*)Helper::seekWidgetByName(ui, "btnHard");
	btnHard->addTouchEventListener(this, toucheventselector(Gamemenu::midCallback));

	// 最高分
	Button* btnHighScore = (Button*)Helper::seekWidgetByName(ui, "btnHighScore");
	btnHighScore->addTouchEventListener(this, toucheventselector(Gamemenu::highScoreCallback));
	
	// 帮助
	Button* btnHelp = (Button*)Helper::seekWidgetByName(ui, "btnHelp");
	btnHelp->addTouchEventListener(this, toucheventselector(Gamemenu::helpCallback));

    return true;
}

void  Gamemenu::midCallback(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN: // 单机时间开始时触发（按下的时候）
		break;
	case TouchEventType::TOUCH_EVENT_MOVED: // 按下之后，进行移动操作时触发
		break;
	case TouchEventType::TOUCH_EVENT_ENDED: // 按下之后，然后松开触发
	{
		Director::getInstance()->replaceScene(GameScene::createScene());
	}
	break;
	case TouchEventType::TOUCH_EVENT_CANCELED: // 中断触发
		break;
	default:
		break;
	}
}

void  Gamemenu::helpCallback(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
{
}

void Gamemenu::highScoreCallback(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN: // 单机时间开始时触发（按下的时候）
		break;
	case TouchEventType::TOUCH_EVENT_MOVED: // 按下之后，进行移动操作时触发
		break;
	case TouchEventType::TOUCH_EVENT_ENDED: // 按下之后，然后松开触发
	{
		Director::getInstance()->replaceScene(HighScore::createScene());
	}
	break;
	case TouchEventType::TOUCH_EVENT_CANCELED: // 中断触发
		break;
	default:
		break;
	}
}