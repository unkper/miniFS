#include"define.h"


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
	fprintf(fp,"end\n");
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

void DeleteSpace(char *SName)
{
	if (remove(SName) == 0)
	{
		printf("\t已成功删除空间“%s”！\n", SName);
	}
	else
		printf("\t空间删除失败，请检查此空间是否存在或正被使用\n");
}