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

//添加学生
void addStudent(FILE* file)
{
	//用户输入新学生信息
	student new;
	printf("请输入新学生的信息：\n");
	printf("学号：");
	scanf("%s", new.ID);
	printf("姓名：");
	scanf("%s", new.name);
	printf("年龄：");
	scanf("%d", &new.age);

	do {
		printf("性别：");
		scanf("%s", new.sex);
		if (strcmp(new.sex, "男") != 0 && strcmp(new.sex, "女") != 0) {
			printf("性别输入错误，请重新输入。\n");
		}
	} while (strcmp(new.sex, "男") != 0 && strcmp(new.sex, "女") != 0);

	printf("班级（例：数试2402）：");
	scanf("%s", new.Class);

	if (fprintf(file, "%s %s %d %s %s\n", new.ID, new.name, new.age, new.sex, new.Class) < 0) {
		printf("保存失败!\n\n");
	}
	else {
		fflush(file);
		printf("保存成功!\n\n");
	}
}



//输出所有学生信息
void show(FILE* file)
{
	//将file*移到文件开头
	fseek(file, 0, SEEK_SET);

	//输出信息
	char buffer[256];
	int haveInformation = 0;
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		printf("%s", buffer);
		haveInformation = 1;
	}
	if (haveInformation) {
		printf("输出完成!\n\n");
	}
	else {
		printf("暂无学生信息!\n\n");
	}
}



//按学号或姓名查找某个学生
void search(FILE* file)
{
	//将file*移到文件开头
	fseek(file, 0, SEEK_SET);

	//输入信息
	printf("请输入姓名或学号：");
	char target[256];
	scanf("%s", target);

	//查找(可修改或删除）
	char buffer[256];
	int isFound = 0;
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		char temp[100];
		strcpy(temp, buffer);
		char* token = strtok(buffer, " \n");
		while (token != NULL) {
			if (strcmp(target, token) == 0) {
				printf("该学生的具体信息是：%s\n", temp);
				isFound = 1;
				char choice;
				printf("是否更改其信息？(y/n):");
				scanf(" %c", &choice);
				if (choice == 'y') {
					change(file, temp);
				}
				else {
					printf("是否删除其信息？(y/n):");
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
		printf("未找到该学生信息!\n");
	}
	printf("\n");
}



//清除所有学生信息
void removeAll(FILE* file)
{
	fclose(file);
	if (remove("Student_Information.txt") == 0) {
		printf("删除成功！\n\n");
		file = fopen("Student_Information.txt", "a+");
	}
	else {
		printf("删除失败!\n\n");
		file = fopen("Student_Information.txt", "a+");
	}
}



//修改学生信息
void change(FILE* file, char target[])
{
	//将file*移到文件开头
	fseek(file, 0, SEEK_SET);

	char buffer[256];
	FILE* change_student = fopen("change_student.txt", "w+");

	//找目标学生
	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		if (strcmp(target, buffer) != 0) {
			fprintf(change_student, "%s", buffer);
		}
		else {

			//输入新学生的信息
			student new;
			printf("请输入新学生的信息：\n");
			printf("学号：");
			scanf("%s", new.ID);
			printf("姓名：");
			scanf("%s", new.name);
			printf("年龄：");
			scanf("%d", &new.age);
			printf("性别(女/男)：");
			scanf("%s", new.sex);
			printf("班级（例：数试2402）：");
			scanf("%s", new.Class);
			fprintf(change_student, "%s %s %d %s %s\n", new.ID, new.name, new.age, new.sex, new.Class);
		}
	}
	fflush(change_student);

	//操作完成，关闭文件
	fclose(file);
	fclose(change_student);

	//替换文件
	if (remove("Student_Information.txt") != 0 || rename("change_student.txt", "Student_Information.txt") != 0) {
		printf("更新信息失败!\n");
	}
	else {
		printf("更新信息成功！\n");
		file = fopen("Student_Information.txt", "a+");
	}
}



//删除某学生信息
void delete(FILE* file, char target[])
{
	//将指针移到开头
	fseek(file, 0, SEEK_SET);

	char buffer[100];
	FILE* delete_student = fopen("delete_student.txt", "w+");

	//找目标学生
	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		if (strcmp(target, buffer) != 0) {
			fprintf(delete_student, "%s", buffer);
		}
	}
	fflush(delete_student);

	//操作完成，关闭文件
	fclose(file);
	fclose(delete_student);

	//替换文件
	if (remove("Student_Information.txt") != 0 || rename("delete_student.txt", "Student_Information.txt") != 0) {
		printf("删除失败!\n");
	}
	else {
		printf("删除成功！\n");
		file = fopen("Student_Information.txt", "a+");
	}
}



//按学号排序
void sort(FILE* file)
{
	//将指针移到开头
	fseek(file, 0, SEEK_SET);

	//将文件转换为数组形式
	student students[100];
	int i = 0;
	while (fscanf(file, "%s %s %d %s %s", students[i].ID, students[i].name, &students[i].age, students[i].sex, students[i].Class) == 5)
	{
		i++;
	}

	//输入排序方式
	int type;
	do {
		printf("请选择排序方式：\n");
		printf("升序：1\n");
		printf("降序：2\n");
		scanf("%d", &type);
		if ((type != 1) && (type != 2)) {
			printf("无效的排序方式，请重新输入。\n\n");
		}
	} while ((type != 1) && (type != 2));

	//进行排序
	if (type == 1) {
		qsort(students, i, sizeof(student), compareAscending); // 升序
	}
	else 
	{
		qsort(students, i, sizeof(student), compareDescending); // 降序
	}

	//将排好序的数组转换为新文件
	FILE* sort_student = fopen("sort_student.txt", "w+");
	for (int w = 0; w < i; w++) {
		fprintf(sort_student, "%s %s %d %s %s\n", students[w].ID, students[w].name, students[w].age, students[w].sex, students[w].Class);
	}
	fflush(sort_student);

	//操作完毕关掉文件
	fclose(file);
	fclose(sort_student);

	//替换文件
	if (remove("Student_Information.txt") != 0 || rename("sort_student.txt", "Student_Information.txt") != 0) {
		printf("排序失败!\n\n");
	}
	else {
		printf("排序成功！\n\n");
		file = fopen("Student_Information.txt", "a+");
	}
}



//sort的比较函数
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