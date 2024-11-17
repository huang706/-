#ifndef MY_HEAD
#define MY_HEAD

//定义学生信息结构
typedef struct {
	char ID[20];
	char name[15];
	int age;
	char sex[5];
	char Class[20];
}student;

FILE* file;	//定义文件指针

//菜单
void menu();

//添加学生信息
void addStudent(FILE* file);

//查看所有学生信息
void show(FILE* file);

//按学号或姓名寻找某同生信息
void search(FILE* file);

//按学号删除某学生
void delete(FILE* file,char target[]);

//按学号或名称排序
void sort(FILE* file);

//清除所有学生信息
void removeAll(FILE* file);

//修改学生信息
void change(FILE* file, char target[]);

//定义比较函数
int compareAscending(void* a, void* b);
int compareDescending(void* a, void* b);

#endif