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

	//��b��ӵ�blocks��  
	blocks->pushBack(b);

	return b;
}

bool BWBlock::initWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor)
{
	Sprite::init();

	lineIndex = 0;

	//���ô�С  
	setContentSize(size);
	//����ê��Ϊ���½�  
	setAnchorPoint(Point::ZERO);
	//��������  
	setTextureRect(Rect(0, 0, size.width, size.height));
	//������ɫ  
	setColor(color);

	//��������  
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

void BWBlock::moveDown() //�����Լ����block,�����ƶ�,�������0 �Զ��Ѿ�ɾ������
{
	this->lineIndex--;

	//�����½�һ��
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// �ܹ�4�� ������index , ��ֱ��֪����������
	runAction(Sequence::create(MoveTo::create(0.1f,Point(getPosition().x, lineIndex * visibleSize.height / 4)), 
		CallFunc::create([this](){

		if (this->lineIndex < 0)
			this->removeBlock();
	}), NULL));
}
