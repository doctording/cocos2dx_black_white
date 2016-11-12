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

	Label* timerLabel; //��ʾʱ��
	int sTime; // ��¼��ʼʱ��
	void updateLabel(float dt); // ʱ��ĸ��º���

	void startGameInit();
	bool timerRunning; // timer�Ƿ���������
	
	void startTimer(); // ��ʼ schedule
	void stopTimer();  // ���� schedule

public:
	virtual void update(float dt);

	// �������
	bool onTouchBegan(Touch *touch, Event *unused_event);
	// �϶�����
	void onTouchMoved(Touch *touch, Event *unused_event);
	//  �϶�����
	void onTouchEnded(Touch *touch, Event *unused_event);
};

#endif // __GameScene_SCENE_H__
