#include "PlistLoader.h"

PlistLoader* PlistLoader::sharedPlistLoader = nullptr;

PlistLoader* PlistLoader::getInstance()
{
	if(sharedPlistLoader == nullptr)
	{
		sharedPlistLoader = new PlistLoader();
		if(!sharedPlistLoader->init())
		{
			delete sharedPlistLoader;
			sharedPlistLoader = nullptr;
		}
	}
	return sharedPlistLoader;
}

void PlistLoader::destroyInstance()
{
	CC_SAFE_DELETE(sharedPlistLoader);
}

PlistLoader::PlistLoader(){}

bool PlistLoader::init()
{
	return true;
}

void PlistLoader::loadPlist(string plist,string png)
{
	string pngNames[7]={"Hero","fly","fly2","left1","left2","right1","right2"}; 

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(plist,png);
	
	SpriteFrame* frame = NULL;
	for(int i=0;i <7;i++)
	{
		string pngName = pngNames[i];
		frame = frameCache->getSpriteFrameByName(pngName+".png");
		this->_spriteFrames.insert(pngName,frame);
	}
	
}

SpriteFrame* PlistLoader::getSpriteFrameByName(string name)
{
	return this->_spriteFrames.at(name);
}