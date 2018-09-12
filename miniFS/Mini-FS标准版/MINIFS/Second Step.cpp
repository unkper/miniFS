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
		printf("\tû�������ļ���׺�������������룡\n");
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
	//��ʾ������ǰ��·��
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
	//��ʽ���ռ�
	if (strcmp(instruction, "fmt") == 0)
	{
		//FormatSpace(Spacename);
		return 2;
	}

	//�½��ļ�
	else if (strcmp(instruction, "new") == 0)
	{
		bool flag = ScanfFileName(Filename, FileExtname);
		if (flag == true)
		{
			if (m_CreateFile(Filename, FileExtname, false, manager.nowFolderIndex))
				printf("\t%s.%s �Ѿ�����\n", Filename, FileExtname);
			else
				printf("\t����ʧ��\n");
		}
		return 3;
	}

	//��ʾĿ¼�е��ļ�
	else if (strcmp(instruction, "ls") == 0)
	{
		ViewAllFiles();
		return 4;
	}

	//�����ļ�
	else if (strcmp(instruction, "cp") == 0)
	{
		if (Copy_File())
			printf("�ļ����Ƴɹ���\n");
		else
			printf("�ļ�����ʧ�ܣ�������ļ��Ƿ���ڻ�ָ���ʽ�Ƿ���ȷ��\n");
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
		bool flag = ScanfFileName(Filename, FileExtname);
		if (flag == true)
		{
			if (strcmp(FileExtname, "txt") != 0)
			{
				printf("\tĿ���ļ������ı��ļ������������룡\n");				
			}
			else
			{
				if (ShowTXTFile(Filename) == false)
				{
					printf("\t�ļ���ʾ����������ļ��Ƿ���ڣ�\n");
				}
				else
					printf("\t�ļ���ʾ�ɹ���\n");
			}
		}
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

	//�ļ�����
	else if (strcmp(instruction, "att") == 0)
	{
		scanf("%s", Filename);
		ShowFileAttribute(Filename);
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
		EnterFolder(Filename);
		return 4;
	}

	//�رտռ�
	else if (strcmp(instruction, "close") == 0)
	{
		CloseSpace();
		fclose(SPACE);
		printf("\t�ռ�%s�ѹرգ�1����˳��ռ䣡\n", Spacename);
		Sleep(1000);
		//CloseSpace();
		return -1;
	}

	//�˳�����
	else if (strcmp(instruction, "exit") == 0)
	{
		CloseSpace();
		printf("\tMini-FS�ռ����˳���\n");
		exit(1);
		return 4;
	}

	//����
	else if (strcmp(instruction, "clean") == 0)
	{
		system("cls");
		FunctionGuide(Spacename);
		return 4;
	}

	else
	{
		printf("ָ����Ч�������ԣ�\n");
	}
	return 0;
}
