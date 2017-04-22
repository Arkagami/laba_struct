#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>

int ID=-1; //ID последнего элемента базы


enum colors { blue, red, green, yellow };
char *coloris[] {"Синий", "Красный" , "Зеленый" , "Желтый" };

struct arsenal {
	int id = -1;					// ID
	char *name = " ";				// Название вооружения
	short number = -1;				// Номер
	colors collor = blue;			// Цвет 
	int damage = -1;				// Урон
	int hp = -1;					// Здоровье
	float runtime = -1.0;			// Время работы (дробные часы)
	long long cost = -1;			// Стоимость (в рублях)
	short shock = -1;				// Время шока
	char *owner = "ВЛК Диверсант";	// Имя владельца (ВЛК Диверсант, если клубный)


	arsenal *next;


	void out()
	{
		printf("%d\n%s\n%d\n%s\n%d\n%d\n%.2f\n%lld\n%d\n%s\n-------------------------------\n", id, name, number, coloris[collor], damage, hp, runtime, cost, shock, owner);
	}
};
typedef arsenal *Pbd;

Pbd baza = NULL;

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
		Head->id = -100;
		Head->next = NULL;
		AddFirst(Head, Newbd); // вставляем первый элемент
		return;
	}
	Pbd e;
	while (e = q->next, e->id != -100) q = q->next; // ищем последний элемент
	Newbd->next = NULL;
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

int StrToInt(char *ss) {
	int i = 0, ii = 0;
	char *s = ss;
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

void outs() {
	Pbd base = baza;
	printf("База данных:\n");
	while (base->id != -100) {
		base->out();
		base = base->next;
	}
}

void inc() {
	Pbd one = new arsenal;
	one->name = "Mixno";
	one->number = 12;
	one->collor = red;
	add(baza, one);
	one->next = NULL;
	one = new arsenal;
	one->name = "MixNo";
	one->number = 14;
	one->next = NULL;
	add(baza, one);
	one = new arsenal;
	one->name = "MixNoooooooooo";
	one->number = 229878;
	one->next = NULL;
	add(baza, one);


	one = new arsenal;
	one->name = "Hui";
	one->number = 1204;
	one->next = NULL;
	AddFirst(baza, one);
}

void saves() {
	FILE *f = fopen("database.txt", "w");
	Pbd base = baza;
	while (base != NULL) {
		fwrite(&base, sizeof(struct arsenal), 1, f);
		base = base->next;
	}
	fclose(f);
}

void scans() {
	FILE *ff = fopen("database.txt", "r");
	Pbd base;
	baza = new arsenal;
	baza = NULL;
	while (fread(&base, sizeof(struct arsenal), 1, ff) == 1) {
	//	base->out();
		add(baza, base);
		base = NULL;
	}
	outs();
	fclose(ff);
}


int main()
{
	setlocale(LC_ALL, "RUS");

	inc();

	int com = -1,	 // Номер команды
		u = -20,	 // Just needed
		kolKom = 3;	 // Количество команд управления
	char s[1000];
	while (1) {
		com = -1;
		u = -20;
		printf("Введите команду:\n");
		printf("0 - Сохранить в файл\n");
		printf("1 - Загрузить из файла\n");
		printf("2 - Вывести базу данных на экран\n");
		gets_s(s, 999);
		u = StrToInt(s);
		while ((intLi(s) == 0) || (u == -1)) {
		repeat:;
			printf("Вы ввели неверное число или строку. Повторите ввод:");
			gets_s(s, 999);
			u = StrToInt(s);
		}
		if (u > kolKom - 1) goto repeat;
		if (u == 0) saves(); else
		if (u == 1) scans(); else
		if (u == 2) outs();
	}


	return 0;
}

