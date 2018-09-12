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
		printf("\t����ͬ���ļ��������޷����У�\n");
		fclose(fp);
		return NULL;
	}

	if ((fp = fopen(SName, "w+")) == NULL)
	{
		printf("\t�ռ䴴��ʧ��.\n");
		exit(1);
	}
	if ((Sysfp = fopen("Sysfile.txt", "r+")) != NULL)
	{
		fseek(Sysfp, 0L, SEEK_END);
		fprintf(Sysfp, "%15s", SName);
		fflush(Sysfp);
		//printf( "%s ", SName);
		//printf("�ռ���Ϣд����ɣ�\n");
		//Sleep(1000);
	}
	else
		printf("\t�ռ���Ϣд��ʧ�ܣ�\n");
	fseek(fp, 1024 * 1024 * 1024L, SEEK_SET);//*1024*1024
	fprintf(fp, "end\n");
	fflush(fp);
	fseek(fp, 0, 0);
	InitGuideBlock();

	//3s
	printf("\t�Ѵ�����Ϊ%s��Mini-FS�ռ䣡3������ռ�.  \r", SName);
	Sleep(333);
	printf("\t�Ѵ�����Ϊ%s��Mini-FS�ռ䣡3������ռ�.. \r", SName);
	Sleep(333);
	printf("\t�Ѵ�����Ϊ%s��Mini-FS�ռ䣡3������ռ�...\r", SName);
	Sleep(333);
	//2s
	printf("\t�Ѵ�����Ϊ%s��Mini-FS�ռ䣡2������ռ�.  \r", SName);
	Sleep(333);
	printf("\t�Ѵ�����Ϊ%s��Mini-FS�ռ䣡2������ռ�.. \r", SName);
	Sleep(333);
	printf("\t�Ѵ�����Ϊ%s��Mini-FS�ռ䣡2������ռ�...\r", SName);
	Sleep(333);
	//1s
	printf("\t�Ѵ�����Ϊ%s��Mini-FS�ռ䣡1������ռ�.  \r", SName);
	Sleep(333);
	printf("\t�Ѵ�����Ϊ%s��Mini-FS�ռ䣡1������ռ�.. \r", SName);
	Sleep(333);
	printf("\t�Ѵ�����Ϊ%s��Mini-FS�ռ䣡1������ռ�...\r", SName);
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
		printf("\t������Mini-FS�ռ䡰%s����3������ռ�.  \r", SName);
		Sleep(333);
		printf("\t������Mini-FS�ռ䡰%s����3������ռ�.. \r", SName);
		Sleep(333);
		printf("\t������Mini-FS�ռ䡰%s����3������ռ�...\r", SName);
		Sleep(333);
		//2s
		printf("\t������Mini-FS�ռ䡰%s����2������ռ�.  \r", SName);
		Sleep(333);
		printf("\t������Mini-FS�ռ䡰%s����2������ռ�.. \r", SName);
		Sleep(333);
		printf("\t������Mini-FS�ռ䡰%s����2������ռ�...\r", SName);
		Sleep(333);
		//1s
		printf("\t������Mini-FS�ռ䡰%s����1������ռ�.  \r", SName);
		Sleep(333);
		printf("\t������Mini-FS�ռ䡰%s����1������ռ�.. \r", SName);
		Sleep(333);
		printf("\t������Mini-FS�ռ䡰%s����1������ռ�...\r", SName);
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
		printf("\t���ʧ�ܣ�\n");
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
	//�½�һ�����ļ���
	UFD rootFolder = CreateUFD("root", "fld");
	rootFolder.attribute = 1;
	manager.allFiles[manager.fileCount++] = rootFolder;
	return;
}
//����������
void ReadGuideBlock()
{
	GuideManager& manager = GuideManager::GetInstance();
	FILE* h = SPACE;
	//���ȶ�������bitmap
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
		printf("\t�ѳɹ�ɾ���ռ䡰%s����\n", SName);
	}
	else
		printf("\t�ռ�ɾ��ʧ�ܣ�����˿ռ��Ƿ���ڻ�����ʹ��\n");
}