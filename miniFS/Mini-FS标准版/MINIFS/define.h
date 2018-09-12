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

extern char instruction[100];//����
extern int NumofBlocks;//����
//extern UFD PasteInfo;
//extern char PasteContent[BLOCK_SIZE];


typedef struct ufd//һ��64B
{
	char name[9] = { 0 };  // �ļ��� 9B
	char extension[4] = { 0 };  // �ļ���չ�� 4B
	unsigned char attribute = 0;  // �ļ������ֶΣ�ֵΪ0ʱ��ʾ�ļ���ֵΪ1ʱ��ʾ�ļ���,ֵΪ2ʱ��ʾ��,ֵΪ3��ʾ��ʱɾ�� 1B
	unsigned short keyvalue;  // �ļ���ʼ�̿�� 2B
	unsigned long length;  // �ļ����� 8B
	char create_time[15] = { 0 }; //15B
	char edit_time[15] = { 0 }; //15B
								//����ļ����У������ڣ���Index���Ϊ-1
	unsigned short nextFileIndex;  // �¸��ļ����У����������λ��2B
	unsigned short frontFileIndex;  // �ϸ��ļ����У����������λ��2B
	unsigned short fatherFolderIndex;  // ���ļ��е�λ��2B
	unsigned short firstChildFile; //������ļ��У������ŵ����׸����ļ���Index 2B
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

//������������������ļ����ļ���,�����������������𴴽������ļ������ļ��У����ĸ������������Ĵ����ļ���
int m_CreateFile(char* Filename, char* FileExtname, bool isFolder = false, int fatherFolderIndex = 0);
void CloseSpace();
void ViewAllFiles();
void ShowFileAttribute(char * Filename);
void EnterFolder(char* fileName);
void BackToFatherFolder();
void PrintTXT(unsigned short key, int length);

long GetStartFp(char *);

//�����ļ����ļ����ͺ�׺��������һ����ʼ���õ�UFD�����UFD�ڵ�������Length��δ��ֵ
UFD CreateUFD(char* fileName, char* fileExtName);

//�����ļ�����
bool Copy_File();

//��WINDOWS�ļ����Ƶ�mini
bool WinToMini(char *FileName);

//��mini�ļ����Ƶ�WINDOWS
bool MiniToWin(char *FileName);

//�������룬�ܹ���ȡ����׺�����ļ���
bool ScanfFileName(char * Filename, char* FileExtname);

//tp����(f+e)
bool ShowTXTFile(char *Filename);

//ɾ�����ǵ�ǰ�ļ����µ��ļ�Filename
bool m_DeleteFile(char *Filename);

//�༭���ǵ�ǰ�ļ����µ��ļ�Filename
bool EditFile(char *Filename);

//����Ҫ��ŵ��ļ��Ĵ�Сsize������һ��int������freeBlocks����������Ҫ�������ݿ�Ŀ��
bool GetFreeBlocks(int size, int* freeBlocks);

//����ĳ��ŵ��ļ��������ݿ�keyvalue������һ��int������freeBlocks�����������ѷ������ݿ�Ŀ��
bool GetFreeBlocks(int keyvalue, int* freeBlocks);

//����һ��unsigned char ���飬��������������д�����ݿ�
bool WriteContentBlocks(unsigned char * content,int size);

//��ʾ��ǰ�ļ�����Ŀ¼��״�ṹ
bool ShowTree();

//�ָ��ļ�Filename(f+e
bool RestoreFile(char *Filename);

//��ʾָ���ļ�ռ���̿��
bool ShowMap(char *Filename);

//�Ż����̿ռ�(ѡ���⣬�߿�+20��
void Optimize();

//�����ļ������ļ���չ�������ص�ǰ�ļ����ҵ����ļ�������
unsigned short FindFile(char* fileName, char* fileExtName);
bool BlockWriter(short keyValue, short nextkeyValue, unsigned char *content, int size);
short BlockReader(short keyValue, int size, unsigned char* temp);
struct tm *GetTime();
char* FormatTime();

FILE *CreateSpace(char *);
FILE *MountSpace(char *);


/////////////////������淶////////////////////

//ֻ����һ��8KB��Bitmap����¼����ʹ�õ����ݿ��



/////////////////���ݿ�淶////////////////////

//���ȴ���һ��short int����ʾ��һ�����ݿ������
//���������ݿ����ݣ���16KB-2