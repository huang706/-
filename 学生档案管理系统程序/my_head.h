#ifndef MY_HEAD
#define MY_HEAD

//����ѧ����Ϣ�ṹ
typedef struct {
	char ID[20];
	char name[15];
	int age;
	char sex[5];
	char Class[20];
}student;

FILE* file;	//�����ļ�ָ��

//�˵�
void menu();

//���ѧ����Ϣ
void addStudent(FILE* file);

//�鿴����ѧ����Ϣ
void show(FILE* file);

//��ѧ�Ż�����Ѱ��ĳͬ����Ϣ
void search(FILE* file);

//��ѧ��ɾ��ĳѧ��
void delete(FILE* file,char target[]);

//��ѧ�Ż���������
void sort(FILE* file);

//�������ѧ����Ϣ
void removeAll(FILE* file);

//�޸�ѧ����Ϣ
void change(FILE* file, char target[]);

//����ȽϺ���
int compareAscending(void* a, void* b);
int compareDescending(void* a, void* b);

#endif