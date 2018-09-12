#pragma once

/* 文件控制块 */
typedef struct UFD
{
	char name[9];  // 文件名
	char extension[4];  // 文件扩展名
	//unsigned char attribute;  // 文件属性字段，值为0时表示文件，值为1时表示文件夹
	unsigned short keyvalue;  // 文件起始盘块号
	unsigned long length;  // 文件长度
	UFD *next;//下一个结点
	//char free;  // 表示目录项是否为空，若值为0，表示空，值为1，表示已分配
	char create_time[15];
	char edit_time[15];
}ufd;