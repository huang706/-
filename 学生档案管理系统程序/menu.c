#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"my_head.h"

//菜单函数
void menu()
{
	printf("================== 学生信息管理系统 ==================\n");
	printf("1.添加学生信息\n");
	printf("2.查看全部学生信息\n");
	printf("3.按学号或姓名查找某学生(可修改或删除其信息）\n");
	printf("4.按学号排序\n");
	printf("5.清除所有信息\n");
	printf("6.退出程序\n");
	printf("======================================================\n");
	printf("请输入您的指令编号：\n");
}