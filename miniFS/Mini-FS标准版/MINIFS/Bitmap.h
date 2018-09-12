#pragma once
#include "define.h"
class Bitmap
{
public:
	Bitmap(byte* content, int length);
	~Bitmap();
	bool GetBlockState(int keyValue);
	void SetBlockState(int keyValue, bool state);
	int GetByteLength();
	byte* Deserialize();
	void printout();

private:
	byte * bitmapSlots;
	int slotCount;
};

