#pragma once
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<Windows.h>
#include<time.h>
#include<algorithm>
#include<iostream>

using namespace std;


//variables

extern char instruction[100];


//functions
void StartGuide();
void Title();
void FunctionGuide(char *SName);
void DoSecondStep(char *);
void Encode(char *);
void DeleteSpace(char *);

FILE *CreateSpace(char *);
FILE *MountSpace(char *);
