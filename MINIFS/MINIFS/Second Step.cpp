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
	printf("�ڴ˴�����ָ�\n");
	scanf("%s", instruction);
	Encode(instruction);
	if (strcmp(instruction, "close") == 0)
	{
		printf("\t�ռ�%s���˳���\n",Spacename);
		return -1;
	}

	//��ʽ���ռ�
	else if (strcmp(instruction, "fmt") == 0)
	{
		//FormatSpace(Spacename);
		return 2;
	}

	//�½��ļ�
	else if (strcmp(instruction, "new") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		memset(FileExtname, 0, sizeof(FileExtname));
		scanf("%s.%s", Filename, FileExtname);
		//CreateFile(Filename, FileExtname);
		return 3;
	}

	//��ʾĿ¼
	else if (strcmp(instruction, "dr") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		scanf("%s", Filename);
		//ShowDirectory(Filename)
		return 4;
	}

	//�����ļ�
	else if (strcmp(instruction, "cp") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		memset(FileExtname, 0, sizeof(FileExtname));
		scanf("%s.%s", Filename, FileExtname);
		//CopyFile(Filename, FileExtname);
		return 4;
	}

	//ɾ���ļ�
	else if (strcmp(instruction, "dl") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		memset(FileExtname, 0, sizeof(FileExtname));
		scanf("%s.%s", Filename, FileExtname);
		//DeleteFile(Filename, FileExtname);
		return 4;
	}

	//��ʾ�ı��ļ�
	else if (strcmp(instruction, "tp") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		scanf("%s", Filename);
		//ShowTXTFile(Filename);
		return 4;
	}

	//������Ϣ
	else if (strcmp(instruction, "help") == 0)
	{
		//ShowHelpInfo();
		return 4;
	}

	//�༭�ļ�
	else if (strcmp(instruction, "edit") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		scanf("%s", Filename);
		//EditFile(Filename);
		return 4;
	}

	//������һ��Ŀ¼
	else if (strcmp(instruction, "back") == 0)
	{
		//BacktoUpperDirectory();
		return 4;
	}

	//�����ǰĿ¼�ļ�
	else if (strcmp(instruction, "ls") == 0)
	{
		//BrowseFiles();
		return 4;
	}

	//���ظ�Ŀ¼
	else if (strcmp(instruction, "cd") == 0)
	{
		//BackToRootDirectory();
		return 4;
	}

	//�����ļ���
	else if (strcmp(instruction, "ent") == 0)
	{
		memset(Filename, 0, sizeof(Filename));
		scanf("%s", Filename);
		//EnterDirectory(Filename);
		return 4;
	}

	//�رտռ�
	else if (strcmp(instruction, "close") == 0)
	{
		//CloseSpace();
		return 4;
	}

	//�˳�����
	else if (strcmp(instruction, "exit") == 0)
	{
		//ExitProgram();
		return 4;
	}

	//����
	else if (strcmp(instruction, "clean") == 0)
	{
		//CleanScreen();
		return 4;
	}

	else
	{
		printf("ָ����Ч�������ԣ�\n");
	}
	return 0;
}/**/