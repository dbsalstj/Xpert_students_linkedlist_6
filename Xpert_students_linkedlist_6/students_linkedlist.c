#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>


/*---오류 목록---
1.학번 중복 검사 필요
2.이름순 정렬 함수 필요
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

void menu_print();/*---메뉴 출력 함수---*/
void init();/*---리스트 초기화 함수---*/
STUDENT* createNode();/*---추가할 노드를 입력 받는 함수---*/
void push_back();/*---노드를 리스트 뒤에 추가하는 함수---*/
void node_print();/*---모든 노드를 출력하는 함수---*/
void remove_node();/*---특정 노드를 삭제하는 함수---*/
void search_node();/*---학생 정보 검색 함수---*/
void free_node();/*---프로그램 초기화를 위한 함수---*/
int length_list();/*---리스트 길이 구하는 함수---*/
void sort_node();/*---리스트 정렬하는 함수---*/



int allDelCount = 0;
/*---메뉴 출력 함수---*/
void menu_print()
{
	printf("============== 학생 관리 프로그램 ==============\n");
	printf("%4d.학생 정보 추가\n", 1);
	printf("%4d.학생 정보 삭제\n", 2);
	printf("%4d.학생 정보 검색\n", 3);
	printf("%4d.학생 목록 출력\n", 4);
	printf("%4d.모든 학생 정보 삭제\n", 5);
	printf("%4d.프로그램 종료\n", 6);
	printf("================================================\n");
}

/*---리스트 초기화 함수---*/
void init()
{
	head = (STUDENT*)malloc(sizeof(STUDENT));
	tail = (STUDENT*)malloc(sizeof(STUDENT));

	head->rlink = tail;
	head->llink = head;
	tail->rlink = tail;
	tail->llink = head;
}

/*---추가할 노드를 입력 받는 함수---*/
STUDENT* createNode()
{
	STUDENT* temp = (STUDENT*)malloc(sizeof(STUDENT));
	STUDENT* temp2;
	temp2 = head;

	int cheak;

	printf("이름 : "); scanf("%s", &temp->name);

	printf("학번 : "); scanf("%d", &cheak);

	//---학번 중복 검사 기능 구현---
	while (temp2->rlink != tail)
	{
		if (temp2->class_num == cheak)
		{
			printf("중복된 학번이 존재합니다.\n");
			return NULL;
		}
		temp2 = temp2->rlink;
	}
	printf("학과 : "); scanf("%s", &temp->department);
	printf("나이 : "); scanf("%d", &temp->age);
	
	temp->class_num = cheak;

	return temp;
}

/*---이름의 사전 순으로 노드에 추가하는 함수---*/
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

/*---모든 노드를 출력하는 함수---*/
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
		puts("출력할 학생의 정보가 없습니다.");
		return;
	}
	else
	{
		while (temp->rlink != tail)
		{
			printf("이름 : %s 학번 : %8d     학과 : %s   나이 : %d\n", &temp->name, temp->class_num, &temp->department, temp->age);
			temp = temp->rlink;
		}
		printf("이름 : %s 학번 : %8d     학과 : %s   나이 : %d\n", &temp->name, temp->class_num, &temp->department, temp->age);
	}
}

/*---특정 노드를 삭제하는 함수---*/
void remove_node()
{
	int del_class_num;
	STUDENT* temp;

	printf("삭제할 학생의 학번을 입력하세요 : "); scanf("%d", &del_class_num);
	
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

/*---학생 정보 검색 함수---*/
void search_node()
{
	int sea_class_num;
	STUDENT* temp;
	temp = head;

	for (int i = 0; i < 27; i++)
		printf("=");
	printf(" 학생 정보 검색 ");
	for (int i = 0; i < 27; i++)
		printf("=");
	printf("\n");

	printf("검색할 학생의 학번을 입력하세요 : "); scanf("%d", &sea_class_num);

	while (temp != tail)
	{
		if (temp->class_num == sea_class_num)
		{
			for (int i = 0; i < 70; i++)
				printf("-");
			printf("\n");

			printf("이름 : %s 학번 : %8d     학과 : %s   나이 : %d\n", &temp->name, temp->class_num, &temp->department, temp->age);

			for (int i = 0; i < 70; i++)
				printf("-");
			printf("\n");
		}
		temp = temp->rlink;
	}

}

/*---프로그램 초기화를 위한 함수---*/
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

/*---리스트 길이 구하는 함수---*/
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

/*---리스트 정렬하는 함수---*/

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
		menu_print(); //메뉴 종류 출력
		printf("원하는 기능을 선택하세요 : "); scanf("%d", &menu); //메뉴를 선택

		switch (menu)
		{
		case 1:
			system("cls");//입력 받기전 콘솔창 비우기
			push_back();//학생 정보 입력
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");//입력 받기전 콘솔창 비우기
			remove_node();
			system("pause");
			system("cls");
			break;
		case 3:
			system("cls");//입력 받기전 콘솔창 비우기
			search_node();//학생 정보 검색
			system("pause");
			system("cls");
			break;
		case 4:
			system("cls");//입력 받기전 콘솔창 비우기
			node_print();//모든 학생 정보 출력
			system("pause");
			system("cls");
			break;
		case 5:
			system("cls");//입력 받기전 콘솔창 비우기
			free_node(&head);//모든 노드 삭제 ***오류***
			init();
			system("pause");
			system("cls");
			break;
		case 6:
			system("cls");//입력 받기전 콘솔창 비우기
			init();
			puts("프로그램을 종료합니다.");
			return 0;
		}
	}
}
