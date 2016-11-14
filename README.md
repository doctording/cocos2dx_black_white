
cocos2dx 黑白块游戏
===
# 游戏截图
![](http://i.imgur.com/uag77ib.png)

![](http://i.imgur.com/txL6NS5.png)

开发环境
===
* win7 + vs2013 + cocos2dx3.0 + cocostudio

* android-ndk-r9d

* apache-ant-1.9.7

* adt-bundle-windows-x86_64-20130917

更多详细的cocos2dx3.0的使用可以参考我的打飞机完整程序

http://blog.csdn.net/qq_26437925/article/details/52059069


sqlite3
===

##cocos2dx + vs 如何使用sqlite3

http://blog.csdn.net/z104207/article/details/7518991

sqlite3的简单封装

http://www.eoeandroid.com/thread-193863-1-1.html?_dsign=3f6701a3


**注：**不一定全对，自己需要整理分析


## sqlite 执行sql语句的函数回调

在封装的Sqlite类中，自己定义一个接收回调的变量，对特定的方法，可以在使用过程中new出变量，使用后然后free调，这种方法不是特别好？。。


cocostudio 使用TextField
===
在cocostuio中用Label,然后在代码中setString()出错，可以换用TextField

使用 setText();可以设置其内容

```
auto ui = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("GameOver/GameOver_1.ExportJson");
ui->setPosition(Point(0, 0));
this->addChild(ui);


txtScore = (TextField*)Helper::seekWidgetByName(ui, "textField_score");
txtScore->setColor(Color3B::RED);
txtScore->setText("0");
```

## 本次游戏说明

本次游戏，主要是sqlite3的使用 和 各种cocos2dx定时器的使用

例如自定义定时方法

```
//每隔1.0f执行一次，省略参数则表示每帧都要执行
//scheduleOnce(schedule_selector(HelloWorld::update), 1.0f); 

//自定义 开启定时器，延时2s执行，执行3+1次，执行间隔1s
//this->schedule(schedule_selector(HelloWorld::update), 1, 3, 2);

//自定义定时器
schedule(schedule_selector(GameScene::update), 0.8);

schedule(schedule_selector(GameScene::updateLabel), 0.2);
```

取消定时器
```
unschedule(schedule_selector(GameScene::update));
unschedule(schedule_selector(GameScene::updateLabel));
```