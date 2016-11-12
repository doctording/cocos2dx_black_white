#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "BWBlock.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

public:
	Size visibleSize;
	Point origin;
	
	void addStartLine();
	void addNormalLine(int lineindex);
	void addEndLine();

	int lineTotalCnt;

	Label* timerLabel; //显示时间
	int sTime; // 记录开始时间
	void updateLabel(float dt); // 时间的更新函数

	void startGameInit();
	bool timerRunning; // timer是否正在运行
	
	void startTimer(); // 开始 schedule
	void stopTimer();  // 结束 schedule

public:
	virtual void update(float dt);

	// 点击手势
	bool onTouchBegan(Touch *touch, Event *unused_event);
	// 拖动手势
	void onTouchMoved(Touch *touch, Event *unused_event);
	//  拖动结束
	void onTouchEnded(Touch *touch, Event *unused_event);
};

#endif // __GameScene_SCENE_H__
