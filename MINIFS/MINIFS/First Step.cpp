#include"define.h"
#include"GuideManager.h"

FILE *CreateSpace(char *SName)
{
	bool check;
	FILE *fp;
	if ((fp = fopen(SName, "r+")) == NULL)
	{
		check=true;
	}
	else
	{
		printf("存在同名文件，操作无法进行！\n");
		fclose(fp);
		return NULL;
	}

	if ((fp = fopen(SName, "w+")) == NULL)
	{
		printf("File open failed.");
		exit(1);
	}
	fseek(fp, 1024*1024*1024L, SEEK_SET);
	
	//InitGuideBlock(fp);
	fflush(fp);
	//3s
	printf("\t已创建名为%s的Mini-FS空间！3秒后进入空间.  \r", SName);
	Sleep(333);
	printf("\t已创建名为%s的Mini-FS空间！3秒后进入空间.. \r", SName);
	Sleep(333);
	printf("\t已创建名为%s的Mini-FS空间！3秒后进入空间...\r", SName);
	Sleep(333);
	//2s
	printf("\t已创建名为%s的Mini-FS空间！2秒后进入空间.  \r", SName);
	Sleep(333);
	printf("\t已创建名为%s的Mini-FS空间！2秒后进入空间.. \r", SName);
	Sleep(333);
	printf("\t已创建名为%s的Mini-FS空间！2秒后进入空间...\r", SName);
	Sleep(333);
	//1s
	printf("\t已创建名为%s的Mini-FS空间！1秒后进入空间.  \r", SName);
	Sleep(333);
	printf("\t已创建名为%s的Mini-FS空间！1秒后进入空间.. \r", SName);
	Sleep(333);
	printf("\t已创建名为%s的Mini-FS空间！1秒后进入空间...\r", SName);
	Sleep(333);
	return fp;
}

FILE *MountSpace(char *SName)
{
	FILE *fp;
	if ((fp = fopen(SName, "r+")) == NULL)
	{
		printf("File open failed.Please try again.");
	}
	else
	{
		ReadGuideBlock(fp);
		printf("\t已加载Mini-FS空间“%s”！3秒后进入空间.  \r", SName);
		Sleep(333);
		printf("\t已加载Mini-FS空间“%s”！3秒后进入空间.. \r", SName);
		Sleep(333);
		printf("\t已加载Mini-FS空间“%s”！3秒后进入空间...\r", SName);
		Sleep(333);
		//2s
		printf("\t已加载Mini-FS空间“%s”！2秒后进入空间.  \r", SName);
		Sleep(333);
		printf("\t已加载Mini-FS空间“%s”！2秒后进入空间.. \r", SName);
		Sleep(333);
		printf("\t已加载Mini-FS空间“%s”！2秒后进入空间...\r", SName);
		Sleep(333);
		//1s
		printf("\t已加载Mini-FS空间“%s”！1秒后进入空间.  \r", SName);
		Sleep(333);
		printf("\t已加载Mini-FS空间“%s”！1秒后进入空间.. \r", SName);
		Sleep(333);
		printf("\t已加载Mini-FS空间“%s”！1秒后进入空间...\r", SName);
		Sleep(333);
	}
	return fp;
}

void InitGuideBlock(FILE* header)
{
	GuideManager& manager = GuideManager::GetInstance();
	manager.Header = header;
	byte bytes[8 * 1024];
	memset(bytes, 0, sizeof(bytes));
	manager.contentMap = new Bitmap(bytes, 8 * 1024);

	manager.fileCount = 0;

}

//读入引导块
void ReadGuideBlock(FILE* header)
{
	GuideManager& manager = GuideManager::GetInstance();
	manager.Header = header;
	//首先读入内容bitmap
	byte bytes[8 * 1024];
	memset(bytes, 0, sizeof(bytes));
	fread(bytes, sizeof(byte), CONTENTBLOCKCOUNT/8, header);
	manager.contentMap = new Bitmap(bytes, 8 * 1024);

	int fileCount;
	FILE* h = header;
	fseek(h, 8 * 1024, SEEK_SET);
	fread(&fileCount, sizeof(int), 1, h);
	manager.fileCount = fileCount;

	fseek(header, BLOCK_SIZE, SEEK_SET);
	UFD* ufds=(UFD*)malloc(sizeof(UFD)*2500);
	fread(ufds, sizeof(UFD), fileCount, header);
	for (int i = 0; i < fileCount; i++)
	{
		manager.files->push_front(ufds[i]);
	}
	return;
}

void WriteGuideBlock(FILE* header)
{
	GuideManager& manager = GuideManager::GetInstance();
    Bitmap& map = *manager.contentMap;
	FILE* p = header;
	fwrite(map.Deserialize(), sizeof(byte), map.GetByteLength(), p);

	fwrite(&manager.fileCount, sizeof(int), 1, p);

	p = header;
	fseek(p, BLOCK_SIZE, SEEK_CUR);
	list<UFD>::iterator iter = manager.files->begin();
	while (iter != manager.files->end())
	{
		fwrite(iter._Ptr, sizeof(UFD), 1, p);
		iter++;
	}

}

void DeleteSpace(char *SName)
{
	if (remove(SName) == 0)
	{
		printf("\t已成功删除空间“%s”！\n", SName);
	}
	else
		printf("\t空间删除失败，请检查此空间是否存在或正被使用\n");
}