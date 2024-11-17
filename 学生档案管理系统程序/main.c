#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"my_head.h"
#include<string.h>

int main()
{
	//打开学生信息文件
	file = fopen("Student_Information.txt", "a+");
	if (file == NULL) {
		printf("无法打开文件");
		return -1;
	}

	//选择执行模式
	int mode;
	do {

		//跳出菜单
		menu();

		//检验输入模式是否有效
		if (scanf("%d", &mode) != 1) {
			printf("无效的指令，请重新输入。\n\n");
			while (getchar() != '\n');
			continue;
		}

		if (mode != 6) {
			switch (mode)
			{
			case 1:
				addStudent(file);
				break;
			case 2:
				show(file);
				break;
			case 3:
				search(file);
				break;
			case 4:
				sort(file);
				break;
			case 5:
				removeAll(file);
				break;
			default:
				printf("您输入的是无效指令，请重新输入指令编号\n\n");
				break;
			}
		}
	} while (mode != 6);

	fclose(file);
	printf("操作完成，程序已退出。\n");
}