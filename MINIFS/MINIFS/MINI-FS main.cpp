#include"define.h"

char instruction[100];
char Spacename[10];

int ReceiveIns();
FILE *SPACE;

int main()
{
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
	getchar();
	return 0;
}

int ReceiveIns()
{
	printf("Mini-FS>");
	scanf("%s", instruction);
	Encode(instruction);
	if (strcmp(instruction, "close") == 0)
	{
		printf("\tMini-FS系统已退出！\n");
		return -1;
	}
	else if (strcmp(instruction, "create") == 0)
	{
		scanf("%s", Spacename);
		SPACE = CreateSpace(Spacename);
		if (SPACE != NULL)
		{
			DoSecondStep(Spacename);
		}
		return 2;
	}
	//装载空间
	else if (strcmp(instruction, "mount") == 0)
	{
		scanf("%s", Spacename);
		SPACE = MountSpace(Spacename);
		if (SPACE != NULL)
		{
			DoSecondStep(Spacename);
		}
		return 3;
	}
	//刷屏
	else if (strcmp(instruction, "remove") == 0)
	{
		scanf("%s", Spacename);
		DeleteSpace(Spacename);		
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
		printf("指令无效，请重试！\n");
	}
	return 0;
}
