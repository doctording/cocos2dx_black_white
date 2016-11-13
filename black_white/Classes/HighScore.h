#ifndef __HIGHSCORE__H__
#define __HIGHSCORE__H__

#include "cocos2d.h"

#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CCSGUIReader.h"

USING_NS_CC;

class HighScore: public cocos2d::Layer
{
public:
    
    virtual bool init();  
    static Scene* createScene();
    CREATE_FUNC(HighScore);
		
	void callbackMenu(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
};

#endif // 