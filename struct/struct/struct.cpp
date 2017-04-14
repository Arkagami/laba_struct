#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>

int ID=-1; //ID последнего элемента базы


struct bd {
	int id;
	char *name;
	int count;
	bd *next;

	void myprint()
	{
			printf("id%d: %s - %d\n", id,  name, count);
	}
};
typedef bd *Pbd;

void putID(Pbd &Head) {
	Pbd q = Head;
	int i = 0;
	while (q != NULL) {
		q->id = i++;
		q = q->next;
	}
	ID = i - 1;
}

void AddFirst(Pbd &Head, Pbd Newbd)
{
	Newbd->next = Head;
	Head = Newbd;
	putID(Head);
}

void add(Pbd &Head, Pbd Newbd)
{
	Pbd q = Head;
	if (Head == NULL) { // если список пуст,
		AddFirst(Head, Newbd); // вставляем первый элемент
		return;
	}
	while (q->next!=NULL) q = q->next; // ищем последний элемент
	q->next = Newbd;
	q = Head;
	putID(Head);
}

void del(Pbd &Head, int id) {
	Pbd q = Head, qq = Head;
	while (q->id != id) {
		qq = q;
		q = q->next;
	}
	qq->next = q->next;
	putID(Head);
}

int intLi(char *s) {
	char *ss = s;
	char chisla[11] = "0123456789";
	while (*ss) {
		for (int i = 0;i < 10;i++) {
			if (*ss == chisla[i]) goto yes;
		}
		return 0;
	yes:
		ss++;
	}
	return 1;
}


int main()
{
	setlocale(LC_ALL, "RUS");
	/*
	Pbd CreateBD(char *nam, int COUNT) {
		Pbd try = new bd;
		try->count = COUNT;
		tr->next = NULL;
		return try;
	}*/

	Pbd one = new bd;
	Pbd baza = NULL;
	one->name = "Mixno";
	one->count = 12;
	add(baza, one);
	one->next = NULL;
	one = new bd;
	one->name = "MixNo";
	one->count = 14;
	one->next = NULL;
	add(baza, one);
	one = new bd;
	one->name = "MixNoooooooooo";
	one->count = 229878;
	one->next = NULL;
	add(baza, one);


	one = new bd;
	one->name = "Hui";
	one->count = 1204;
	one->next = NULL;
	AddFirst(baza, one);



	Pbd q = baza;
	while (q!=NULL) {
		q->myprint();
		q = q->next;
	}

	printf("---------------------------------------------\n");

	del(baza, 1);

	q = baza;
	while (q != NULL) {
		q->myprint();
		q = q->next;
	}

	int com = -1;
	char *s;
	printf("\nВведите команду:");
	scanf("%s", &s);
	printf("%s\n", *s);
	while (intLi(s) != 1) {
		printf("Вы ввели неверное число или строку. Повторите ввод:");
		scanf(" %s", &s);
		s--;
		*s = '\0';
	}
	printf("%s\n", *s);



	return 0;
}

