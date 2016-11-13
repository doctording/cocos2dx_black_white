#include "GameMenu.h"
#include "HighScore.h"

#include "DataUtil.h"

#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CCSGUIReader.h"
#include <cstdio>
#include <string>

using namespace cocos2d::ui;
using namespace cocostudio;

//传入一个CCrenderTexture 
//相当于一个正在运行的游戏的截图作为这个暂停对话框的背景 
//这样就看起来像是对话框在游戏界面之上，一般游戏当中都是这样子写的。
Scene* HighScore::createScene()
{
    auto *scene = Scene::create();
	auto *layer = HighScore::create();

	scene->addChild(layer);

    return scene;
}

bool HighScore::init()
{

    if ( !CCLayer::init() )
    {
        return false;
    }
	//得到窗口的大小
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	//原点坐标
	Point origin = Director::sharedDirector()->getVisibleOrigin();

	auto ui = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("HighScore_3/HighScore_1.ExportJson");
	ui->setPosition(Point(0, 0));
	this->addChild(ui);

	// 数据库读取
	// TODO
	DataUtil::initDB("ok.db");
	string sqls = "select max(score) from user";
	DataUtil::getDataInfo(sqls, NULL);
	DataUtil::closeDB();
	std::string str(DataUtil::pScore);

	TextField* label = (TextField*)Helper::seekWidgetByName(ui, "textField_score");
	label->setColor(Color3B::RED);
	
	//auto score_str = __String::createWithFormat("%d", 10);
	//label->setText(score_str->getCString());
	label->setText(str.c_str());

	free(DataUtil::pScore);

	// back
	Button* btnBack = (Button*)Helper::seekWidgetByName(ui, "btn_back");
	btnBack->addTouchEventListener(this, toucheventselector(HighScore::callbackMenu));

    return true;
}

void  HighScore::callbackMenu(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
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