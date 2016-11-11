#ifndef __BWBLOCK_H__
#define __BWBLOCK_H__

#include "cocos2d.h"

#include <string>

USING_NS_CC;

class BWBlock : public Sprite
{
private:
	int lineIndex;
	static Vector<BWBlock*> *blocks;

public:

	static Vector<BWBlock*> * getBlocks();

	static BWBlock* createWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor);

	virtual bool initWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor);

	void removeBlock();

	int getLineIndex();
	void setLineIndex(int _lineIndex);

	void moveDown();
};

#endif //
