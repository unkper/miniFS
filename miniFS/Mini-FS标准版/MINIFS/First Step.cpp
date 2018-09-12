#include"define.h"
#include"GuideManager.h"

FILE *CreateSpace(char *SName)
{
	bool check;
	FILE *fp, *Sysfp;
	if ((fp = fopen(SName, "r+")) == NULL)
	{
		check = true;
	}
	else
	{
		printf("\t存在同名文件，操作无法进行！\n");
		fclose(fp);
		return NULL;
	}

	if ((fp = fopen(SName, "w+")) == NULL)
	{
		printf("\t空间创建失败.\n");
		exit(1);
	}
	if ((Sysfp = fopen("Sysfile.txt", "r+")) != NULL)
	{
		fseek(Sysfp, 0L, SEEK_END);
		fprintf(Sysfp, "%15s", SName);
		fflush(Sysfp);
		//printf( "%s ", SName);
		//printf("空间信息写入完成！\n");
		//Sleep(1000);
	}
	else
		printf("\t空间信息写入失败！\n");
	fseek(fp, 1024 * 1024 * 1024L, SEEK_SET);//*1024*1024
	fprintf(fp, "end\n");
	fflush(fp);
	fseek(fp, 0, 0);
	InitGuideBlock();

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
	Sleep(333);/**/
	return fp;
}

FILE *MountSpace(char *SName)
{
	FILE *fp;
	if ((fp = fopen(SName, "rb+")) == NULL)
	{
		printf("\tFile open failed.Please try again.\n");
	}
	else
	{
		printf("\t正加载Mini-FS空间“%s”！3秒后进入空间.  \r", SName);
		Sleep(333);
		printf("\t正加载Mini-FS空间“%s”！3秒后进入空间.. \r", SName);
		Sleep(333);
		printf("\t正加载Mini-FS空间“%s”！3秒后进入空间...\r", SName);
		Sleep(333);
		//2s
		printf("\t正加载Mini-FS空间“%s”！2秒后进入空间.  \r", SName);
		Sleep(333);
		printf("\t正加载Mini-FS空间“%s”！2秒后进入空间.. \r", SName);
		Sleep(333);
		printf("\t正加载Mini-FS空间“%s”！2秒后进入空间...\r", SName);
		Sleep(333);
		//1s
		printf("\t正加载Mini-FS空间“%s”！1秒后进入空间.  \r", SName);
		Sleep(333);
		printf("\t正加载Mini-FS空间“%s”！1秒后进入空间.. \r", SName);
		Sleep(333);
		printf("\t正加载Mini-FS空间“%s”！1秒后进入空间...\r", SName);
		Sleep(333);/**/
	}
	return fp;
}

void BrowseFiles()
{
	FILE *fp;
	char ch;
	if ((fp = fopen("Sysfile.txt", "r+")) == NULL)
	{
		printf("\t浏览失败！\n");
		return;
	}
	while ((ch = fgetc(fp)) != EOF)
	{
		putchar(ch);
	}
	putchar('\n');
	return;
}

void InitGuideBlock()
{
	GuideManager& manager = GuideManager::GetInstance();
	byte bytes[8 * 1024];
	memset(bytes, 0, sizeof(bytes));
	manager.contentMap = new Bitmap(bytes, 8 * 1024);
	memset(manager.allFiles, 0, sizeof(manager.allFiles));
	//新建一个根文件夹
	UFD rootFolder = CreateUFD("root", "fld");
	rootFolder.attribute = 1;
	manager.allFiles[manager.fileCount++] = rootFolder;
	return;
}
//读入引导块
void ReadGuideBlock()
{
	GuideManager& manager = GuideManager::GetInstance();
	FILE* h = SPACE;
	//首先读入内容bitmap
	byte bytes[8 * 1024];
	int i = 0;
	memset(bytes, 0, sizeof(bytes));
	for (i = 0; i < 8 * 1024; i++)
		fscanf(h, "%c", &bytes[i]);
	manager.contentMap = new Bitmap(bytes, 8 * 1024);
	fseek(h, BLOCK_SIZE, SEEK_SET);
	fread(manager.allFiles, sizeof(UFD), MAXFILESNUMBER, h);
	for (i = 0; ; i++)
	{
		if (strlen(manager.allFiles[i].name) == 0)
			break;
	}
	manager.fileCount = i;
	return;
}

void WriteGuideBlock()
{
	GuideManager& manager = GuideManager::GetInstance();
	Bitmap& map = *manager.contentMap;
	byte* mapData = map.Deserialize();
	FILE* p = SPACE;
	for (int i = 0; i < 8 * 1024; i++)
		fprintf(p, "%c", mapData[i]);
	fflush(p);
	p = SPACE;
	fseek(p, BLOCK_SIZE, SEEK_SET);
	fwrite(manager.allFiles, sizeof(UFD), manager.fileCount, p);
	fflush(p);
	return;
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