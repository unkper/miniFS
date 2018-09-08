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
	fprintf(fp,"end\n");
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

void DeleteSpace(char *SName)
{
	if (remove(SName) == 0)
	{
		printf("\t�ѳɹ�ɾ���ռ䡰%s����\n", SName);
	}
	else
		printf("\t�ռ�ɾ��ʧ�ܣ�����˿ռ��Ƿ���ڻ�����ʹ��\n");
}