#include"define.h"
#include"GuideManager.h"

int ReceiveSIns(char *);

char Filename[9];
char FileExtname[4];

bool ScanfFileName(char * Filename, char* FileExtname)
{
	char m_string[15];
	int i, Extflag = 0;
	memset(m_string, 0, sizeof(m_string));
	scanf("%s", m_string);
	for (i = 0; m_string[i] != 0; i++)
	{
		if (m_string[i] == '.')
			Extflag = 1;
	}
	if (Extflag == 0)
	{
		printf("\t没有输入文件后缀名，请重新输入！\n");
		return false;
	}
	strcpy(Filename, strtok(m_string, "."));
	strcpy(FileExtname, strtok(NULL, "."));
	return true;
}

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
	printf("Mini-FS>");

	GuideManager manager = GuideManager::GetInstance();
	//显示命令行前的路径
	int save[30] = { 0 };
	int i = 0;
	int index = manager.nowFolderIndex;
	for (i = 0; ; i++)
	{
		save[i] = index;
		if (manager.allFiles[index].fatherFolderIndex == NULLFILE)
			break;
		else
			index = manager.allFiles[index].fatherFolderIndex;
	}
	for (; i >= 0; i--)
		printf("%s>", manager.allFiles[save[i]].name);

	scanf("%s", instruction);
	Encode(instruction);
	//格式化空间
	if (strcmp(instruction, "fmt") == 0)
	{
		//FormatSpace(Spacename);
		return 2;
	}

	//新建文件
	else if (strcmp(instruction, "new") == 0)
	{
		bool flag = ScanfFileName(Filename, FileExtname);
		if (flag == true)
		{
			if (m_CreateFile(Filename, FileExtname, false, manager.nowFolderIndex))
				printf("\t%s.%s 已经创建\n", Filename, FileExtname);
			else
				printf("\t创建失败\n");
		}
		return 3;
	}

	//显示目录中的文件
	else if (strcmp(instruction, "ls") == 0)
	{
		ViewAllFiles();
		return 4;
	}

	//复制文件
	else if (strcmp(instruction, "cp") == 0)
	{
		if (Copy_File())
			printf("文件复制成功！\n");
		else
			printf("文件复制失败，请检查此文件是否存在或指令格式是否正确！\n");
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
		bool flag = ScanfFileName(Filename, FileExtname);
		if (flag == true)
		{
			if (strcmp(FileExtname, "txt") != 0)
			{
				printf("\t目标文件不是文本文件，请重新输入！\n");				
			}
			else
			{
				if (ShowTXTFile(Filename) == false)
				{
					printf("\t文件显示错误，请检查此文件是否存在！\n");
				}
				else
					printf("\t文件显示成功！\n");
			}
		}
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
		BackToFatherFolder();
		return 4;
	}

	else if (strcmp(instruction, "pst") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		scanf("%s", Filename);
		//PasteFile(Filename);
		return 4;
	}

	//文件属性
	else if (strcmp(instruction, "att") == 0)
	{
		scanf("%s", Filename);
		ShowFileAttribute(Filename);
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
		EnterFolder(Filename);
		return 4;
	}

	//关闭空间
	else if (strcmp(instruction, "close") == 0)
	{
		CloseSpace();
		fclose(SPACE);
		printf("\t空间%s已关闭，1秒后退出空间！\n", Spacename);
		Sleep(1000);
		//CloseSpace();
		return -1;
	}

	//退出程序
	else if (strcmp(instruction, "exit") == 0)
	{
		CloseSpace();
		printf("\tMini-FS空间已退出！\n");
		exit(1);
		return 4;
	}

	//清屏
	else if (strcmp(instruction, "clean") == 0)
	{
		system("cls");
		FunctionGuide(Spacename);
		return 4;
	}

	else
	{
		printf("指令无效，请重试！\n");
	}
	return 0;
}
