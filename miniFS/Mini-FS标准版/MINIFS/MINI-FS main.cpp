#include"define.h"

char instruction[100];
char Spacename[20];

//UFD PasteInfo;//�����壬��������
//char PasteContent[BLOCK_SIZE];//�����壬��������

//FILE *HeadfpofContents;
//FILE *HeadfpofFiles;
FILE *SPACE;

int ReceiveIns();

int main()
{
	//InitSystem();
	Title();	
	StartGuide();
	while (1)
	{
		switch (ReceiveIns()) {
			//-1 close program
			case -1: exit(1); break;
			default: break;
		}
	}
	return 0;
}

int ReceiveIns()
{
	printf("Mini-FS>");
	scanf("%s", instruction);
	Encode(instruction);
	if (strcmp(instruction, "close") == 0)
	{
		printf("\tMini-FSϵͳ���˳���\n");
		return -1;
	}
	else if (strcmp(instruction, "create") == 0)
	{
		scanf("%s", Spacename);		
		SPACE = CreateSpace(Spacename);
		if (SPACE != NULL)
		{
			DoSecondStep(Spacename);
			system("cls");
			Title();
			StartGuide();
		}
		return 2;
	}
	//װ�ؿռ�
	else if (strcmp(instruction, "mount") == 0)
	{
		scanf("%s", Spacename);
		SPACE = MountSpace(Spacename);
		ReadGuideBlock();
		if (SPACE != NULL)
		{
			DoSecondStep(Spacename);
			system("cls");
			Title();
			StartGuide();
		}
		return 3;
	}
	//ˢ��
	else if (strcmp(instruction, "remove") == 0)
	{
		scanf("%s", Spacename);
		DeleteSpace(Spacename);
		return 4;
	}
	else if (strcmp(instruction, "ls") == 0)
	{
		BrowseFiles();
		return 4;
	}
	else if (strcmp(instruction, "clean") == 0)
	{
		system("cls");
		Title();
		StartGuide();
		return 5;
	}
	else
	{
		printf("ָ����Ч�������ԣ�\n");
	}
	return 0;
}