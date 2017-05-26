#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

int ID = -1; //ID последнего элемента базы


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
		//if (ii > i) return -1;
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
char *coloris[]{ "Синий", "Красный" , "Зеленый" , "Желтый" };

union charging {
	int percent;
	char *status = "Разряжен";
	void news() {
		percent = NULL;
		status = NULL;
	}
};

struct arsenal {
	int id = -1;						// ID
	char name[20] = "";					// Название вооружения
	short number = -1;					// Номер
	colors collor = blue;				// Цвет 
	int damage = 25;					// Урон
	int hp = 100;						// Здоровье
	float runtime = 0.0;				// Время работы (дробные часы)
	union charging charge;				// Статус аккумулятора
	int what = 2;						// Нужно для union
	long long cost = 0;					// Стоимость (в рублях)
	short shock = 0;					// Время шока (мс)
	char owner[14] = "ВТК Диверсант";	// Имя владельца (ВТК Диверсант, если клубный)

										/*ID					3
										Название вооружения 20
										Номер				6
										Цвет				8
										Урон				5
										Здоровье			9
										Время работы	    13
										Статус акуумулятора	10
										Стоимость		    10
										Шок				    5
										Имя владельца		14*/

	arsenal *next;


	void out()
	{
		if (what == 1) printf("%-2d|%-19s|%-5d|%-7s|%-4d|%-8d|%-12.2f|%-2d%%       |%-9lld|%-4d|%-13s|\n", id, name, number, coloris[collor], damage, hp, runtime, charge.percent, cost, shock, owner);
		if (what == 2) printf("%-2d|%-19s|%-5d|%-7s|%-4d|%-8d|%-12.2f|%-10s|%-9lld|%-4d|%-13s|\n", id, name, number, coloris[collor], damage, hp, runtime, charge.status, cost, shock, owner);
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
	while (q->next != NULL) q = q->next; // ищем последний элемент
	q->next = Newbd;
	q = Head;
	putID(Head);
}

void delet(Pbd &Head, int id) {
	ID--;
	if (id == 0) {
		Head = Head->next;
		putID(Head);
		return;
	}
	Pbd q = Head, qq = Head;
	while (q->id != id) {
		qq = q;
		q = q->next;
	}
	qq->next = q->next;
	putID(Head);
}

void dels() {
	if (ID == -1) {
		printf("База пуста.\n");
		return;
	}
	char s[1000];
	printf("Введите ID элемента:");
	s[0] = '\0'; gets_s(s, 999);
	int id = StrToInt(s);
	while ((intLi(s) == 0) || (id < 0) || (id > ID)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		s[0] = '\0'; gets_s(s, 999);
		id = StrToInt(s);
	}
	delet(baza, id);
}

void outs() {
	Pbd base = baza;
	printf("База данных:\nID|Название вооружения|Номер|Цвет   |Урон|Здоровье|Время работы|Батарея   |Стоимость|Шок |Имя владельца|\n");
	while (base != NULL) {
		base->out();
		base = base->next;
	}
}

void ins() {
	Pbd one = new arsenal;


	char s[1000];

	printf("Название вооружения (более 19 букв обрезается):");
	s[0] = '\0'; gets_s(s, 999);
	s[19] = '\0';
	strcpy(one->name, s);

	printf("Номер (более 5 цифр обрезается):");
	s[0] = '\0'; gets_s(s, 999);
	int y = StrToInt(s);
	while (intLi(s) == 0) {
		printf("Вы ввели неверное число. Повторите ввод:");
		s[0] = '\0'; gets_s(s, 999);
		y = StrToInt(s);
	}
	s[5] = '\0';
	y = StrToInt(s);
	one->number = y % 100000;

	printf("Цвет (Синий, Красный , Зеленый , Желтый):");
	s[0] = '\0'; gets_s(s, 999);
	myStrcmp(s, "Синий");
	while (!myStrcmp(s, "Синий") && !myStrcmp(s, "синий") && !myStrcmp(s, "Красный") && !myStrcmp(s, "красный") && !myStrcmp(s, "Зеленый") && !myStrcmp(s, "зеленый") && !myStrcmp(s, "Желтый") && !myStrcmp(s, "желтый")) {
		printf("Вы ввели неверный цвет. Повторите ввод:");
		s[0] = '\0'; gets_s(s, 999);
	}
	if (myStrcmp(s, "Синий") || myStrcmp(s, "синий")) one->collor = blue; else
		if (myStrcmp(s, "Красный") || myStrcmp(s, "красный")) one->collor = red; else
			if (myStrcmp(s, "Зеленый") || myStrcmp(s, "зеленый")) one->collor = green; else
				if (myStrcmp(s, "Желтый") || myStrcmp(s, "желтый")) one->collor = yellow;

	printf("Урон (более 4 цифр обрезается):");
	s[0] = '\0'; gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		s[0] = '\0'; gets_s(s, 999);
		y = StrToInt(s);
	}
	s[4] = '\0';
	y = StrToInt(s);
	one->damage = y % 10000;

	printf("Здоровье (более 4 цифр обрезается):");
	s[0] = '\0'; gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		s[0] = '\0'; gets_s(s, 999);
		y = StrToInt(s);
	}
	s[4] = '\0';
	y = StrToInt(s);
	one->hp = y % 10000;

	printf("Время работы (дробью через точку не более 8 символов):");
	s[0] = '\0'; gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		s[0] = '\0'; gets_s(s, 999);
		y = StrToInt(s);
	}
	s[8] = '\0';
	one->runtime = atof(s);

	printf("Заряд аккумулятора (более 2 цифр обрезается; доступны статусы \"Заряжен\", \"Заряжается\", \"Разряжен\"):");
	s[0] = '\0'; gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		s[0] = '\0'; gets_s(s, 999);
		if (s[0] == 'з') s[0] = 'З';
		if (s[0] == 'р') s[0] = 'Р';
		if ((myStrcmp(s, "Заряжен") == 1) || (myStrcmp(s, "Заряжается") == 1) || (myStrcmp(s, "Разряжен") == 1)) {
			one->charge.news(); strcpy(one->charge.status, s); one->what = 2; goto outss;
		}
		y = StrToInt(s);
	}
	s[3] = '\0';
	char ss[1000];
	ss[0] = s[0];
	ss[1] = s[1];
	ss[2] = '\0';
	y = StrToInt(s);
	if (y > 100) {
		y = StrToInt(ss);
	}
	if ((y > 5) && (y < 100)) {
		one->what = 1;
		one->charge.news();
		one->charge.percent = y;
	}
	if (y == 100) {
		one->what = 2;
		one->charge.news();
		one->charge.status = "Заряжен";
	}
	if (y <= 5) {
		one->what = 2;
		one->charge.news();
		one->charge.status = "Разряжен";
	}
	outss:;

	printf("Стоимость в рублях (более 9 цифр обрезается):");
	s[0] = '\0'; gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		s[0] = '\0'; gets_s(s, 999);
		y = StrToInt(s);
	}
	s[9] = '\0';
	y = StrToInt(s);
	one->cost = y % 1000000000;

	printf("Шок в мс (более 4 цифр обрезается):");
	s[0] = '\0'; gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		s[0] = '\0'; gets_s(s, 999);
		y = StrToInt(s);
	}
	s[4] = '\0';
	y = StrToInt(s);
	one->shock = y % 10000;

	printf("Имя владельца (более 13 букв обрезается):");
	s[0] = '\0'; gets_s(s, 999);
	s[13] = '\0';
	if (myStrcmp(s, "") == 0) strcpy(one->owner, s);

	one->next = NULL;
	add(baza, one);
}

void inc() {
	Pbd one = new arsenal;
	strcpy(one->name, "АК-105");
	one->collor = blue;
	one->cost = 33500;
	one->damage = 25;
	one->hp = 100;
	one->number = 6;
	one->runtime = 3.71;
	one->charge.news();
	one->charge.percent = 89;
	one->what = 1;
	one->shock = 1000;
	one->next = NULL;
	add(baza, one);
	one = new arsenal;
	strcpy(one->name, "АК-12LT Хищник");
	one->collor = red;
	one->cost = 27000;
	one->damage = 25;
	one->hp = 100;
	one->number = 60;
	one->runtime = 7.39;
	one->charge.news();
	one->charge.status = "Заряжен";
	one->what = 2;
	one->shock = 1000;
	strcpy(one->owner, "Mixno");
	one->next = NULL;
	add(baza, one);
}

void finds() {
	Pbd base = baza;
	int count = 0;
	printf("Введите номер критерия поиска:");
	int com = -1,	 // Номер команды
		u = -20,	 // Just needed
		kolKom = 11;	 // Количество команд управления
	char s[1000];
	com = -1;
	u = -20;
	printf("0 - ID\n");
	printf("1 - Название вооружения\n");
	printf("2 - Номер\n");
	printf("3 - Цвет\n");
	printf("4 - Урон\n");
	printf("5 - Здоровье\n");
	printf("6 - Время работы\n");
	printf("7 - Заряд аккумулятора\n");
	printf("8 - Стоимость\n");
	printf("9 - Шок\n");
	printf("10 - Имя владельца\n");
	s[0] = '\0'; gets_s(s, 999);
	u = StrToInt(s);
	while ((intLi(s) == 0) || (u == -1)) {
	repeats:;
		printf("Вы ввели неверное число или строку. Повторите ввод:");
		s[0] = '\0'; gets_s(s, 999);
		u = StrToInt(s);
	}
	system("cls");
	if (u > kolKom - 1) goto repeats; else

	if (u == 0) {
			printf("ID:");
			s[0] = '\0'; gets_s(s, 999);
			int id = StrToInt(s);
			while ((intLi(s) == 0) || (id < 0) || (id > ID)) {
				printf("Вы ввели неверное число. Повторите ввод:");
				s[0] = '\0'; gets_s(s, 999);
				id = StrToInt(s);
			}
			printf("База данных:\nID|Название вооружения|Номер|Цвет   |Урон|Здоровье|Время работы|Батарея   |Стоимость|Шок |Имя владельца|\n");
			while (base != NULL) {
				if (base->id == id) {
					count++; base->out();
				} base = base->next;
			}
			if (count == 0) printf("Элемент не найден.\n");
		}
	if (u == 1) {
		printf("Название вооружения (более 19 букв обрезается):");
		s[0] = '\0'; gets_s(s, 999);
		s[19] = '\0';
		printf("База данных:\nID|Название вооружения|Номер|Цвет   |Урон|Здоровье|Время работы|Батарея   |Стоимость|Шок |Имя владельца|\n");
		while (base != NULL) {
			if (myStrcmp(s, base->name)) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("Элемент не найден.\n");
	}
	if (u == 2) {
		printf("Номер (более 5 цифр обрезается):");
		s[0] = '\0'; gets_s(s, 999);
		int y = StrToInt(s);
		while (intLi(s) == 0) {
			printf("Вы ввели неверное число. Повторите ввод:");
			s[0] = '\0'; gets_s(s, 999);
			y = StrToInt(s);
		}
		s[5] = '\0';
		y = StrToInt(s);
		y = y % 100000;
		printf("База данных:\nID|Название вооружения|Номер|Цвет   |Урон|Здоровье|Время работы|Батарея   |Стоимость|Шок |Имя владельца|\n");
		while (base != NULL) {
			if (base->number == y) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("Элемент не найден.\n");
	}
	if (u == 3) {
		printf("Цвет:");
		s[0] = '\0'; gets_s(s, 999);
		myStrcmp(s, "Синий");
		while (!myStrcmp(s, "Синий") && !myStrcmp(s, "синий") && !myStrcmp(s, "Красный") && !myStrcmp(s, "красный") && !myStrcmp(s, "Зеленый") && !myStrcmp(s, "зеленый") && !myStrcmp(s, "Желтый") && !myStrcmp(s, "желтый")) {
			printf("Вы ввели неверный цвет. Повторите ввод:");
			s[0] = '\0'; gets_s(s, 999);
		}
		colors collor;
		if (myStrcmp(s, "Синий") || myStrcmp(s, "синий")) collor = blue; else
			if (myStrcmp(s, "Красный") || myStrcmp(s, "красный"))collor = red; else
				if (myStrcmp(s, "Зеленый") || myStrcmp(s, "зеленый")) collor = green; else
					if (myStrcmp(s, "Желтый") || myStrcmp(s, "желтый")) collor = yellow;
		printf("База данных:\nID|Название вооружения|Номер|Цвет   |Урон|Здоровье|Время работы|Батарея   |Стоимость|Шок |Имя владельца|\n");
		while (base != NULL) {
			if (base->collor == collor) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("Элемент не найден.\n");
	}
	if (u == 4) {
		printf("Урон (более 4 цифр обрезается):");
		s[0] = '\0'; gets_s(s, 999);
		int y = StrToInt(s);
		while ((intLi(s) == 0) || (y == -1)) {
			printf("Вы ввели неверное число. Повторите ввод:");
			s[0] = '\0'; gets_s(s, 999);
			y = StrToInt(s);
		}
		s[4] = '\0';
		y = StrToInt(s);
		y = y % 10000;
		printf("База данных:\nID|Название вооружения|Номер|Цвет   |Урон|Здоровье|Время работы|Батарея   |Стоимость|Шок |Имя владельца|\n");
		while (base != NULL) {
			if (base->damage == y) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("Элемент не найден.\n");
	}
	if (u == 5) {
		printf("Здоровье (более 4 цифр обрезается):");
		s[0] = '\0'; gets_s(s, 999);
		int y = StrToInt(s);
		while ((intLi(s) == 0) || (y == -1)) {
			printf("Вы ввели неверное число. Повторите ввод:");
			s[0] = '\0'; gets_s(s, 999);
			y = StrToInt(s);
		}
		s[4] = '\0';
		y = StrToInt(s);
		y = y % 10000;
		printf("База данных:\nID|Название вооружения|Номер|Цвет   |Урон|Здоровье|Время работы|Батарея   |Стоимость|Шок |Имя владельца|\n");
		while (base != NULL) {
			if (base->hp == y) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("Элемент не найден.\n");
	}
	if (u == 6) {
		printf("Время работы (дробью через точку не более 8 символов):");
		s[0] = '\0'; gets_s(s, 999);
		int y = StrToInt(s);
		while ((intLi(s) == 0) || (y == -1)) {
			printf("Вы ввели неверное число. Повторите ввод:");
			s[0] = '\0'; gets_s(s, 999);
			y = StrToInt(s);
		}
		s[8] = '\0';
		double f = atof(s);
		printf("База данных:\nID|Название вооружения|Номер|Цвет   |Урон|Здоровье|Время работы|Батарея   |Стоимость|Шок |Имя владельца|\n");
		while (base != NULL) {
			if (base->runtime == f) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("Элемент не найден.\n");
	}
	if (u == 7) {
		printf("Заряд аккумулятора (более 2 цифр обрезается; доступны статусы \"Заряжен\", \"Заряжается\", \"Разряжен\"):");
		s[0] = '\0'; gets_s(s, 999);
		int y = StrToInt(s);
		if (s[0] == 'з') s[0] = 'З';
		if (s[0] == 'р') s[0] = 'Р';
		if ((myStrcmp(s, "Заряжен") == 1) || (myStrcmp(s, "Заряжается") == 1) || (myStrcmp(s, "Разряжен") == 1)) {
			printf("База данных:\nID|Название вооружения|Номер|Цвет   |Урон|Здоровье|Время работы|Батарея   |Стоимость|Шок |Имя владельца|\n");
			while (base != NULL) {
				if ((base->what == 2) && myStrcmp(s, base->charge.status)) {
					count++; base->out();
				} base = base->next;
			}
			if (count == 0) printf("Элемент не найден.\n");
			goto outsa;
		}
		while ((intLi(s) == 0) || (y == -1)) {
			printf("Вы ввели неверное число. Повторите ввод:");
			s[0] = '\0'; gets_s(s, 999);
			if (s[0] == 'з') s[0] = 'З';
			if (s[0] == 'р') s[0] = 'Р';
			if ((myStrcmp(s, "Заряжен") == 1) || (myStrcmp(s, "Заряжается") == 1) || (myStrcmp(s, "Разряжен") == 1)) {
				printf("База данных:\nID|Название вооружения|Номер|Цвет   |Урон|Здоровье|Время работы|Батарея   |Стоимость|Шок |Имя владельца|\n");
				while (base != NULL) {
					if ((base->what == 2) && myStrcmp(s, base->charge.status)) {
						count++; base->out();
					} base = base->next;
				}
				if (count == 0) printf("Элемент не найден.\n");
				goto outsa;
			}
			y = StrToInt(s);
		}
		s[2] = '\0';
		y = StrToInt(s);
		printf("База данных:\nID|Название вооружения|Номер|Цвет   |Урон|Здоровье|Время работы|Батарея   |Стоимость|Шок |Имя владельца|\n");
		while (base != NULL) {
			if ((base->what == 1) && (base->charge.percent == y)) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("Элемент не найден.\n");
	outsa:;
	}
	if (u == 8) {
		printf("Стоимость в рублях (более 9 цифр обрезается):");
		s[0] = '\0'; gets_s(s, 999);
		int y = StrToInt(s);
		while ((intLi(s) == 0) || (y == -1)) {
			printf("Вы ввели неверное число. Повторите ввод:");
			s[0] = '\0'; gets_s(s, 999);
			y = StrToInt(s);
		}
		s[9] = '\0';
		y = StrToInt(s);
		y = y % 1000000000;
		printf("База данных:\nID|Название вооружения|Номер|Цвет   |Урон|Здоровье|Время работы|Батарея   |Стоимость|Шок |Имя владельца|\n");
		while (base != NULL) {
			if (base->cost == y) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("Элемент не найден.\n");
	}
	if (u == 9) {
		printf("Шок в мс (более 4 цифр обрезается):");
		s[0] = '\0'; gets_s(s, 999);
		int y = StrToInt(s);
		while ((intLi(s) == 0) || (y == -1)) {
			printf("Вы ввели неверное число. Повторите ввод:");
			s[0] = '\0'; gets_s(s, 999);
			y = StrToInt(s);
		}
		s[4] = '\0';
		y = StrToInt(s);
		y = y % 10000;
		printf("База данных:\nID|Название вооружения|Номер|Цвет   |Урон|Здоровье|Время работы|Батарея   |Стоимость|Шок |Имя владельца|\n");
		while (base != NULL) {
			if (base->shock == y) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("Элемент не найден.\n");
	}
	if (u == 10) {
		printf("Имя владельца (более 13 букв обрезается):");
		s[0] = '\0'; gets_s(s, 999);
		s[13] = '\0';
		printf("База данных:\nID|Название вооружения|Номер|Цвет   |Урон|Здоровье|Время работы|Батарея   |Стоимость|Шок |Имя владельца|\n");
		while (base != NULL) {
			if (myStrcmp(s, base->owner)) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("Элемент не найден.\n");
	}
	else printf("\n");
	u = -1;
}


int main()
{
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD maxWindow = GetLargestConsoleWindowSize(out_handle); // размер самого большого возможного консольного окна
	SMALL_RECT srctWindow = { 0, 0, maxWindow.X - 92, maxWindow.Y - 24 };
	SMALL_RECT minWindow = { 0, 0, 0, 0 };
	SetConsoleWindowInfo(out_handle, true, &minWindow);
	SetConsoleScreenBufferSize(out_handle, maxWindow);
	SetConsoleWindowInfo(out_handle, true, &srctWindow);


	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	inc();

	int com = -1,	 // Номер команды
		u = -20,	 // Just needed
		kolKom = 5;	 // Количество команд управления
	char s[1000];
	while (1) {
		com = -1;
		u = -20;
		printf("Введите команду:\n");
		printf("0 - Вывести базу данных на экран\n");
		printf("1 - Добавить элемент\n");
		printf("2 - Найти элемент\n");
		printf("3 - Удалить элемент\n");
		printf("4 - Удалить всю базу\n");
		s[0] = '\0'; gets_s(s, 999);
		u = StrToInt(s);
		while ((intLi(s) == 0) || (u == -1)) {
		repeat:;
			printf("Вы ввели неверное число или строку. Повторите ввод:");
			s[0] = '\0'; gets_s(s, 999);
			u = StrToInt(s);
		}
		system("cls");
		if (u > kolKom - 1) goto repeat; else
		if (u == 0) outs();
		if (u == 1) ins();
		if (u == 2) finds();
		if (u == 3) dels();
		if (u == 4) { baza = NULL; ID = -1; }
		else printf("\n");
		u = -1;
	}


	return 0;
}