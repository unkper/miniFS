#pragma once
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<Windows.h>
#include<time.h>
#include<algorithm>
#include<iostream>
#include "Bitmap.h"

using namespace std;


//variables

extern char instruction[100];

#define BLOCK_SIZE 1<<16

//functions
void StartGuide();
void Title();
void FunctionGuide(char *SName);
void DoSecondStep(char *);
void Encode(char *);
void DeleteSpace(char *);
byte* BlockReader(int keyValue,int size);
bool BlockWriter(int keyValue, byte* content, int size);

FILE *CreateSpace(char *);
FILE *MountSpace(char *);
