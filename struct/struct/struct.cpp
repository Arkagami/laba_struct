#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

int ID=-1; //ID ïîñëåäíåãî ýëåìåíòà áàçû


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
char *coloris[] {"Ñèíèé", "Êðàñíûé" , "Çåëåíûé" , "Æåëòûé" };

struct arsenal {
	int id = -1;						// ID
	char name[20] = "";					// Íàçâàíèå âîîðóæåíèÿ
	short number = -1;					// Íîìåð
	colors collor = blue;				// Öâåò 
	int damage = 25;					// Óðîí
	int hp = 100;						// Çäîðîâüå
	float runtime = 0.0;				// Âðåìÿ ðàáîòû (äðîáíûå ÷àñû)
	long long cost = 0;					// Ñòîèìîñòü (â ðóáëÿõ)
	short shock = 0;					// Âðåìÿ øîêà (ìñ)
	char owner[14] = "ÂËÊ Äèâåðñàíò";	// Èìÿ âëàäåëüöà (ÂËÊ Äèâåðñàíò, åñëè êëóáíûé)

      /*ID					3
		Íàçâàíèå âîîðóæåíèÿ 20
		Íîìåð				6
		Öâåò				8
		Óðîí				5
		Çäîðîâüå			9
		Âðåìÿ ðàáîòû	    13
		Ñòîèìîñòü		    10
		Øîê				    5
		Èìÿ âëàäåëüöà		14*/

	arsenal *next;


	void out()
	{
		printf("%-2d|%-19s|%-5d|%-7s|%-4d|%-8d|%-12.2f|%-9lld|%-4d|%-13s|\n", id, name, number, coloris[collor], damage, hp, runtime, cost, shock, owner);
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
	if (Head == NULL) { // åñëè ñïèñîê ïóñò,
		AddFirst(Head, Newbd); // âñòàâëÿåì ïåðâûé ýëåìåíò
		putID(Head);
		return;
	}
	Pbd e;
	while (q->next!=NULL) q = q->next; // èùåì ïîñëåäíèé ýëåìåíò
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
		printf("Áàçà ïóñòà.\n");
		return;
	}
	char s[1000];
	printf("Введите ID элемента:");
	gets_s(s, 999);
	int id = StrToInt(s);
	while ((intLi(s) == 0) || (id < 0) || (id > ID)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		gets_s(s, 999);
		id = StrToInt(s);
	}
	delet(baza, id);
}

void outs() {
	Pbd base = baza;								
	printf("Áàçà äàííûõ:\nID|Íàçâàíèå âîîðóæåíèÿ|Íîìåð|Öâåò   |Óðîí|Çäîðîâüå|Âðåìÿ ðàáîòû|Ñòîèìîñòü|Øîê |Èìÿ âëàäåëüöà|\n");
	while (base != NULL) {
		base->out();
		base = base->next;
	}
}

void ins() {
	Pbd one = new arsenal;


	char s[1000];

	printf("Название вооружения (более 19 букв обрезается):");
	gets_s(s, 999);	
	s[19] = '\0';
	strcpy(one->name, s);

	printf("Номер (более 5 цифр обрезается):");
	gets_s(s, 999);
	int y = StrToInt(s);
	while (intLi(s) == 0) {
		printf("Вы ввели неверное число. Повторите ввод:");
		gets_s(s, 999);
		y = StrToInt(s);
	}
	s[5] = '\0';
	y = StrToInt(s);
	one->number = y % 100000;

	printf("Цвет:");
	gets_s(s, 999);
	myStrcmp(s, "Синий");
	while (!myStrcmp(s, "Синий") && !myStrcmp(s, "синий") && !myStrcmp(s, "Красный") && !myStrcmp(s, "красный") && !myStrcmp(s, "Зеленый") && !myStrcmp(s, "зеленый") && !myStrcmp(s, "Желтый") && !myStrcmp(s, "желтый")) {
		printf("Вы ввели неверный цвет. Повторите ввод:");
		gets_s(s, 999);
	}
	if (myStrcmp(s, "Ñèíèé") || myStrcmp(s, "ñèíèé")) one->collor = blue; else
		if (myStrcmp(s, "Êðàñíûé") || myStrcmp(s, "êðàñíûé")) one->collor = red; else
			if (myStrcmp(s, "Çåëåíûé") || myStrcmp(s, "çåëåíûé")) one->collor = green; else
				if (myStrcmp(s, "Æåëòûé") || myStrcmp(s, "æåëòûé")) one->collor = yellow;

	printf("Урон (более 4 цифр обрезается):");
	gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		gets_s(s, 999);
		y = StrToInt(s);
	}
	s[4] = '\0';
	y = StrToInt(s);
	one->damage = y % 10000;

	printf("Здоровье (более 4 цифр обрезается):");
	gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		gets_s(s, 999);
		y = StrToInt(s);
	}
	s[4] = '\0';
	y = StrToInt(s);
	one->hp = y % 10000;

	printf("Время работы (дробью через точку не более 8 символов):");
	gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		gets_s(s, 999);
		y = StrToInt(s);
	}
	s[8] = '\0';
	one->runtime = atof(s);

	printf("Стоимость в рублях (более 9 цифр обрезается):");
	gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		gets_s(s, 999);
		y = StrToInt(s);
	}
	s[9] = '\0';
	y = StrToInt(s);
	one->cost = y % 1000000000;

	printf("Шок в мс (более 4 цифр обрезается):");
	gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("Вы ввели неверное число. Повторите ввод:");
		gets_s(s, 999);
		y = StrToInt(s);
	}
	s[4] = '\0';
	y = StrToInt(s);
	one->shock = y % 10000;

	printf("Имя владельца (более 13 букв обрезается):");
	gets_s(s, 999);
	s[13] = '\0';
	if (myStrcmp(s, "") == 0) strcpy(one->owner, s);

	one->next = NULL;
	add(baza, one);
}

void inc() {
	Pbd one = new arsenal;
	strcpy(one->name, "ÀÊ-105");
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
	strcpy(one->name, "ÀÊ-12LT Õèùíèê");
	one->collor = red;
	one->cost = 27000;
	one->damage = 25;
	one->hp = 100;
	one->number = 60;
	one->runtime = 7.39;
	one->shock = 1000;
	strcpy(one->owner, "ÄèÊàðü");
	one->next = NULL;
	add(baza, one);
}

void finds() {
	Pbd base = baza;
	int count = 0;
	printf("Ââåäèòå íîìåð êðèòåðèÿ ïîèñêà:");
	int com = -1,	 // Íîìåð êîìàíäû
		u = -20,	 // Just needed
		kolKom = 10;	 // Êîëè÷åñòâî êîìàíä óïðàâëåíèÿ
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
		printf("7 - Стоимость\n");
		printf("8 - Шок\n");
		printf("9 - Имя владельца\n");
		gets_s(s, 999);
		u = StrToInt(s);
		while ((intLi(s) == 0) || (u == -1)) {
		repeats:;
			printf("Вы ввели неверное число или строку. Повторите ввод:");
			gets_s(s, 999);
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
					gets_s(s, 999);
					id = StrToInt(s);
				}
				printf("Áàçà äàííûõ:\nID|Íàçâàíèå âîîðóæåíèÿ|Íîìåð|Öâåò   |Óðîí|Çäîðîâüå|Âðåìÿ ðàáîòû|Ñòîèìîñòü|Øîê |Èìÿ âëàäåëüöà|\n");
				while (base != NULL) {
					if (base->id == id) {
						count++; base->out();
					} base = base->next;
				}
				if (count == 0) printf("Ýëåìåíò íå íàéäåí.\n");
				}
		if (u == 1) {
			printf("Название вооружения (более 19 букв обрезается):");
			gets_s(s, 999);
			s[19] = '\0';
			printf("Áàçà äàííûõ:\nID|Íàçâàíèå âîîðóæåíèÿ|Íîìåð|Öâåò   |Óðîí|Çäîðîâüå|Âðåìÿ ðàáîòû|Ñòîèìîñòü|Øîê |Èìÿ âëàäåëüöà|\n");
			while (base != NULL) {
				if (myStrcmp(s, base->name)) {
					count++; base->out();
				} base = base->next;
			}
			if (count == 0) printf("Ýëåìåíò íå íàéäåí.\n");
		}
		if (u == 2) {
			printf("Номер (более 5 цифр обрезается):");
			gets_s(s, 999);
			int y = StrToInt(s);
			while (intLi(s) == 0) {
				printf("Вы ввели неверное число. Повторите ввод:");
				gets_s(s, 999);
				y = StrToInt(s);
			}
			s[5] = '\0';
			y = StrToInt(s);
			y = y % 100000;
			printf("Áàçà äàííûõ:\nID|Íàçâàíèå âîîðóæåíèÿ|Íîìåð|Öâåò   |Óðîí|Çäîðîâüå|Âðåìÿ ðàáîòû|Ñòîèìîñòü|Øîê |Èìÿ âëàäåëüöà|\n");
			while (base != NULL) {
				if (base->number == y) {
					count++; base->out();
				} base = base->next;
			}
				if (count == 0) printf("Ýëåìåíò íå íàéäåí.\n");
		}
		if (u == 3) {
			printf("Цвет:");
			gets_s(s, 999);
			myStrcmp(s, "Синий");
			while (!myStrcmp(s, "Синий") && !myStrcmp(s, "синий") && !myStrcmp(s, "Красный") && !myStrcmp(s, "красный") && !myStrcmp(s, "Зеленый") && !myStrcmp(s, "зеленый") && !myStrcmp(s, "Желтый") && !myStrcmp(s, "желтый")) {
				printf("Вы ввели неверный цвет. Повторите ввод:");
				gets_s(s, 999);
			}
			colors collor;
			if (myStrcmp(s, "Ñèíèé") || myStrcmp(s, "ñèíèé")) collor = blue; else
			if (myStrcmp(s, "Êðàñíûé") || myStrcmp(s, "êðàñíûé"))collor = red; else
			if (myStrcmp(s, "Çåëåíûé") || myStrcmp(s, "çåëåíûé")) collor = green; else
			if (myStrcmp(s, "Æåëòûé") || myStrcmp(s, "æåëòûé")) collor = yellow;
			printf("Áàçà äàííûõ:\nID|Íàçâàíèå âîîðóæåíèÿ|Íîìåð|Öâåò   |Óðîí|Çäîðîâüå|Âðåìÿ ðàáîòû|Ñòîèìîñòü|Øîê |Èìÿ âëàäåëüöà|\n");
			while (base != NULL) { 
				if (base->collor == collor) {
				count++; base->out();
			} base = base->next; }
			if (count==0) printf("Ýëåìåíò íå íàéäåí.\n");
		}
		if (u == 4) {
			printf("Урон (более 4 цифр обрезается):");
			gets_s(s, 999);
			int y = StrToInt(s);
			while ((intLi(s) == 0) || (y == -1)) {
				printf("Вы ввели неверное число. Повторите ввод:");
				gets_s(s, 999);
				y = StrToInt(s);
			}
			s[4] = '\0';
			y = StrToInt(s);
			y = y % 10000;
			printf("Áàçà äàííûõ:\nID|Íàçâàíèå âîîðóæåíèÿ|Íîìåð|Öâåò   |Óðîí|Çäîðîâüå|Âðåìÿ ðàáîòû|Ñòîèìîñòü|Øîê |Èìÿ âëàäåëüöà|\n");
			while (base != NULL) {
				if (base->damage == y) {
					count++; base->out();
				} base = base->next;
			}
			if (count == 0) printf("Ýëåìåíò íå íàéäåí.\n");
		}
		if (u == 5) {
			printf("Здоровье (более 4 цифр обрезается):");
			gets_s(s, 999);
			int y = StrToInt(s);
			while ((intLi(s) == 0) || (y == -1)) {
				printf("Вы ввели неверное число. Повторите ввод:");
				gets_s(s, 999);
				y = StrToInt(s);
			}
			s[4] = '\0';
			y = StrToInt(s);
			y = y % 10000;
			printf("Áàçà äàííûõ:\nID|Íàçâàíèå âîîðóæåíèÿ|Íîìåð|Öâåò   |Óðîí|Çäîðîâüå|Âðåìÿ ðàáîòû|Ñòîèìîñòü|Øîê |Èìÿ âëàäåëüöà|\n");
			while (base != NULL) {
				if (base->hp == y) {
					count++; base->out();
				} base = base->next;
			}
			if (count == 0) printf("Ýëåìåíò íå íàéäåí.\n");
		}
		if (u == 6) {
			printf("Время работы (дробью через точку не более 8 символов):");
			gets_s(s, 999);
			int y = StrToInt(s);
			while ((intLi(s) == 0) || (y == -1)) {
				printf("Вы ввели неверное число. Повторите ввод:");
				gets_s(s, 999);
				y = StrToInt(s);
			}
			s[8] = '\0';
			double f = atof(s);
			printf("Áàçà äàííûõ:\nID|Íàçâàíèå âîîðóæåíèÿ|Íîìåð|Öâåò   |Óðîí|Çäîðîâüå|Âðåìÿ ðàáîòû|Ñòîèìîñòü|Øîê |Èìÿ âëàäåëüöà|\n");
			while (base != NULL) {
				if (base->runtime == f) {
					count++; base->out();
				} base = base->next;
			}
			if (count == 0) printf("Ýëåìåíò íå íàéäåí.\n");
		}
		if (u == 7) {
			printf("Стоимость в рублях (более 9 цифр обрезается):");
			gets_s(s, 999);
			int y = StrToInt(s);
			while ((intLi(s) == 0) || (y == -1)) {
				printf("Вы ввели неверное число. Повторите ввод:");
				gets_s(s, 999);
				y = StrToInt(s);
			}
			s[9] = '\0';
			y = StrToInt(s);
			y = y % 1000000000;
			printf("Áàçà äàííûõ:\nID|Íàçâàíèå âîîðóæåíèÿ|Íîìåð|Öâåò   |Óðîí|Çäîðîâüå|Âðåìÿ ðàáîòû|Ñòîèìîñòü|Øîê |Èìÿ âëàäåëüöà|\n");
			while (base != NULL) {
				if (base->cost == y) {
					count++; base->out();
				} base = base->next;
			}
			if (count == 0) printf("Ýëåìåíò íå íàéäåí.\n");
		}
		if (u == 8) {
			printf("Шок в мс (более 4 цифр обрезается):");
			gets_s(s, 999);
			int y = StrToInt(s);
			while ((intLi(s) == 0) || (y == -1)) {
				printf("Вы ввели неверное число. Повторите ввод:");
				gets_s(s, 999);
				y = StrToInt(s);
			}
			s[4] = '\0';
			y = StrToInt(s);
			y = y % 10000;
			printf("Áàçà äàííûõ:\nID|Íàçâàíèå âîîðóæåíèÿ|Íîìåð|Öâåò   |Óðîí|Çäîðîâüå|Âðåìÿ ðàáîòû|Ñòîèìîñòü|Øîê |Èìÿ âëàäåëüöà|\n");
			while (base != NULL) {
				if (base->shock == y) {
					count++; base->out();
				} base = base->next;
			}
			if (count == 0) printf("Ýëåìåíò íå íàéäåí.\n");
		}
		if (u == 9) {
			printf("Имя владельца (более 13 букв обрезается):");
			gets_s(s, 999);
			s[13] = '\0';
			printf("Áàçà äàííûõ:\nID|Íàçâàíèå âîîðóæåíèÿ|Íîìåð|Öâåò   |Óðîí|Çäîðîâüå|Âðåìÿ ðàáîòû|Ñòîèìîñòü|Øîê |Èìÿ âëàäåëüöà|\n");
			while (base != NULL) {
				if (myStrcmp(s, base->owner)) {
					count++; base->out();
				} base = base->next;
			}
			if (count == 0) printf("Ýëåìåíò íå íàéäåí.\n");
		}
		else printf("\n");
		u = -1;
}


int main()
{
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD maxWindow = GetLargestConsoleWindowSize(out_handle); // ðàçìåð ñàìîãî áîëüøîãî âîçìîæíîãî êîíñîëüíîãî îêíà
	SMALL_RECT srctWindow = { 0, 0, maxWindow.X - 101, maxWindow.Y - 24 };
	SMALL_RECT minWindow = { 0, 0, 0, 0 };
	SetConsoleWindowInfo(out_handle, true, &minWindow);
	SetConsoleScreenBufferSize(out_handle, maxWindow);
	SetConsoleWindowInfo(out_handle, true, &srctWindow);


	SetConsoleCP(1251);// óñòàíîâêà êîäîâîé ñòðàíèöû win-cp 1251 â ïîòîê ââîäà
	SetConsoleOutputCP(1251); // óñòàíîâêà êîäîâîé ñòðàíèöû win-cp 1251 â ïîòîê âûâîäà

	inc();

	int com = -1,	 // Íîìåð êîìàíäû
		u = -20,	 // Just needed
		kolKom = 5;	 // Êîëè÷åñòâî êîìàíä óïðàâëåíèÿ
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
		gets_s(s, 999);
		u = StrToInt(s);
		while ((intLi(s) == 0) || (u == -1)) {
		repeat:;
			printf("Вы ввели неверное число или строку. Повторите ввод:");
			gets_s(s, 999);
			u = StrToInt(s);
		}
		system("cls");
		if (u > kolKom - 1) goto repeat; else
		if (u == 0) outs();
		if (u == 1) ins();
		if (u == 2) finds();
		if (u == 3) dels();
		if (u == 4) { baza = NULL; ID = -1; } else printf("\n");
		u = -1;
	}


	return 0;
}
