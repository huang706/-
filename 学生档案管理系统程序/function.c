#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"my_head.h"
#include<string.h>

/*typedef struct {
	char ID[20];
	char name[15];
	int age;
	char sex[5];
	char Class[20];
}student;*/

//���ѧ��
void addStudent(FILE* file)
{
	//�û�������ѧ����Ϣ
	student new;
	printf("��������ѧ������Ϣ��\n");
	printf("ѧ�ţ�");
	scanf("%s", new.ID);
	printf("������");
	scanf("%s", new.name);
	printf("���䣺");
	scanf("%d", &new.age);

	do {
		printf("�Ա�");
		scanf("%s", new.sex);
		if (strcmp(new.sex, "��") != 0 && strcmp(new.sex, "Ů") != 0) {
			printf("�Ա�����������������롣\n");
		}
	} while (strcmp(new.sex, "��") != 0 && strcmp(new.sex, "Ů") != 0);

	printf("�༶����������2402����");
	scanf("%s", new.Class);

	if (fprintf(file, "%s %s %d %s %s\n", new.ID, new.name, new.age, new.sex, new.Class) < 0) {
		printf("����ʧ��!\n\n");
	}
	else {
		fflush(file);
		printf("����ɹ�!\n\n");
	}
}



//�������ѧ����Ϣ
void show(FILE* file)
{
	//��file*�Ƶ��ļ���ͷ
	fseek(file, 0, SEEK_SET);

	//�����Ϣ
	char buffer[256];
	int haveInformation = 0;
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		printf("%s", buffer);
		haveInformation = 1;
	}
	if (haveInformation) {
		printf("������!\n\n");
	}
	else {
		printf("����ѧ����Ϣ!\n\n");
	}
}



//��ѧ�Ż���������ĳ��ѧ��
void search(FILE* file)
{
	//��file*�Ƶ��ļ���ͷ
	fseek(file, 0, SEEK_SET);

	//������Ϣ
	printf("������������ѧ�ţ�");
	char target[256];
	scanf("%s", target);

	//����(���޸Ļ�ɾ����
	char buffer[256];
	int isFound = 0;
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		char temp[100];
		strcpy(temp, buffer);
		char* token = strtok(buffer, " \n");
		while (token != NULL) {
			if (strcmp(target, token) == 0) {
				printf("��ѧ���ľ�����Ϣ�ǣ�%s\n", temp);
				isFound = 1;
				char choice;
				printf("�Ƿ��������Ϣ��(y/n):");
				scanf(" %c", &choice);
				if (choice == 'y') {
					change(file, temp);
				}
				else {
					printf("�Ƿ�ɾ������Ϣ��(y/n):");
					scanf(" %c", &choice);
					if (choice == 'y') {
						delete(file, temp);
					}
				}
				goto end;
			}
			token = strtok(NULL, " \n");
		}
	}
end:
	if (!isFound) {
		printf("δ�ҵ���ѧ����Ϣ!\n");
	}
	printf("\n");
}



//�������ѧ����Ϣ
void removeAll(FILE* file)
{
	fclose(file);
	if (remove("Student_Information.txt") == 0) {
		printf("ɾ���ɹ���\n\n");
		file = fopen("Student_Information.txt", "a+");
	}
	else {
		printf("ɾ��ʧ��!\n\n");
		file = fopen("Student_Information.txt", "a+");
	}
}



//�޸�ѧ����Ϣ
void change(FILE* file, char target[])
{
	//��file*�Ƶ��ļ���ͷ
	fseek(file, 0, SEEK_SET);

	char buffer[256];
	FILE* change_student = fopen("change_student.txt", "w+");

	//��Ŀ��ѧ��
	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		if (strcmp(target, buffer) != 0) {
			fprintf(change_student, "%s", buffer);
		}
		else {

			//������ѧ������Ϣ
			student new;
			printf("��������ѧ������Ϣ��\n");
			printf("ѧ�ţ�");
			scanf("%s", new.ID);
			printf("������");
			scanf("%s", new.name);
			printf("���䣺");
			scanf("%d", &new.age);
			printf("�Ա�(Ů/��)��");
			scanf("%s", new.sex);
			printf("�༶����������2402����");
			scanf("%s", new.Class);
			fprintf(change_student, "%s %s %d %s %s\n", new.ID, new.name, new.age, new.sex, new.Class);
		}
	}
	fflush(change_student);

	//������ɣ��ر��ļ�
	fclose(file);
	fclose(change_student);

	//�滻�ļ�
	if (remove("Student_Information.txt") != 0 || rename("change_student.txt", "Student_Information.txt") != 0) {
		printf("������Ϣʧ��!\n");
	}
	else {
		printf("������Ϣ�ɹ���\n");
		file = fopen("Student_Information.txt", "a+");
	}
}



//ɾ��ĳѧ����Ϣ
void delete(FILE* file, char target[])
{
	//��ָ���Ƶ���ͷ
	fseek(file, 0, SEEK_SET);

	char buffer[100];
	FILE* delete_student = fopen("delete_student.txt", "w+");

	//��Ŀ��ѧ��
	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		if (strcmp(target, buffer) != 0) {
			fprintf(delete_student, "%s", buffer);
		}
	}
	fflush(delete_student);

	//������ɣ��ر��ļ�
	fclose(file);
	fclose(delete_student);

	//�滻�ļ�
	if (remove("Student_Information.txt") != 0 || rename("delete_student.txt", "Student_Information.txt") != 0) {
		printf("ɾ��ʧ��!\n");
	}
	else {
		printf("ɾ���ɹ���\n");
		file = fopen("Student_Information.txt", "a+");
	}
}



//��ѧ������
void sort(FILE* file)
{
	//��ָ���Ƶ���ͷ
	fseek(file, 0, SEEK_SET);

	//���ļ�ת��Ϊ������ʽ
	student students[100];
	int i = 0;
	while (fscanf(file, "%s %s %d %s %s", students[i].ID, students[i].name, &students[i].age, students[i].sex, students[i].Class) == 5)
	{
		i++;
	}

	//��������ʽ
	int type;
	do {
		printf("��ѡ������ʽ��\n");
		printf("����1\n");
		printf("����2\n");
		scanf("%d", &type);
		if ((type != 1) && (type != 2)) {
			printf("��Ч������ʽ�����������롣\n\n");
		}
	} while ((type != 1) && (type != 2));

	//��������
	if (type == 1) {
		qsort(students, i, sizeof(student), compareAscending); // ����
	}
	else 
	{
		qsort(students, i, sizeof(student), compareDescending); // ����
	}

	//���ź��������ת��Ϊ���ļ�
	FILE* sort_student = fopen("sort_student.txt", "w+");
	for (int w = 0; w < i; w++) {
		fprintf(sort_student, "%s %s %d %s %s\n", students[w].ID, students[w].name, students[w].age, students[w].sex, students[w].Class);
	}
	fflush(sort_student);

	//������Ϲص��ļ�
	fclose(file);
	fclose(sort_student);

	//�滻�ļ�
	if (remove("Student_Information.txt") != 0 || rename("sort_student.txt", "Student_Information.txt") != 0) {
		printf("����ʧ��!\n\n");
	}
	else {
		printf("����ɹ���\n\n");
		file = fopen("Student_Information.txt", "a+");
	}
}



//sort�ıȽϺ���
int compareAscending(void* a, void* b)
{
	student* x = (student*)a;
	student* y = (student*)b;
	return strcmp(x->ID, y->ID);
}
int compareDescending(void* a, void* b)
{
	student* x = (student*)a;
	student* y = (student*)b;
	return strcmp(y->ID, x->ID);
}