#ifndef __Gamemenu__H__
#define __Gamemenu__H__

#include "cocos2d.h"

#include "ui\CocosGUI.h"
#include "editor-support\cocostudio\CCSGUIReader.h"

USING_NS_CC;

class Gamemenu : public cocos2d::Layer
{
public:
    
    virtual bool init();  
    static Scene* createScene();
    CREATE_FUNC(Gamemenu);
		
	void midCallback(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
	void helpCallback(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
	void highScoreCallback(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
};

#endif // __Gamemenu_H__