#pragma once

/* �ļ����ƿ� */
typedef struct UFD
{
	char name[9];  // �ļ���
	char extension[4];  // �ļ���չ��
	//unsigned char attribute;  // �ļ������ֶΣ�ֵΪ0ʱ��ʾ�ļ���ֵΪ1ʱ��ʾ�ļ���
	unsigned short keyvalue;  // �ļ���ʼ�̿��
	unsigned long length;  // �ļ�����
	UFD *next;//��һ�����
	//char free;  // ��ʾĿ¼���Ƿ�Ϊ�գ���ֵΪ0����ʾ�գ�ֵΪ1����ʾ�ѷ���
	char create_time[15];
	char edit_time[15];
}ufd;