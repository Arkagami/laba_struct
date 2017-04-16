#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>

int ID=-1; //ID последнего элемента базы


struct arsenal {
	int id;
	char *name;			// Название вооружения
	short number;		// Номер
	int damage;			// Урон
	int hp;				// Здоровье
	float runtime;		// Время работы (дробные часы)
	long long cost;		// Стоимость
	short shock;		// Время шока
	char *owner;		// Имя владельца (ВЛК Диверсант, если клубный)


	arsenal *next;

	void myprint()
	{
			//printf("id%d: %s - %d\n", id,  name, number);
	}
};
typedef arsenal *Pbd;

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

int StrToInt(char *s) {
	int i = 0, ii = 0;
	while (*s) {
		ii = i;
		if (*s == '0') { i = 10 * i + 0; }
		if (*s == '1') { i = 10 * i + 1; }
		if (*s == '2') { i = 10 * i + 2; }
		if (*s == '3') { i = 10 * i + 3; }
		if (*s == '4') { i = 10 * i + 4; }
		if (*s == '5') { i = 10 * i + 5; }
		if (*s == '6') { i = 10 * i + 6; }
		if (*s == '7') { i = 10 * i + 7; }
		if (*s == '8') { i = 10 * i + 8; }
		if (*s == '9') { i = 10 * i + 9; }
		s++;
		if (ii > i) return -1;
	}
	return i;
}

int intLi(char s[1000]) {
	int w = 0;
	char chisla[11] = "0123456789";
	while (s[w]) {
		for (int i = 0;i < 10;i++) {
			if (s[w] == chisla[i]) goto yes;
		}
		return 0;
	yes:
		w++;
	}
	return 1;
}


int main()
{
	setlocale(LC_ALL, "RUS");
	/*
	Pbd CreateBD(char *nam, int COUNT) {
		Pbd try = new arsenal;
		try->count = COUNT;
		tr->next = NULL;
		return try;
	}*/

	Pbd one = new arsenal;
	Pbd baza = NULL;
	one->name = "Mixno";
	one->count = 12;
	add(baza, one);
	one->next = NULL;
	one = new arsenal;
	one->name = "MixNo";
	one->count = 14;
	one->next = NULL;
	add(baza, one);
	one = new arsenal;
	one->name = "MixNoooooooooo";
	one->count = 229878;
	one->next = NULL;
	add(baza, one);


	one = new arsenal;
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

	int com = -1, //Номер команды
		kolKom=0; //Количество команд управления
	char s[1000];
	printf("\nВведите команду:");
	gets_s(s, 999);
	printf("%s\n", s);
	while ((intLi(s) == 0) || (StrToInt(s)==-1)) {
	repeat:;
		printf("Вы ввели неверное число или строку. Повторите ввод:");
		gets_s(s, 999);
	}
	if (StrToInt(s) > kolKom-1) goto repeat;



	return 0;
}

