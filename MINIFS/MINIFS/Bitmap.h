#pragma once
#include "define.h"
class Bitmap
{
public:
	Bitmap(byte* content,int length);
	~Bitmap();
	bool GetBlockState(int keyValue);
	void SetBlockState(int keyValue, bool state);
	void printout();

private:
	byte * bitmapSlots;
	int slotCount;
};

