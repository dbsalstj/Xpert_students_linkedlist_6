#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>


/*---���� ���---
1.�й� �ߺ� �˻� �ʿ�
2.�̸��� ���� �Լ� �ʿ�
*/

typedef struct students {
	char name[20];
	char department[20];
	int age;
	int class_num;
	struct students* llink;//nest
	struct students* rlink;//prev
}STUDENT;

STUDENT* head;
STUDENT* tail;

void menu_print();/*---�޴� ��� �Լ�---*/
void init();/*---����Ʈ �ʱ�ȭ �Լ�---*/
STUDENT* createNode();/*---�߰��� ��带 �Է� �޴� �Լ�---*/
void push_back();/*---��带 ����Ʈ �ڿ� �߰��ϴ� �Լ�---*/
void node_print();/*---��� ��带 ����ϴ� �Լ�---*/
void remove_node();/*---Ư�� ��带 �����ϴ� �Լ�---*/
void search_node();/*---�л� ���� �˻� �Լ�---*/
void free_node();/*---���α׷� �ʱ�ȭ�� ���� �Լ�---*/
int length_list();/*---����Ʈ ���� ���ϴ� �Լ�---*/
void sort_node();/*---����Ʈ �����ϴ� �Լ�---*/



int allDelCount = 0;
/*---�޴� ��� �Լ�---*/
void menu_print()
{
	printf("============== �л� ���� ���α׷� ==============\n");
	printf("%4d.�л� ���� �߰�\n", 1);
	printf("%4d.�л� ���� ����\n", 2);
	printf("%4d.�л� ���� �˻�\n", 3);
	printf("%4d.�л� ��� ���\n", 4);
	printf("%4d.��� �л� ���� ����\n", 5);
	printf("%4d.���α׷� ����\n", 6);
	printf("================================================\n");
}

/*---����Ʈ �ʱ�ȭ �Լ�---*/
void init()
{
	head = (STUDENT*)malloc(sizeof(STUDENT));
	tail = (STUDENT*)malloc(sizeof(STUDENT));

	head->rlink = tail;
	head->llink = head;
	tail->rlink = tail;
	tail->llink = head;
}

/*---�߰��� ��带 �Է� �޴� �Լ�---*/
STUDENT* createNode()
{
	STUDENT* temp = (STUDENT*)malloc(sizeof(STUDENT));
	STUDENT* temp2;
	temp2 = head;

	int cheak;

	printf("�̸� : "); scanf("%s", &temp->name);

	printf("�й� : "); scanf("%d", &cheak);

	//---�й� �ߺ� �˻� ��� ����---
	while (temp2->rlink != tail)
	{
		if (temp2->class_num == cheak)
		{
			printf("�ߺ��� �й��� �����մϴ�.\n");
			return NULL;
		}
		temp2 = temp2->rlink;
	}
	printf("�а� : "); scanf("%s", &temp->department);
	printf("���� : "); scanf("%d", &temp->age);
	
	temp->class_num = cheak;

	return temp;
}

/*---�̸��� ���� ������ ��忡 �߰��ϴ� �Լ�---*/
void push_back()
{
	STUDENT* newNode = createNode();
	//STUDENT* temp;
	STUDENT* temp = head->rlink;

	if (head->rlink == tail) {
		head->rlink = newNode;
		newNode->llink = head;
		newNode->rlink = tail;
		tail->llink = newNode;
	}
	else {
		while (1) {
			if (strcmp(temp->name, newNode->name) > 0) {
				newNode->rlink = temp;
				newNode->llink = temp->llink;
				temp->llink->rlink = newNode;
				temp->llink = newNode;
				return;
			}
			if (temp == tail)
			{
				newNode->rlink = tail;
				newNode->llink = tail->llink;
				tail->llink->rlink = newNode;
				tail->llink = newNode;
				return;
			}
			temp = temp->rlink;
		}
	}

	/*
	temp = tail;
	temp->llink->rlink = newNode;
	newNode->llink = temp->llink;
	temp->llink = newNode;
	newNode->rlink = temp;
	*/

	allDelCount = 0;
}

/*---��� ��带 ����ϴ� �Լ�---*/
void node_print()
{
	STUDENT* temp;
	temp = head;
	temp = temp->rlink;

	//sort_node();

	if (allDelCount)
		return;
	if (temp->rlink == NULL)
	{
		puts("����� �л��� ������ �����ϴ�.");
		return;
	}
	else
	{
		while (temp->rlink != tail)
		{
			printf("�̸� : %s �й� : %8d     �а� : %s   ���� : %d\n", &temp->name, temp->class_num, &temp->department, temp->age);
			temp = temp->rlink;
		}
		printf("�̸� : %s �й� : %8d     �а� : %s   ���� : %d\n", &temp->name, temp->class_num, &temp->department, temp->age);
	}
}

/*---Ư�� ��带 �����ϴ� �Լ�---*/
void remove_node()
{
	int del_class_num;
	STUDENT* temp;

	printf("������ �л��� �й��� �Է��ϼ��� : "); scanf("%d", &del_class_num);
	
	temp = head->rlink;
	while (temp != tail)
	{
		if (temp->class_num == del_class_num)
		{
			temp->rlink->llink = temp->llink;
			temp->llink->rlink = temp->rlink;
			free(temp);
			return;
		}
		temp = temp->rlink;
	}
}

/*---�л� ���� �˻� �Լ�---*/
void search_node()
{
	int sea_class_num;
	STUDENT* temp;
	temp = head;

	for (int i = 0; i < 27; i++)
		printf("=");
	printf(" �л� ���� �˻� ");
	for (int i = 0; i < 27; i++)
		printf("=");
	printf("\n");

	printf("�˻��� �л��� �й��� �Է��ϼ��� : "); scanf("%d", &sea_class_num);

	while (temp != tail)
	{
		if (temp->class_num == sea_class_num)
		{
			for (int i = 0; i < 70; i++)
				printf("-");
			printf("\n");

			printf("�̸� : %s �й� : %8d     �а� : %s   ���� : %d\n", &temp->name, temp->class_num, &temp->department, temp->age);

			for (int i = 0; i < 70; i++)
				printf("-");
			printf("\n");
		}
		temp = temp->rlink;
	}

}

/*---���α׷� �ʱ�ȭ�� ���� �Լ�---*/
void free_node()
{
	STUDENT* delNode = head;

	if (head != NULL)
	{
		head->llink->rlink = NULL;
		while (delNode != NULL)
		{
			delNode->llink = NULL;
			head = delNode->rlink;
			free(delNode);
			delNode = head;
		}
	}
	allDelCount++;
}

/*---����Ʈ ���� ���ϴ� �Լ�---*/
int length_list()
{
	STUDENT* temp;
	int count = 0;
	if (tail)
	{
		temp = head;
		do
		{
			count++;
			temp = temp->rlink;
		} while (temp != tail);
	}
	return count-1;
}

/*---����Ʈ �����ϴ� �Լ�---*/

//void sort_node(STUDENT* list)
//{
//	STUDENT* temp = head->rlink;
//	while (1)
//	{
//		if(strcmp())
//	}
//}


int main(void)
{
	int menu = 0;
	init();
	while (menu != 6)
	{
		menu_print(); //�޴� ���� ���
		printf("���ϴ� ����� �����ϼ��� : "); scanf("%d", &menu); //�޴��� ����

		switch (menu)
		{
		case 1:
			system("cls");//�Է� �ޱ��� �ܼ�â ����
			push_back();//�л� ���� �Է�
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");//�Է� �ޱ��� �ܼ�â ����
			remove_node();
			system("pause");
			system("cls");
			break;
		case 3:
			system("cls");//�Է� �ޱ��� �ܼ�â ����
			search_node();//�л� ���� �˻�
			system("pause");
			system("cls");
			break;
		case 4:
			system("cls");//�Է� �ޱ��� �ܼ�â ����
			node_print();//��� �л� ���� ���
			system("pause");
			system("cls");
			break;
		case 5:
			system("cls");//�Է� �ޱ��� �ܼ�â ����
			free_node(&head);//��� ��� ���� ***����***
			init();
			system("pause");
			system("cls");
			break;
		case 6:
			system("cls");//�Է� �ޱ��� �ܼ�â ����
			init();
			puts("���α׷��� �����մϴ�.");
			return 0;
		}
	}
}
