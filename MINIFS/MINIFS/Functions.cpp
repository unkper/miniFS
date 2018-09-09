#include"define.h"
#include "GuideManager.h"

void Encode(char *ins)
{
	int i = 0;
	while (ins[i] != 0)
	{
		if (ins[i] >= 'A'&&ins[i] <= 'Z')
		{
			ins[i] += 32;
		}
		i++;
	}
}

void m_CreateFile(char * Filename, char * FileExtname)
{
	time_t t = time(0);
	char tmp[15];
	memset(tmp, 0, sizeof(tmp));
	strftime(tmp, sizeof(tmp), "%Y/%m/%d", localtime(&t));
	GuideManager& manager = GuideManager::GetInstance();
	UFD newFile;
	newFile.length = 0;
	strcpy(newFile.create_time, tmp);
	strcpy(newFile.edit_time, tmp);
	strcpy(newFile.name, Filename);
	strcpy(newFile.extension, FileExtname);
	newFile.next = NULL;
	//这个-1在unsigned short为正值，
	newFile.keyvalue = -1;
	if (manager.fileCount = 0)
	{
		manager.fileCount++;
		manager.files->push_front(newFile);
		return;
	}
	list<UFD>::iterator itor = manager.files->begin();
	bool ifRepeat = false;
	while (itor != manager.files->end())
	{
		UFD itorThing = (*itor);
		if (itorThing.name == newFile.name)
		{
			ifRepeat = true;
			break;
		}
		itor++;
	}
	if (!ifRepeat)
	{
		manager.fileCount++;
		manager.files->push_front(newFile);
	}	
	else
	{
		cout << "存在同名文件，创建失败";
	}
	return;
}

void m_DeleteFile(char * Filename)
{

}

void CloseSpace()
{
	GuideManager manager = GuideManager::GetInstance();
	return WriteGuideBlock(manager.Header);
}

