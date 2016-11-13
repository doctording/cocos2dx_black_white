#include "GameMenu.h"
#include "HighScore.h"

#include "DataUtil.h"

#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CCSGUIReader.h"
#include <cstdio>
#include <string>

using namespace cocos2d::ui;
using namespace cocostudio;

//����һ��CCrenderTexture 
//�൱��һ���������е���Ϸ�Ľ�ͼ��Ϊ�����ͣ�Ի���ı��� 
//�����Ϳ��������ǶԻ�������Ϸ����֮�ϣ�һ����Ϸ���ж���������д�ġ�
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
	//�õ����ڵĴ�С
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	//ԭ������
	Point origin = Director::sharedDirector()->getVisibleOrigin();

	auto ui = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("HighScore_3/HighScore_1.ExportJson");
	ui->setPosition(Point(0, 0));
	this->addChild(ui);

	// ���ݿ��ȡ
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
	case TouchEventType::TOUCH_EVENT_BEGAN: // ����ʱ�俪ʼʱ���������µ�ʱ��
		break;
	case TouchEventType::TOUCH_EVENT_MOVED: // ����֮�󣬽����ƶ�����ʱ����
		break;
	case TouchEventType::TOUCH_EVENT_ENDED: // ����֮��Ȼ���ɿ�����
	{
		Director::getInstance()->replaceScene(Gamemenu::createScene());
	}
	break;
	case TouchEventType::TOUCH_EVENT_CANCELED: // �жϴ���
		break;
	default:
		break;
	}
}