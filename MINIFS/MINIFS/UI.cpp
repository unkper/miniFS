#include"define.h"

void PrintLine()
{
	int index = 80;
	while(index--)
	{
		printf("*");
	}
	printf("\n");
}

void Title()
{
	printf("\n\t\t\t\tMini-FS �ļ�����ϵͳ\n\n");
	PrintLine();
	printf("\n");
}

void StartGuide()
{
	printf("\t��ӭʹ��Mini-FSϵͳ��ʹ������ָ����������ϵͳ��\n");
	//printf("Welcome to Mini-FS��operate the system by using following instructions:\n");
	printf("\t1.����\"create [name]\":����һ����Ϊ[name]���½� mini-FS �ռ�\n");
	printf("\t2.����\"mount [name]\":����һ����Ϊ[name]�����е� mini-FS �ռ�\n");
	printf("\t3.����\"remove [name]\":�Ӵ�����ɾ��һ����Ϊ[name]�����е� mini-FS �ռ�\n");
	printf("\t4.����\"close\":�ر� mini-FS ϵͳ\n");
	printf("\t5.����\"clean\":ˢ����Ļ\n");
	printf("\n");
	PrintLine();
}

void FunctionGuide(char *SName)
{
	Title();
	printf("\t�ռ�\"%s\"�Ѱ�װ��ʹ������ָ���������˿ռ䣺\n",SName);
	//printf("Welcome to Mini-FS��operate the system by using following instructions:\n");
	printf("\t1.����\"fmt\":��ʽ����ǰ�ռ�\n");
	printf("\t2.����\"new [name].[ext]\"�½�һ���ļ���Ϊ[name]���ļ���չ��Ϊ[ext]���ļ�\n");
	printf("\t3.����\"dr [name]\" ��ʾ��ǰĿ¼�µ��ļ�Ŀ¼\n");
	printf("\t4.����\"cp [name].[ext]\" ����һ���ļ���Ϊ[name]���ļ���չ��Ϊ[ext]���ļ�\n");
	printf("\t5.����\"dl [name].[ext]\" ɾ��һ���ļ���Ϊ[name]���ļ���չ��Ϊ[ext]���ļ�\n");
	printf("\t6.����\"tp [name]\" ��ʾһ���ļ���Ϊ[name]���ı��ļ�\n");
	printf("\t7.����\"help [ins]\" ��ʾ��Ϊ[ins]��ָ�����ϸ����\n");
	printf("\t8.����\"edit [name]\" �༭һ���ļ���Ϊ[name]���ı��ļ�\n");
	printf("\t9.����\"back\" ������һ��Ŀ¼\n");
	printf("\t10.����\"ls\" �����ǰĿ¼�������ļ���\n");
	printf("\t11.����\"cd\" ����Mini-FS�ռ��Ŀ¼\n");
	printf("\t12.����\"ent [name]\"���뵱ǰĿ¼����Ϊ[name]���ļ���\n");
	printf("\t13.����\"close\" �رոÿռ䣬����Mini-FS��ҳ\n");
	printf("\t14.����\"exit\" �˳�Mini-FSϵͳ\n");
	printf("\t15.����\"clean\"ˢ����Ļ\n");
	printf("\n");
	PrintLine();

}