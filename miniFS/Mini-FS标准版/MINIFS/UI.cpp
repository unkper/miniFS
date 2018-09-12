#include"define.h"

void PrintLine()
{
	int index = 80;
	while (index--)
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
	printf("\t4.����\"ls\":����������������е� mini-FS �ռ�\n");
	printf("\t5.����\"close\":�ر� mini-FS ϵͳ\n");
	printf("\t6.����\"clean\":ˢ����Ļ\n");
	printf("\n");
	PrintLine();
}

void FunctionGuide(char *SName)
{
	//GuideManager manager =	GuideManager::GetInstance();
	//manager.files.;
	Title();
	printf("\t�ռ�\"%s\"�Ѱ�װ��ʹ������ָ���������˿ռ䣺\n", SName);
	//printf("Welcome to Mini-FS��operate the system by using following instructions:\n");
	printf("\t1.����\"fmt\":��ʽ����ǰ�ռ�\n");
	printf("\t2.����\"new [name].[ext]\"�½�һ���ļ���Ϊ[name]���ļ���չ��Ϊ[ext]���ļ�\n");
	printf("\t3.����\"ls \" ��ʾ��ǰĿ¼�µ������ļ�\n");
	printf("\t4.����\"cp\":\n");
	printf("\t\t1>����\"cp win [name].[ext] mini\" :\n\t\t��windowsϵͳ����һ���ļ���Ϊ[name]���ļ���չ��Ϊ[ext]���ļ���Mini-FSϵͳ\n");
	printf("\t\t2>����\"cp mini [name].[ext] win\" :\n\t\t��Mini-FSϵͳ����һ���ļ���Ϊ[name]���ļ���չ��Ϊ[ext]���ļ���windowsϵͳ\n");
	printf("\t5.����\"att [name].[ext]\" ��ʾһ���ļ���Ϊ[name]���ļ���չ��Ϊ[ext]���ļ�����ϸ��Ϣ\n");
	printf("\t6.����\"tp [name].txt\"��ʾһ����Ϊ[name]���ı��ļ�������\n");
	//printf("\t6.����\"pst [name].ext\"��һ���ļ���Ϊ[name]���ļ���չ��Ϊ[ext]���ļ��Ӽ����帴�Ƶ���ǰĿ¼��\n");
	//printf("\t8.����\"edit [name]\" �༭һ���ļ���Ϊ[name]���ı��ļ�\n");
	//printf("\t10.����\"cd\" ����Mini-FS�ռ��Ŀ¼\n");
	printf("\t7.����\"ent [name]\"���뵱ǰĿ¼����Ϊ[name]���ļ���\n");
	printf("\t8.����\"back\" ������һ��Ŀ¼\n");
	printf("\t9.����\"help [ins]\" ��ʾ��Ϊ[ins]��ָ�����ϸ����\n");
	printf("\t10.����\"close\" �رոÿռ䣬����Mini-FS��ҳ\n");
	printf("\t11.����\"exit\" �˳�Mini-FSϵͳ\n");
	printf("\t12.����\"clean\"ˢ����Ļ\n");
	printf("\n");
	PrintLine();

}