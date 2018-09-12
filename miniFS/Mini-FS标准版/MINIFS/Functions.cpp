#include"define.h"
#include"GuideManager.h"

int WriteFile(FILE *fp,int);
void WriteContents(char *, int, int);

int NumOfChar;//����

short BlockReader(short keyValue, int size, unsigned char* temp)
{
	if (size>16 * 1024 - 2)
	{
		printf("size error!!\n");
		return NULL;
	}
	FILE* p = SPACE;
	fseek(p, (long)((keyValue + 32) * 16 * 1024), 0);
	short next = 0;
	fscanf(p, "%2d", &next);
	temp = (unsigned char*)malloc(sizeof(unsigned char)*size);
	for (int i = 0; i<size; i++)
		temp[i] = getc(p);
	return next;
}

bool BlockWriter(short keyValue, short nextkeyValue, unsigned char *content, int size)
{
	if (size>16 * 1024 - 2)
	{
		printf("content length error!!\n");
		return false;
	}
	FILE* p = SPACE;
	fseek(p, (long)((keyValue + 32) * 16 * 1024), 0);
	fprintf(p, "%2d", nextkeyValue);
	for (int i = 0; i<size; i++)
		putc(content[i], p);
	return true;
}

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

bool Copy_File()
{
	char SystemName[10];
	char FileName[10];
	char FileEXTName[10];
	scanf("%s", SystemName);
	Encode(SystemName);
	if (strcmp(SystemName, "mini") == 0)
	{
		scanf("%s.%s", FileName, FileEXTName);
		scanf("%s", SystemName);
		Encode(SystemName);
		if (strcmp(SystemName, "mini") == 0)
		{

			return true;
		}
		else if (strcmp(SystemName, "win") == 0)
		{
			return MiniToWin(FileName);
		}
		else
			return false;
	}
	else if (strcmp(SystemName, "win") == 0)
	{
		scanf("%s", FileName);
		scanf("%s", SystemName);
		Encode(SystemName);
		if (strcmp(SystemName, "mini") == 0)
		{
			return WinToMini(FileName);
		}
		else
			return false;
	}
	else
		return false;
}

bool WinToMini(char *FileName) //, char *FileEXTName
{
	FILE *fp;
	time_t t = time(0);
	char tmp[15];
	char filename[15] = { 0 };
	char name[15] = { 0 };
	char ext[4] = { 0 };
	int index;
	GuideManager& manager = GuideManager::GetInstance();
	strcpy(filename, FileName);
	memset(tmp, 0, sizeof(tmp));
	strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S", localtime(&t));

	//UFD newFile;
	//newFile.length = 0;

	//strcpy(newFile.create_time, tmp);
	//strcpy(newFile.edit_time, tmp);	
	strcpy(name, strtok(filename, "."));
	strcpy(ext, strtok(NULL, "."));
	index = m_CreateFile(filename, ext, 0, manager.nowFolderIndex);
	//���-1��unsigned shortΪ��ֵ��
	int numofchar = 0, numofblocks = 0, i = 0, flag = 0;
	int RequireBlockNum = numofchar / (BLOCK_SIZE - 2) + 1;
	if ((fp = fopen(FileName, "rb+")) == NULL)
	{
		return false;
	}
	else
	{
		//newFile.length = numofchar;
		while (RequireBlockNum > 0)
		{
			while (manager.contentMap->GetBlockState(i))
			{
				i++;
			}
			if (flag == 0)
			{
				numofblocks = i;
				flag = 1;
			}
			//WriteContents(FileName, numofchar, i);
			RequireBlockNum--;
		}
		numofchar = WriteFile(fp,numofblocks);
		//WriteContents(FileName, numofchar, numofblocks);
		//
		NumOfChar = numofchar;
		manager.allFiles[index].keyvalue = numofblocks;
		manager.allFiles[index].length = numofchar;
		return true;
	}
}

bool MiniToWin(char *FileName)
{
	char ch;
	int startnum,numofchar;
	GuideManager& manager = GuideManager::GetInstance();
	int i = manager.allFiles[manager.nowFolderIndex].firstChildFile;
	char m_name[15];
	while (i != NULLFILE)
	{
		UFD file = manager.allFiles[i];
		memset(m_name, 0, sizeof(m_name));
		strcpy(m_name, file.name);
		strcat(m_name, ".");
		strcat(m_name, file.extension);
		if (strcmp(m_name, FileName) == 0)
		{
			startnum = file.keyvalue;
			numofchar = file.length;
			break;
		}
		i = file.nextFileIndex;
	}
	//return -1;
	//long  GetStartFp(FileName);
	if (startnum == -1)
	{
		printf("��Ŀ¼���޴��ļ��������¼�飡\n");
		return false;
	}
	FILE *newfp;
	fseek(SPACE, (startnum+32)*BLOCK_SIZE, SEEK_SET);
	if ((newfp = fopen(FileName, "wb+")) == NULL)
	{
		return false;
	}
	else
	{
		i = 0;
		while (i<numofchar)
		{
			ch = getc(SPACE);
			fprintf(newfp, "%c", ch);
			i++;
		}
		fflush(newfp);
		fclose(newfp);
		return true;
	}
}

void WriteContents(char *Filename, int Length, int numofblocks)
{
	//char ch;
	struct tm *p;
	int i;
	fseek(SPACE, (numofblocks+32)* BLOCK_SIZE, SEEK_SET);
	//�ļ���+��չ��
	fprintf(SPACE, "%13s", Filename);
	//printf("%13s", Filename);
	// �ļ���ʼ�̿��
	fprintf(SPACE, "%2d", numofblocks);
	//printf( "%2d", numofblocks);
	// �ļ�����
	fprintf(SPACE, "%8d", Length);
	//printf("%8d", Length);
	//����ʱ��+�༭ʱ��
	p = GetTime();
	fprintf(SPACE, "%d%.2d%.2d%.2d%.2d%.2d ", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
	fprintf(SPACE, "%d%.2d%.2d%.2d%.2d%.2d ", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
	fflush(SPACE);
	//printf("%d%.2d%.2d%.2d%.2d%.2d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday,8+p->tm_hour, p->tm_min, p->tm_sec);
	return;
}

int WriteFile(FILE *fp,int numofblocks)
{
	char ch;
	int numofchar = 0;
	fseek(SPACE, (numofblocks+32)*BLOCK_SIZE, SEEK_SET);
	while ((ch = getc(fp)) != EOF)
	{
		//fseek(SPACE,0L, SEEK_CUR);
		fprintf(SPACE, "%c", ch);
		//putchar(ch);
		numofchar++;
		fflush(SPACE);
	}
	putchar('\n');
	fclose(fp);
	return numofchar;
}

UFD CreateUFD(char* fileName, char* fileExtName)//���UFD������������û����ֵ
{
	UFD newFile;
	strcpy(newFile.create_time, FormatTime());
	strcpy(newFile.edit_time, FormatTime());
	strcpy(newFile.name, fileName);
	strcpy(newFile.extension, fileExtName);
	newFile.fatherFolderIndex = NULLFILE;
	newFile.firstChildFile = NULLFILE;
	newFile.frontFileIndex = NULLFILE;
	newFile.keyvalue = NULLFILE;
	newFile.length = 0;
	newFile.nextFileIndex = NULLFILE;
	return newFile;
}

char* FormatTime()
{
	struct tm *m_time = GetTime();
	char timeString[15] = { 0 };
	char format[5] = { 0 };
	sprintf(format, "%4d", (1900 + m_time->tm_year));
	strcat(timeString, format);
	sprintf(format, "%.2d", (1 + m_time->tm_mon));
	strcat(timeString, format);
	sprintf(format, "%.2d", (m_time->tm_mday));
	strcat(timeString, format);
	sprintf(format, "%.2d", (8 + m_time->tm_hour));
	strcat(timeString, format);
	sprintf(format, "%.2d", (m_time->tm_min));
	strcat(timeString, format);
	sprintf(format, "%.2d", (m_time->tm_sec));
	strcat(timeString, format);
	printf("%s", timeString);
	return timeString;
}

struct tm *GetTime()
{
#include<time.h>	
	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	return p;
}

long GetStartFp(char *Filename)
{
	GuideManager& manager = GuideManager::GetInstance();
	int i = manager.allFiles[manager.nowFolderIndex].firstChildFile;
	char m_name[15];
	while (i != NULLFILE)
	{
		UFD file = manager.allFiles[i];
		memset(m_name, 0, sizeof(m_name));
		strcpy(m_name, file.name);
		strcat(m_name, ".");
		strcat(m_name, file.extension);
		if (strcmp(m_name, Filename) == 0)
		{
			return file.keyvalue;
		}
		i = file.nextFileIndex;
	}
	return -1;
}

//���ص��Ǵ����õ�UFD�������������
int m_CreateFile(char* Filename, char* FileExtname, bool isFolder, int fatherFolderIndex)
{
	if (strlen(Filename) > 8)
	{
		printf("\t�ļ������ȱ���С��9\n");
		return 0;
	}
	if (strlen(FileExtname) > 3)
	{
		printf("\t�ļ���׺�����ȱ���С��4\n");
		return 0;
	}
	int flag = FindFile(Filename, FileExtname);
	if (flag != NULLFILE)
	{
		printf("\t����ͬ���ļ�\n");
		return 0;
	}
	GuideManager& manager = GuideManager::GetInstance();
	unsigned short Index = manager.fileCount++;
	UFD newFile = CreateUFD(Filename, FileExtname);
	UFD fatherFolder = manager.allFiles[fatherFolderIndex];
	if (fatherFolder.attribute != 1)
	{
		printf("\t���ļ��в����ļ�������\n");
		return 0;
	}
	strcpy(fatherFolder.edit_time, FormatTime());
	if (isFolder || strcmp(FileExtname, "fld") == 0)
		newFile.attribute = 1;
	else
		newFile.attribute = 0;
	if (fatherFolder.firstChildFile == NULLFILE)
	{
		fatherFolder.firstChildFile = Index;
		newFile.fatherFolderIndex = fatherFolderIndex;
	}
	else
	{
		//������ͷ����
		unsigned short nextIndex = fatherFolder.firstChildFile;
		UFD next = manager.allFiles[nextIndex];
		next.frontFileIndex = Index;
		newFile.nextFileIndex = nextIndex;
		newFile.fatherFolderIndex = fatherFolderIndex;
		fatherFolder.firstChildFile = Index;
		manager.allFiles[nextIndex] = next;
	}
	manager.allFiles[fatherFolderIndex] = fatherFolder;
	manager.allFiles[Index] = newFile;
	WriteGuideBlock();
	return Index;
}

void CloseSpace()
{
	return WriteGuideBlock();
}

//Ҫ�����ļ��У���չ��Ϊfld,�����ļ�������չ����ȫһ����
unsigned short FindFile(char* fileName, char* fileExtName)
{
	GuideManager& manager = GuideManager::GetInstance();
	int i = manager.allFiles[manager.nowFolderIndex].firstChildFile;
	while (i != NULLFILE)
	{
		UFD file = manager.allFiles[i];
		if (strcmp(file.name, fileName) == 0 && strcmp(file.extension, fileExtName) == 0)
			return i;
		i = file.nextFileIndex;
	}
	return NULLFILE;
}

void ViewAllFiles()
{
	GuideManager& manager = GuideManager::GetInstance();
	int i = manager.allFiles[manager.nowFolderIndex].firstChildFile;
	while (i != NULLFILE)
	{
		UFD file = manager.allFiles[i];
		printf("\t%s.%s\n", file.name, file.extension);
		i = file.nextFileIndex;
	}
}

void ShowFileAttribute(char * Filename)
{
	int flag = 0, i, Extflag = 0;
	char filename[9], extenname[4] = { 0 };

	for (i = 0; Filename[i] != 0; i++)
	{
		if (Filename[i] == '.')
			Extflag = 1;
	}
	if (Extflag == 0)
	{
		printf("\tû�������ļ���׺�������������룡\n");
		return;
	}
	strcpy(filename, strtok(Filename, "."));
	strcpy(extenname, strtok(NULL, "."));
	GuideManager& manager = GuideManager::GetInstance();
	int index = manager.allFiles[manager.nowFolderIndex].firstChildFile;
	while (index != NULLFILE)
	{
		UFD file = manager.allFiles[index];
		if (strcmp(file.name, filename) == 0 && strcmp(file.extension, extenname) == 0)
		{
			char createTime[20], editTime[20];
			printf("%s.%s ��Ϣ��\n", file.name, file.extension);
			printf("\t�ļ���С��%ld\n", file.length);
			strcpy(createTime, file.create_time);
			strcpy(editTime, file.edit_time);
			printf("\t����ʱ�䣺  ");
			for (int i = 0; i < 4; i++)
				printf("%c", createTime[i]);
			printf("-");
			for (int i = 4; i < 6; i++)
				printf("%c", createTime[i]);
			printf("-");
			for (int i = 6; i < 8; i++)
				printf("%c", createTime[i]);
			printf(" ");
			for (int i = 8; i < 10; i++)
				printf("%c", createTime[i]);
			printf(":");
			for (int i = 10; i < 12; i++)
				printf("%c", createTime[i]);
			printf(":");
			for (int i = 12; i < 14; i++)
				printf("%c", createTime[i]);
			printf("\n");


			printf("\t���һ�α༭ʱ�䣺  ");
			for (int i = 0; i < 4; i++)
				printf("%c", editTime[i]);
			printf("-");
			for (int i = 4; i < 6; i++)
				printf("%c", editTime[i]);
			printf("-");
			for (int i = 6; i < 8; i++)
				printf("%c", editTime[i]);
			printf(" ");
			for (int i = 8; i < 10; i++)
				printf("%c", editTime[i]);
			printf(":");
			for (int i = 10; i < 12; i++)
				printf("%c", editTime[i]);
			printf(":");
			for (int i = 12; i < 14; i++)
				printf("%c", editTime[i]);
			printf("\n");
			flag = 1;
			break;
		}
		index = file.nextFileIndex;
	}
	if (flag == 0)
		printf("\t�ļ������ڣ���\n");
}

void ShowHelpInfo()
{
	char cmdname[20];//��������
	scanf("%s", cmdname);

	if (cmdname == "\0")
	{
		printf("�й�ĳ���������ϸ��Ϣ������� help ������\n\n");
		printf("cd		�����ָ��Ŀ¼��\n");
		printf("create		����һ���µ��ļ�\n");
		printf("cp		��һ���ļ����Ƶ���һ��λ��\n");
		printf("dl		ɾ������һ���ļ�\n");
		printf("dr		��ʾ��ǰĿ¼�е��ļ����ļ���\n");
		printf("tp		����ͨ�ı���ʽ��ʾһ���ļ�������\n");
		printf("more		�Է�ҳ�ı���ʽ��ʾһ���ļ�������\n");
		printf("fmt		��ʽ������\n");
		printf("att		��ʾһ���ļ��ľ�������\n");
		printf("rc		�ָ�һ����ɾ���ļ�\n");
		printf("edit		�༭�ļ�����\n");
		printf("close		�ر�miniUFSϵͳ\n");
		printf("\n");
	}
	else
	{
		if (strcmp(cmdname, "create") == 0)
		{
			printf("����һ���µ��ļ���\n");
			printf("\n");
			printf("create [path] [dirname]\n\n");
			printf("path		����·�������·������,����ָ����Ҫɾ���ļ��еľ���λ��\n");
			printf("dirname		�������ļ�������\n");
			printf("�����������ϵͳ��ʹ��Ĭ���ļ����������ļ��С�\n\n");
			printf("�ڵ�ǰĿ¼�´���һ���µ��ļ���\n");
			printf("NEWDIR ����ո���Ϊ�ָ���������Ŀ¼���벻Ҫ�����ո�\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "fmt") == 0)
		{
			printf("��ʽ������\n");
			printf("\n");
			printf("fmt [-option]\n\n");
			printf("���� option:\n");
			printf("	-d : �ͼ���ʽ��\n");
			printf("	-n : ��ͨ��ʽ��\n");
			printf("	�����дѡ����Ĭ��ʹ�� -n ѡ�\n\n");
			printf("ִ�гɹ��󣬽����ʽ���������̿ռ䣬�������������ļ�\n");
			printf("ϵͳ�ļ��Ƚ����ָ����״̬\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "dr") == 0)
		{
			printf("��ʾ��ǰĿ¼�е��ļ����ļ���\n");
			printf("\n");
			printf("dr [filename]\n\n");
			printf("filename ָ��Ҫ�г����ļ�����֧��������ʽ��\n\n");
			printf("������ִ�гɹ�������Ļ���г���ǰĿ¼�µ������ļ����ļ���\n\n");
			printf("�ļ����ļ��н����ļ�����ĸ˳������\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "cp") == 0)
		{
			printf("��һ���ļ����Ƶ���һ��λ��\n");
			printf("\n");
			printf("cp [path1]filename1  [path2]filename2\n\n");
			printf("path1 path2 ����·�������·������,����ָ���ļ��ľ���λ�� \n");
			printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "dl") == 0)
		{
			printf("ɾ������һ���ļ���\n");
			printf("\n");
			printf("dl [path] dirname\n\n");
			printf("path		����·�������·������,����ָ����Ҫɾ���ļ��еľ���λ��\n");
			printf("dirname		��Ҫɾ�����ļ������ƣ�֧��ʹ��ͨ�����\n\n");
			printf("������ļ����Լ���������ļ��к��ļ�һ��ɾ��\n");
			printf("DELDIR ����ո���Ϊ�ָ���������Ŀ¼���벻Ҫ�����ո�\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "att") == 0)
		{
			printf("��ʾһ���ļ��еľ�������\n");
			printf("\n");
			printf("att [path]dirname\n\n");
			printf("path  ����·�������·������,����ָ���ļ��еľ���λ�� \n\n");
			printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n");
			printf("ִ�гɹ��󽫻���ʾ�ļ��е����ԣ���ɶ���д��\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "edit") == 0)
		{
			printf("�༭�ļ�����\n");
			printf("\n");
			printf("edit [-option] [path]filename \n\n");
			printf("���� option��\n\n");
			printf("	-w : �Ը�д��ʽ���ļ���\n");
			printf("	-a : ��׷����ʽ���ļ���\n");
			printf("	-vim : ʹ��Vim���ļ���\n");
			printf("	��������ѡ����Ĭ��ʹ�� -a ѡ�\n\n");
			printf("path  ����·�������·������,����ָ���ļ��ľ���λ�� \n");
			printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n\n");
			printf("filename ��Ҫ�༭���ļ�����\n");
			printf("ִ�гɹ��󣬿��Լ�����д���ļ��е�����\n\n");
			printf("ʹ�� -w �� -a ѡ��ʱ��Ҫ�����༭��CTRL + C\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "tp") == 0)
		{
			printf("����ͨ�ı���ʽ��ʾһ���ļ�������\n");
			printf("\n");
			printf("tp [path]filename\n\n");
			printf("path  ����·�������·������,����ָ���ļ��ľ���λ�� \n");
			printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n\n");
			printf("filename ��Ҫ��ʾ���ļ�����\n\n");
			printf("ִ�гɹ��󽫻��ָ���ļ��е������������Ļ��\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "back") == 0)
		{
			printf("��ʾһ���ļ��еľ�������\n");
			printf("\n");
			printf("att [path]dirname\n\n");
			printf("path  ����·�������·������,����ָ���ļ��еľ���λ�� \n\n");
			printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n");
			printf("ִ�гɹ��󽫻���ʾ�ļ��е����ԣ���ɶ���д��\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "close") == 0)
		{
			printf("�ر�miniUFSϵͳ\n");
			printf("\n");
			printf("close\n");
			printf("ִ�гɹ��󣬽���ر�miniUFSϵͳ\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
		}
		else
		{
			printf("�Ҳ�����Ӧ���\n");
		}
	}
}

void EnterFolder(char* fileName)
{
	char filename[9] = { 0 }, extenname[4] = { 0 };
	int i, Extflag = 0, flag = 0;
	for (i = 0; fileName[i] != 0; i++)
	{
		if (fileName[i] == '.')
			Extflag = 1;
	}
	if (Extflag == 0)
	{
		printf("\tû�������ļ���׺�������������룡\n");
		return;
	}
	strcpy(filename, strtok(fileName, "."));
	strcpy(extenname, strtok(NULL, "."));
	if (strcmp(extenname, "fld") != 0)
		printf("\t���벻���ļ��У����������룡\n");
	else
	{
		GuideManager& manager = GuideManager::GetInstance();
		int i = manager.allFiles[manager.nowFolderIndex].firstChildFile;
		while (i != NULLFILE)
		{
			UFD file = manager.allFiles[i];
			if (strcmp(filename, manager.allFiles[i].name) == 0 && strcmp(extenname, manager.allFiles[i].extension) == 0)
			{
				manager.nowFolderIndex = i;
				flag = 1;
				break;
			}
			else
			{
				i = manager.allFiles[i].nextFileIndex;
			}
		}
		if (flag == 0)
			printf("�ļ���%s.%s�����ڣ���\n", filename, extenname);
	}
}

void BackToFatherFolder()
{
	GuideManager& manager = GuideManager::GetInstance();
	if (manager.nowFolderIndex != 0)
		manager.nowFolderIndex = manager.allFiles[manager.nowFolderIndex].fatherFolderIndex;
	else printf("�Ѿ��ڸ��ļ����£���");
}

bool ShowTXTFile(char *Filename)
{
	GuideManager& manager = GuideManager::GetInstance();
	int i = manager.allFiles[manager.nowFolderIndex].firstChildFile;
	while (i != NULLFILE)
	{
		UFD file = manager.allFiles[i];
		if ((strcmp(file.name, Filename) == 0))
		{
			PrintTXT(file.keyvalue,file.length);
			return true;
		}
		i= file.nextFileIndex;
	}
	return false;
}

void PrintTXT(unsigned short key,int length)
{
	char ch;
	int i = 0;
	fseek(SPACE, (key+32)*BLOCK_SIZE, SEEK_SET);
	while (i < length)
	{
		ch = getc(SPACE);
		printf( "%c", ch);
		i++;
	}
	return ;
}