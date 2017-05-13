#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

int ID=-1; //ID последнего элемента базы


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
	int w = 0, dot = 0;
	char chisla[11] = "0123456789";
	while (s[w]) {
		for (int i = 0;i < 10;i++) {
			if (s[w] == chisla[i]) goto yes;
			if (s[w] == '.') {
				dot++;
				if (dot == 2) return 0;
				goto yes;
			}
		}
		return 0;
	yes:
		w++;
	}
	return 1;
}

int myStrcmp(char s1[1000], char s2[1000]) {
	int p = 0;
	if (s1[p] == '\n') s1[p] = '\0';
	if (s2[p] == '\n') s2[p] = '\0';
	while (s1[p]) {
		if (s1[p] != s2[p]) { goto wers; }
		p++;
		if (s1[p] == '\n') s1[p] = '\0';
		if (s2[p] == '\n') s2[p] = '\0';
	}
	if (s1[p] == s2[p]) return 1;
wers:;
	return 0;
}


enum colors { blue, red, green, yellow };
char *coloris[] {"Синий", "Красный" , "Зеленый" , "Желтый" };

struct arsenal {
	int id = -1;					// ID
	char *name = "";				// Название вооружения
	short number = -1;				// Номер
	colors collor = blue;			// Цвет 
	int damage = 25;				// Урон
	int hp = 100;					// Здоровье
	float runtime = 0.0;			// Время работы (дробные часы)
	long long cost = 0;				// Стоимость (в рублях)
	short shock = 0;				// Время шока (мс)
	char *owner = "ВЛК Диверсант";	// Имя владельца (ВЛК Диверсант, если клубный)


	arsenal *next;


	void out()
	{
		printf("ID: %d\nНазвание вооружения: %s\nНомер: %d\nЦвет: %s\nУрон: %d%%\nЗдоровье: %d%%\nВремя работы: %.2f часов\nСтоимость: %lld рублей\nШок: %d мс\nИмя владельца: %s\n-------------------------------\n", id, name, number, coloris[collor], damage, hp, runtime, cost, shock, owner);
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
		AddFirst(Head, Newbd); // вставляем первый элемент
		putID(Head);
		return;
	}
	Pbd e;
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

void outs() {
	Pbd base = baza;
	printf("База данных:\n");
	while (base != NULL) {
		base->out();
		base = base->next;
	}
}

void ins() {
	Pbd one = new arsenal;


	char s[1000] = "";

	printf("Название вооружения:");
	gets_s(s, 999);
	one->name = s;

	printf("Номер:");
	gets_s(s, 999);
	int y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		gets_s(s, 999);
		y = StrToInt(s);
	}
	one->id = y;

	printf("Цвет:");
	gets_s(s, 999);
	myStrcmp(s, "Синий");
	while (!myStrcmp(s, "Синий") && !myStrcmp(s, "синий") && !myStrcmp(s, "Красный") && !myStrcmp(s, "красный") && !myStrcmp(s, "Зеленый") && !myStrcmp(s, "зеленый") && !myStrcmp(s, "Желтый") && !myStrcmp(s, "желтый")) {
		printf("Вы ввели неверный цвет. Повторите ввод:");
		gets_s(s, 999);
	}
	if (myStrcmp(s, "Синий") || myStrcmp(s, "синий")) one->collor = blue; else
		if (myStrcmp(s, "Красный") || myStrcmp(s, "красный")) one->collor = red; else
			if (myStrcmp(s, "Зеленый") || myStrcmp(s, "зеленый")) one->collor = green; else
				if (myStrcmp(s, "Желтый") || myStrcmp(s, "желтый")) one->collor = yellow;

	printf("Урон:");
	gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		gets_s(s, 999);
		y = StrToInt(s);
	}
	one->damage = y;

	printf("Здоровье:");
	gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		gets_s(s, 999);
		y = StrToInt(s);
	}
	one->hp = y;

	printf("Время работы (дробью через точку):");
	gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		gets_s(s, 999);
		y = StrToInt(s);
	}
	one->runtime = atof(s);

	one->next = NULL;
	add(baza, one);
}

void inc() {
	Pbd one = new arsenal;
	one->name = "АК-105";
	one->collor = blue;
	one->cost = 33500;
	one->damage = 25;
	one->hp = 100;
	one->number = 6;
	one->runtime = 3.71;
	one->shock = 1000;
	one->next = NULL;
	add(baza, one);
	one = new arsenal;
	one->name = "АК-12LT Хищник";
	one->collor = red;
	one->cost = 27000;
	one->damage = 25;
	one->hp = 100;
	one->number = 60;
	one->runtime = 7.39;
	one->shock = 1000;
	one->owner = "ДиКарь";
	one->next = NULL;
	add(baza, one);
}


int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	inc();

	int com = -1,	 // Номер команды
		u = -20,	 // Just needed
		kolKom = 3;	 // Количество команд управления
	char s[1000];
	while (1) {
		com = -1;
		u = -20;
		printf("Введите команду:\n");
		printf("0 - Вывести базу данных на экран\n");
		printf("1 - Добавить элемент\n");
		gets_s(s, 999);
		u = StrToInt(s);
		while ((intLi(s) == 0) || (u == -1)) {
		repeat:;
			printf("Вы ввели неверное число или строку. Повторите ввод:");
			gets_s(s, 999);
			u = StrToInt(s);
		}
		if (u > kolKom - 1) goto repeat; else
		if (u == 0) outs();
		if (u == 1) ins();
		u = -1;
	}


	return 0;
}

