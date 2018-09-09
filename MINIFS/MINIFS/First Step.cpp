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
		printf("����ͬ���ļ��������޷����У�\n");
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
		printf("\t�Ѽ���Mini-FS�ռ䡰%s����3������ռ�.  \r", SName);
		Sleep(333);
		printf("\t�Ѽ���Mini-FS�ռ䡰%s����3������ռ�.. \r", SName);
		Sleep(333);
		printf("\t�Ѽ���Mini-FS�ռ䡰%s����3������ռ�...\r", SName);
		Sleep(333);
		//2s
		printf("\t�Ѽ���Mini-FS�ռ䡰%s����2������ռ�.  \r", SName);
		Sleep(333);
		printf("\t�Ѽ���Mini-FS�ռ䡰%s����2������ռ�.. \r", SName);
		Sleep(333);
		printf("\t�Ѽ���Mini-FS�ռ䡰%s����2������ռ�...\r", SName);
		Sleep(333);
		//1s
		printf("\t�Ѽ���Mini-FS�ռ䡰%s����1������ռ�.  \r", SName);
		Sleep(333);
		printf("\t�Ѽ���Mini-FS�ռ䡰%s����1������ռ�.. \r", SName);
		Sleep(333);
		printf("\t�Ѽ���Mini-FS�ռ䡰%s����1������ռ�...\r", SName);
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

//����������
void ReadGuideBlock(FILE* header)
{
	GuideManager& manager = GuideManager::GetInstance();
	manager.Header = header;
	//���ȶ�������bitmap
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
		printf("\t�ѳɹ�ɾ���ռ䡰%s����\n", SName);
	}
	else
		printf("\t�ռ�ɾ��ʧ�ܣ�����˿ռ��Ƿ���ڻ�����ʹ��\n");
}