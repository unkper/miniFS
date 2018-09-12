#pragma once
#include "define.h"
class GuideManager
{
public:
	~GuideManager();
	Bitmap * contentMap;
	UFD allFiles[MAXFILESNUMBER];
	int nowFolderIndex = 0;   //��ǰ����
	int fileCount = 0;
	static GuideManager& GetInstance()
	{
		static GuideManager *instance = new GuideManager();
		return *instance;
	};

private:
	GuideManager() {};
	static GuideManager* instance;
};

