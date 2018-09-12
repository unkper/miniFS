#include "Bitmap.h"


Bitmap::Bitmap(byte * content, int ByteLen)
{
	bitmapSlots = (byte*)malloc(sizeof(byte)*ByteLen);
	memset(bitmapSlots, 0, sizeof(bitmapSlots));
	for (int i = 0; i < ByteLen; i++)
	{
		bitmapSlots[i] |= content[i];
	}
	this->slotCount = ByteLen * 8;
}

Bitmap::~Bitmap()
{
	free(bitmapSlots);
}

//���keyValueָ�������ݿ�ı�ţ���һ�����ݿ��keyValueΪ0,�䷵�ظÿ��Ƿ�ռ��
bool Bitmap::GetBlockState(int keyValue)
{
	if (keyValue > this->slotCount)
	{
		printf("your keyValue big than bitmap length");
		exit(-1);
	}
	//��������Ǹ�λ
	int indexInArray = keyValue / 8;
	int indexInChar = keyValue % 8;
	byte b = this->bitmapSlots[indexInArray];
	b = b >> indexInChar;
	b = b & 1;
	if (b == 1)
		return true;
	else return false;
}

void Bitmap::SetBlockState(int keyValue, bool state)
{
	if (keyValue > this->slotCount)
	{
		printf("your keyValue big than bitmap length");
		exit(-1);
	}
	//��������Ǹ�λ
	int indexInArray = keyValue / 8;
	int indexInChar = keyValue % 8;
	if (state)
	{
		bitmapSlots[indexInArray] |= (1 << indexInChar);
	}	
	else
	{
		bitmapSlots[indexInArray] &= ~(1 << indexInChar);
	}
	return;
}

int Bitmap::GetByteLength()
{
	return this->slotCount/8;
}

byte * Bitmap::Deserialize()
{
	return this->bitmapSlots;
}

void Bitmap::printout()
{
	int i = 0;
	for (i = 0; i < this->slotCount / 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			byte b = this->bitmapSlots[i];
			b = b >> j;
			b &= 1;
			printf("%d", b);
		}
		printf("  ");
	}
	printf("\n");
}
