#pragma once
#include "define.h"
class GuideManager
{
public:
	~GuideManager();
	Bitmap* contentMap;
	list<UFD> (*files);
	int fileCount = 0;
	FILE* Header;
	static GuideManager& GetInstance()
	{
		static GuideManager *instance = new GuideManager();
		return *instance;
	};

private:
	GuideManager() {};
	static GuideManager* instance;
};

