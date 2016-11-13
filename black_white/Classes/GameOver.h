#ifndef _GAME_OVER_H_
#define _GAME_OVER_H_
#include "cocos2d.h"

#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CCSGUIReader.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;

//”Œœ∑Ω· ¯≥°æ∞
class GameOver : public Layer
{
public:
	static Scene * createScene();
	bool init();
	CREATE_FUNC(GameOver);
public:

	void againCallback(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
	void highScoreCallback(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
	void menuCallback(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);

	int score;
	TextField * txtScore;
	void onEnter();
};

#endif