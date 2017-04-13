#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct bd {
	char *name;
	int count;
	bd *next;

	void myprint()
	{
			printf("%s - %d\n", name, count);
	}
};
typedef bd *Pbd;

void AddFirst(Pbd &Head, Pbd Newbd)
{
	Newbd->next = Head;
	Head = Newbd;
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
	Head = q;
}

int main()
{
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


	return 0;
}

