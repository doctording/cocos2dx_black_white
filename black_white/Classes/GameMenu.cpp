#include "GameMenu.h"
#include "Game.h"
#include "HighScore.h"

#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CCSGUIReader.h"

using namespace cocos2d::ui;
using namespace cocostudio;

//����һ��CCrenderTexture 
//�൱��һ���������е���Ϸ�Ľ�ͼ��Ϊ�����ͣ�Ի���ı��� 
//�����Ϳ��������ǶԻ�������Ϸ����֮�ϣ�һ����Ϸ���ж���������д�ġ�
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
	//�õ����ڵĴ�С
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	//ԭ������
	Point origin = Director::sharedDirector()->getVisibleOrigin();

	auto ui = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("GameMenu_2/GameMenu_1.ExportJson");
	ui->setPosition(Point(0, 0));
	this->addChild(ui);

	// ��Ϸ�е�
	Button* btnMiddle = (Button*)Helper::seekWidgetByName(ui, "btnMiddle");
	btnMiddle->addTouchEventListener(this, toucheventselector(Gamemenu::midCallback));
	
	// ��Ϸ��
	Button* btnHard = (Button*)Helper::seekWidgetByName(ui, "btnHard");
	btnHard->addTouchEventListener(this, toucheventselector(Gamemenu::midCallback));

	// ��߷�
	Button* btnHighScore = (Button*)Helper::seekWidgetByName(ui, "btnHighScore");
	btnHighScore->addTouchEventListener(this, toucheventselector(Gamemenu::highScoreCallback));
	
	// ����
	Button* btnHelp = (Button*)Helper::seekWidgetByName(ui, "btnHelp");
	btnHelp->addTouchEventListener(this, toucheventselector(Gamemenu::helpCallback));

    return true;
}

void  Gamemenu::midCallback(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN: // ����ʱ�俪ʼʱ���������µ�ʱ��
		break;
	case TouchEventType::TOUCH_EVENT_MOVED: // ����֮�󣬽����ƶ�����ʱ����
		break;
	case TouchEventType::TOUCH_EVENT_ENDED: // ����֮��Ȼ���ɿ�����
	{
		Director::getInstance()->replaceScene(GameScene::createScene());
	}
	break;
	case TouchEventType::TOUCH_EVENT_CANCELED: // �жϴ���
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
	case TouchEventType::TOUCH_EVENT_BEGAN: // ����ʱ�俪ʼʱ���������µ�ʱ��
		break;
	case TouchEventType::TOUCH_EVENT_MOVED: // ����֮�󣬽����ƶ�����ʱ����
		break;
	case TouchEventType::TOUCH_EVENT_ENDED: // ����֮��Ȼ���ɿ�����
	{
		Director::getInstance()->replaceScene(HighScore::createScene());
	}
	break;
	case TouchEventType::TOUCH_EVENT_CANCELED: // �жϴ���
		break;
	default:
		break;
	}
}