#include"define.h"

int ReceiveSIns(char *);

char Filename[9];
char FileExtname[4];

void DoSecondStep(char *SName)
{
	system("cls");
	FunctionGuide(SName);
	while (1)
	{
		switch (ReceiveSIns(SName)) {
			//-1 close program
		case -1: return; break;
		default: break;
		}
	}/**/
	return;
}

int ReceiveSIns(char *Spacename)
{
	printf("在此处输入指令：\n");
	scanf("%s", instruction);
	Encode(instruction);
	if (strcmp(instruction, "close") == 0)
	{
		printf("\t空间%s已退出！\n",Spacename);
		return -1;
	}

	//格式化空间
	else if (strcmp(instruction, "fmt") == 0)
	{
		//FormatSpace(Spacename);
		return 2;
	}

	//新建文件
	else if (strcmp(instruction, "new") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		memset(FileExtname, 0, sizeof(FileExtname));
		scanf("%s.%s", Filename, FileExtname);
		//CreateFile(Filename, FileExtname);
		return 3;
	}

	//显示目录
	else if (strcmp(instruction, "dr") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		scanf("%s", Filename);
		//ShowDirectory(Filename)
		return 4;
	}

	//复制文件
	else if (strcmp(instruction, "cp") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		memset(FileExtname, 0, sizeof(FileExtname));
		scanf("%s.%s", Filename, FileExtname);
		//CopyFile(Filename, FileExtname);
		return 4;
	}

	//删除文件
	else if (strcmp(instruction, "dl") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		memset(FileExtname, 0, sizeof(FileExtname));
		scanf("%s.%s", Filename, FileExtname);
		//DeleteFile(Filename, FileExtname);
		return 4;
	}

	//显示文本文件
	else if (strcmp(instruction, "tp") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		scanf("%s", Filename);
		//ShowTXTFile(Filename);
		return 4;
	}

	//帮助信息
	else if (strcmp(instruction, "help") == 0)
	{
		//ShowHelpInfo();
		return 4;
	}

	//编辑文件
	else if (strcmp(instruction, "edit") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		scanf("%s", Filename);
		//EditFile(Filename);
		return 4;
	}

	//返回上一级目录
	else if (strcmp(instruction, "back") == 0)
	{
		//BacktoUpperDirectory();
		return 4;
	}

	//浏览当前目录文件
	else if (strcmp(instruction, "ls") == 0)
	{
		//BrowseFiles();
		return 4;
	}

	//返回根目录
	else if (strcmp(instruction, "cd") == 0)
	{
		//BackToRootDirectory();
		return 4;
	}

	//进入文件夹
	else if (strcmp(instruction, "ent") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		scanf("%s", Filename);
		//EnterDirectory(Filename);
		return 4;
	}

	//关闭空间
	else if (strcmp(instruction, "close") == 0)
	{
		//CloseSpace();
		return 4;
	}

	//退出程序
	else if (strcmp(instruction, "exit") == 0)
	{
		//ExitProgram();
		return 4;
	}

	//清屏
	else if (strcmp(instruction, "clean") == 0)
	{
		//CleanScreen();
		return 4;
	}

	else
	{
		printf("指令无效，请重试！\n");
	}
	return 0;
}/**/