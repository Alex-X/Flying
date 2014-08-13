#ifndef _PlistLoader_H_
#define _PlistLoader_H_

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class PlistLoader
{
public:
	static PlistLoader* getInstance();

	static void destroyInstance();
	
	void loadPlist(string plist,string png);
	
	SpriteFrame* getSpriteFrameByName(string name);

protected:

	PlistLoader();

	virtual bool init();

	static PlistLoader* sharedPlistLoader;

	Map<string,SpriteFrame*> _spriteFrames;
};

#endif