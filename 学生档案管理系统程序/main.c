#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"my_head.h"
#include<string.h>

int main()
{
	//��ѧ����Ϣ�ļ�
	file = fopen("Student_Information.txt", "a+");
	if (file == NULL) {
		printf("�޷����ļ�");
		return -1;
	}

	//ѡ��ִ��ģʽ
	int mode;
	do {

		//�����˵�
		menu();

		//��������ģʽ�Ƿ���Ч
		if (scanf("%d", &mode) != 1) {
			printf("��Ч��ָ����������롣\n\n");
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
				printf("�����������Чָ�����������ָ����\n\n");
				break;
			}
		}
	} while (mode != 6);

	fclose(file);
	printf("������ɣ��������˳���\n");
}