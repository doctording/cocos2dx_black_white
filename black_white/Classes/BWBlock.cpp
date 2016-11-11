#include "BWBlock.h"


Vector<BWBlock*> * BWBlock::blocks = new Vector<BWBlock*>();

Vector<BWBlock*> * BWBlock::getBlocks()
{
	return BWBlock::blocks;
}

BWBlock* BWBlock::createWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor)
{
	auto b = new BWBlock();
	b->initWithArgs(color, size, label, fontSize, textColor);
	b->autorelease();

	//将b添加到blocks中  
	blocks->pushBack(b);

	return b;
}

bool BWBlock::initWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor)
{
	Sprite::init();

	lineIndex = 0;

	//设置大小  
	setContentSize(size);
	//设置锚点为左下角  
	setAnchorPoint(Point::ZERO);
	//设置区域  
	setTextureRect(Rect(0, 0, size.width, size.height));
	//设置颜色  
	setColor(color);

	//设置文字  
	auto myLabel = Label::create();
	myLabel->setString(label);
	myLabel->setSystemFontSize(fontSize);
	myLabel->setTextColor(textColor);
	addChild(myLabel);
	myLabel->setPosition(size.width / 2, size.height / 2);

	return true;
}

void BWBlock::removeBlock()
{
	removeFromParent();
	blocks->eraseObject(this);
}


int BWBlock::getLineIndex()
{
	return lineIndex;
}

void BWBlock::setLineIndex(int _lineIndex)
{
	lineIndex = _lineIndex;
}

void BWBlock::moveDown() //控制自己这个block,往下移动,如果等于0 自动已经删除掉了
{
	this->lineIndex--;

	//整个下降一行
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// 总共4行 ，有了index , 就直接知道纵坐标了
	runAction(Sequence::create(MoveTo::create(0.1f,Point(getPosition().x, lineIndex * visibleSize.height / 4)), 
		CallFunc::create([this](){

		if (this->lineIndex < 0)
			this->removeBlock();
	}), NULL));
}
