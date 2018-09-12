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
	printf("\n\t\t\t\tMini-FS 文件管理系统\n\n");
	PrintLine();
	printf("\n");
}

void StartGuide()
{
	printf("\t欢迎使用Mini-FS系统，使用以下指令来操作此系统：\n");
	//printf("Welcome to Mini-FS，operate the system by using following instructions:\n");
	printf("\t1.输入\"create [name]\":建立一个名为[name]的新建 mini-FS 空间\n");
	printf("\t2.输入\"mount [name]\":加载一个名为[name]的已有的 mini-FS 空间\n");
	printf("\t3.输入\"remove [name]\":从磁盘中删除一个名为[name]的已有的 mini-FS 空间\n");
	printf("\t4.输入\"ls\":浏览磁盘中所有已有的 mini-FS 空间\n");
	printf("\t5.输入\"close\":关闭 mini-FS 系统\n");
	printf("\t6.输入\"clean\":刷新屏幕\n");
	printf("\n");
	PrintLine();
}

void FunctionGuide(char *SName)
{
	//GuideManager manager =	GuideManager::GetInstance();
	//manager.files.;
	Title();
	printf("\t空间\"%s\"已安装，使用以下指令来操作此空间：\n", SName);
	//printf("Welcome to Mini-FS，operate the system by using following instructions:\n");
	printf("\t1.输入\"fmt\":格式化当前空间\n");
	printf("\t2.输入\"new [name].[ext]\"新建一个文件名为[name]，文件扩展名为[ext]的文件\n");
	printf("\t3.输入\"ls \" 显示当前目录下的所有文件\n");
	printf("\t4.输入\"cp\":\n");
	printf("\t\t1>输入\"cp win [name].[ext] mini\" :\n\t\t从windows系统复制一个文件名为[name]，文件扩展名为[ext]的文件到Mini-FS系统\n");
	printf("\t\t2>输入\"cp mini [name].[ext] win\" :\n\t\t从Mini-FS系统复制一个文件名为[name]，文件扩展名为[ext]的文件到windows系统\n");
	printf("\t5.输入\"att [name].[ext]\" 显示一个文件名为[name]，文件扩展名为[ext]的文件的详细信息\n");
	printf("\t6.输入\"tp [name].txt\"显示一个名为[name]的文本文件的内容\n");
	//printf("\t6.输入\"pst [name].ext\"将一个文件名为[name]，文件扩展名为[ext]的文件从剪贴板复制到当前目录下\n");
	//printf("\t8.输入\"edit [name]\" 编辑一个文件名为[name]的文本文件\n");
	//printf("\t10.输入\"cd\" 返回Mini-FS空间根目录\n");
	printf("\t7.输入\"ent [name]\"进入当前目录下名为[name]的文件夹\n");
	printf("\t8.输入\"back\" 返回上一级目录\n");
	printf("\t9.输入\"help [ins]\" 显示名为[ins]的指令的详细解释\n");
	printf("\t10.输入\"close\" 关闭该空间，返回Mini-FS首页\n");
	printf("\t11.输入\"exit\" 退出Mini-FS系统\n");
	printf("\t12.输入\"clean\"刷新屏幕\n");
	printf("\n");
	PrintLine();

}