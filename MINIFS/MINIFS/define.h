#pragma once
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<Windows.h>
#include<time.h>
#include<algorithm>
#include<iostream>
#include "Bitmap.h"
#include "global.h"
#include <list>
#include <time.h>
using namespace std;


//variables

extern char instruction[100];

#define BLOCK_SIZE 1<<14
#define GUIDEBLOCKIDX 0
#define DIRLOCKIDX 1
#define CONTENTBLOCKIDX 32
#define CONTENTBLOCKCOUNT 8*8*1024

//functions
void StartGuide();
void Title();
void FunctionGuide(char *SName);
void DoSecondStep(char *);
void Encode(char *);
void DeleteSpace(char *);

void ReadGuideBlock(FILE* header);
void WriteGuideBlock(FILE* header);
void InitGuideBlock(FILE* header);

void m_CreateFile(char* Filename, char* FileExtname);
void CloseSpace();

FILE *CreateSpace(char *);
FILE *MountSpace(char *);
