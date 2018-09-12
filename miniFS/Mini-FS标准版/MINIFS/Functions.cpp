#include"define.h"
#include"GuideManager.h"

int WriteFile(FILE *fp,int);
void WriteContents(char *, int, int);

int NumOfChar;//别用

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
	//这个-1在unsigned short为正值，
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
		printf("此目录下无此文件，请重新检查！\n");
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
	//文件名+扩展名
	fprintf(SPACE, "%13s", Filename);
	//printf("%13s", Filename);
	// 文件起始盘块号
	fprintf(SPACE, "%2d", numofblocks);
	//printf( "%2d", numofblocks);
	// 文件长度
	fprintf(SPACE, "%8d", Length);
	//printf("%8d", Length);
	//创建时间+编辑时间
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

UFD CreateUFD(char* fileName, char* fileExtName)//这个UFD的所有索引都没赋过值
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

//返回的是创建好的UFD在数组里的索引
int m_CreateFile(char* Filename, char* FileExtname, bool isFolder, int fatherFolderIndex)
{
	if (strlen(Filename) > 8)
	{
		printf("\t文件名长度必须小于9\n");
		return 0;
	}
	if (strlen(FileExtname) > 3)
	{
		printf("\t文件后缀名长度必须小于4\n");
		return 0;
	}
	int flag = FindFile(Filename, FileExtname);
	if (flag != NULLFILE)
	{
		printf("\t存在同名文件\n");
		return 0;
	}
	GuideManager& manager = GuideManager::GetInstance();
	unsigned short Index = manager.fileCount++;
	UFD newFile = CreateUFD(Filename, FileExtname);
	UFD fatherFolder = manager.allFiles[fatherFolderIndex];
	if (fatherFolder.attribute != 1)
	{
		printf("\t父文件夹不是文件夹类型\n");
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
		//在链表头插入
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

//要查找文件夹，扩展名为fld,返回文件名与扩展名完全一样的
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
		printf("\t没有输入文件后缀名，请重新输入！\n");
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
			printf("%s.%s 信息：\n", file.name, file.extension);
			printf("\t文件大小：%ld\n", file.length);
			strcpy(createTime, file.create_time);
			strcpy(editTime, file.edit_time);
			printf("\t创建时间：  ");
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


			printf("\t最后一次编辑时间：  ");
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
		printf("\t文件不存在！！\n");
}

void ShowHelpInfo()
{
	char cmdname[20];//命令名称
	scanf("%s", cmdname);

	if (cmdname == "\0")
	{
		printf("有关某个命令的详细信息，请键入 help 命令名\n\n");
		printf("cd		变更到指定目录下\n");
		printf("create		创建一个新的文件\n");
		printf("cp		将一个文件复制到另一个位置\n");
		printf("dl		删除至少一个文件\n");
		printf("dr		显示当前目录中的文件和文件夹\n");
		printf("tp		以普通文本形式显示一个文件的内容\n");
		printf("more		以分页文本形式显示一个文件的内容\n");
		printf("fmt		格式化磁盘\n");
		printf("att		显示一个文件的具体属性\n");
		printf("rc		恢复一个已删除文件\n");
		printf("edit		编辑文件功能\n");
		printf("close		关闭miniUFS系统\n");
		printf("\n");
	}
	else
	{
		if (strcmp(cmdname, "create") == 0)
		{
			printf("创建一个新的文件夹\n");
			printf("\n");
			printf("create [path] [dirname]\n\n");
			printf("path		绝对路径或相对路径均可,用于指明需要删除文件夹的具体位置\n");
			printf("dirname		创建的文件夹名称\n");
			printf("如果不输入则系统会使用默认文件夹名创建文件夹。\n\n");
			printf("在当前目录下创建一个新的文件夹\n");
			printf("NEWDIR 命令将空格视为分隔符，所以目录中请不要包含空格。\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "fmt") == 0)
		{
			printf("格式化磁盘\n");
			printf("\n");
			printf("fmt [-option]\n\n");
			printf("可用 option:\n");
			printf("	-d : 低级格式化\n");
			printf("	-n : 普通格式化\n");
			printf("	如果不写选项则默认使用 -n 选项。\n\n");
			printf("执行成功后，将会格式化整个磁盘空间，清空里面的所有文件\n");
			printf("系统文件等将被恢复最初状态\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "dr") == 0)
		{
			printf("显示当前目录中的文件和文件夹\n");
			printf("\n");
			printf("dr [filename]\n\n");
			printf("filename 指定要列出的文件名，支持正则表达式。\n\n");
			printf("如果不填，执行成功后将在屏幕中列出当前目录下的所有文件和文件夹\n\n");
			printf("文件和文件夹将以文件名字母顺序排序。\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "cp") == 0)
		{
			printf("将一个文件复制到另一个位置\n");
			printf("\n");
			printf("cp [path1]filename1  [path2]filename2\n\n");
			printf("path1 path2 绝对路径或相对路径均可,用于指明文件的具体位置 \n");
			printf("如不填写，默认为当前目录下\n\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "dl") == 0)
		{
			printf("删除至少一个文件夹\n");
			printf("\n");
			printf("dl [path] dirname\n\n");
			printf("path		绝对路径或相对路径均可,用于指明需要删除文件夹的具体位置\n");
			printf("dirname		需要删除的文件夹名称，支持使用通配符。\n\n");
			printf("将会把文件夹以及里面的子文件夹和文件一并删除\n");
			printf("DELDIR 命令将空格视为分隔符，所以目录中请不要包含空格。\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "att") == 0)
		{
			printf("显示一个文件夹的具体属性\n");
			printf("\n");
			printf("att [path]dirname\n\n");
			printf("path  绝对路径或相对路径均可,用于指明文件夹的具体位置 \n\n");
			printf("如不填写，默认为当前目录下\n");
			printf("执行成功后将会显示文件夹的属性，如可读可写等\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "edit") == 0)
		{
			printf("编辑文件功能\n");
			printf("\n");
			printf("edit [-option] [path]filename \n\n");
			printf("可用 option：\n\n");
			printf("	-w : 以覆写形式打开文件。\n");
			printf("	-a : 以追加形式打开文件。\n");
			printf("	-vim : 使用Vim打开文件。\n");
			printf("	如果不添加选项则默认使用 -a 选项。\n\n");
			printf("path  绝对路径或相对路径均可,用于指明文件的具体位置 \n");
			printf("如不填写，默认为当前目录下\n\n");
			printf("filename 需要编辑的文件名称\n");
			printf("执行成功后，可以键入想写入文件中的内容\n\n");
			printf("使用 -w 和 -a 选项时需要结束编辑按CTRL + C\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "tp") == 0)
		{
			printf("以普通文本形式显示一个文件的内容\n");
			printf("\n");
			printf("tp [path]filename\n\n");
			printf("path  绝对路径或相对路径均可,用于指明文件的具体位置 \n");
			printf("如不填写，默认为当前目录下\n\n");
			printf("filename 需要显示的文件名称\n\n");
			printf("执行成功后将会把指定文件中的内容输出到屏幕上\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "back") == 0)
		{
			printf("显示一个文件夹的具体属性\n");
			printf("\n");
			printf("att [path]dirname\n\n");
			printf("path  绝对路径或相对路径均可,用于指明文件夹的具体位置 \n\n");
			printf("如不填写，默认为当前目录下\n");
			printf("执行成功后将会显示文件夹的属性，如可读可写等\n");
			printf("\n");
			printf("\n");
		}
		else if (strcmp(cmdname, "close") == 0)
		{
			printf("关闭miniUFS系统\n");
			printf("\n");
			printf("close\n");
			printf("执行成功后，将会关闭miniUFS系统\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
		}
		else
		{
			printf("找不到对应命令。\n");
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
		printf("\t没有输入文件后缀名，请重新输入！\n");
		return;
	}
	strcpy(filename, strtok(fileName, "."));
	strcpy(extenname, strtok(NULL, "."));
	if (strcmp(extenname, "fld") != 0)
		printf("\t输入不是文件夹，请重新输入！\n");
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
			printf("文件夹%s.%s不存在！！\n", filename, extenname);
	}
}

void BackToFatherFolder()
{
	GuideManager& manager = GuideManager::GetInstance();
	if (manager.nowFolderIndex != 0)
		manager.nowFolderIndex = manager.allFiles[manager.nowFolderIndex].fatherFolderIndex;
	else printf("已经在根文件夹下！！");
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