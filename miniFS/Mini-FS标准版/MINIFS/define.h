#pragma once
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<Windows.h>
#include<time.h>
#include<algorithm>
#include<iostream>
#include "Bitmap.h"

#define BLOCK_SIZE 16384
#define GUIDEBLOCKIDX 0
#define DIRLOCKIDX 1
#define CONTENTBLOCKIDX 32
#define CONTENTBLOCKCOUNT 65504
#define MAXFILESNUMBER 16000
#define NULLFILE 65535

#define CSTART 16384
#define FSTART 524288

using namespace std;
//variables

extern char instruction[100];//别用
extern int NumofBlocks;//别用
//extern UFD PasteInfo;
//extern char PasteContent[BLOCK_SIZE];


typedef struct ufd//一共64B
{
	char name[9] = { 0 };  // 文件名 9B
	char extension[4] = { 0 };  // 文件扩展名 4B
	unsigned char attribute = 0;  // 文件属性字段，值为0时表示文件，值为1时表示文件夹,值为2时表示空,值为3表示暂时删除 1B
	unsigned short keyvalue;  // 文件起始盘块号 2B
	unsigned long length;  // 文件长度 8B
	char create_time[15] = { 0 }; //15B
	char edit_time[15] = { 0 }; //15B
								//如果文件（夹）不存在，将Index标记为-1
	unsigned short nextFileIndex;  // 下个文件（夹）在数组里的位置2B
	unsigned short frontFileIndex;  // 上个文件（夹）在数组里的位置2B
	unsigned short fatherFolderIndex;  // 父文件夹的位置2B
	unsigned short firstChildFile; //如果是文件夹，这里存放的是首个子文件的Index 2B
}UFD;

//extern FILE *HeadfpofContents;
//extern FILE *HeadfpofFiles;
extern FILE *SPACE;

//Functions
void StartGuide();
void Title();
void FunctionGuide(char *SName);
void DoSecondStep(char *);
void Encode(char *);
void DeleteSpace(char *);
void BrowseFiles();
void ReadGuideBlock();
void WriteGuideBlock();
void InitGuideBlock();

//利用这个函数创建空文件与文件夹,第三个参数用于区别创建的是文件还是文件夹，第四个参数用于在哪创建文件夹
int m_CreateFile(char* Filename, char* FileExtname, bool isFolder = false, int fatherFolderIndex = 0);
void CloseSpace();
void ViewAllFiles();
void ShowFileAttribute(char * Filename);
void EnterFolder(char* fileName);
void BackToFatherFolder();
void PrintTXT(unsigned short key, int length);

long GetStartFp(char *);

//填入文件的文件名和后缀名，返回一个初始化好的UFD，这个UFD内的索引和Length均未赋值
UFD CreateUFD(char* fileName, char* fileExtName);

//复制文件函数
bool Copy_File();

//将WINDOWS文件复制到mini
bool WinToMini(char *FileName);

//将mini文件复制到WINDOWS
bool MiniToWin(char *FileName);

//处理输入，能够提取出后缀名和文件名
bool ScanfFileName(char * Filename, char* FileExtname);

//tp功能(f+e)
bool ShowTXTFile(char *Filename);

//删除的是当前文件夹下的文件Filename
bool m_DeleteFile(char *Filename);

//编辑的是当前文件夹下的文件Filename
bool EditFile(char *Filename);

//输入要存放的文件的大小size，返回一个int型数组freeBlocks，里面存的是要放入内容块的块号
bool GetFreeBlocks(int size, int* freeBlocks);

//输入某存放的文件的首内容块keyvalue，返回一个int型数组freeBlocks，里面存的是已放入内容块的块号
bool GetFreeBlocks(int keyvalue, int* freeBlocks);

//填入一个unsigned char 数组，函数将数组内容写入内容块
bool WriteContentBlocks(unsigned char * content,int size);

//显示当前文件夹下目录树状结构
bool ShowTree();

//恢复文件Filename(f+e
bool RestoreFile(char *Filename);

//显示指定文件占用盘块号
bool ShowMap(char *Filename);

//优化磁盘空间(选做题，高考+20分
void Optimize();

//填入文件名和文件扩展名，返回当前文件下找到的文件的索引
unsigned short FindFile(char* fileName, char* fileExtName);
bool BlockWriter(short keyValue, short nextkeyValue, unsigned char *content, int size);
short BlockReader(short keyValue, int size, unsigned char* temp);
struct tm *GetTime();
char* FormatTime();

FILE *CreateSpace(char *);
FILE *MountSpace(char *);


/////////////////引导块规范////////////////////

//只存入一个8KB的Bitmap，记录的是使用的内容块号



/////////////////内容块规范////////////////////

//首先存入一个short int，表示下一个内容块的索引
//下面存放内容块内容，共16KB-2