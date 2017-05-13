#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

int ID=-1; //ID ���������� �������� ����


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
char *coloris[] {"�����", "�������" , "�������" , "������" };

struct arsenal {
	int id = -1;					// ID
	char *name = "";				// �������� ����������
	short number = -1;				// �����
	colors collor = blue;			// ���� 
	int damage = 25;				// ����
	int hp = 100;					// ��������
	float runtime = 0.0;			// ����� ������ (������� ����)
	long long cost = 0;				// ��������� (� ������)
	short shock = 0;				// ����� ���� (��)
	char *owner = "��� ���������";	// ��� ��������� (��� ���������, ���� �������)


	arsenal *next;


	void out()
	{
		printf("ID: %d\n�������� ����������: %s\n�����: %d\n����: %s\n����: %d%%\n��������: %d%%\n����� ������: %.2f �����\n���������: %lld ������\n���: %d ��\n��� ���������: %s\n-------------------------------\n", id, name, number, coloris[collor], damage, hp, runtime, cost, shock, owner);
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
	if (Head == NULL) { // ���� ������ ����,
		AddFirst(Head, Newbd); // ��������� ������ �������
		putID(Head);
		return;
	}
	Pbd e;
	while (q->next!=NULL) q = q->next; // ���� ��������� �������
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
	printf("���� ������:\n");
	while (base != NULL) {
		base->out();
		base = base->next;
	}
}

void ins() {
	Pbd one = new arsenal;


	char s[1000] = "";

	printf("�������� ����������:");
	gets_s(s, 999);
	one->name = s;

	printf("�����:");
	gets_s(s, 999);
	int y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("�� ����� �������� �����. ��������� ����:");
		gets_s(s, 999);
		y = StrToInt(s);
	}
	one->id = y;

	printf("����:");
	gets_s(s, 999);
	myStrcmp(s, "�����");
	while (!myStrcmp(s, "�����") && !myStrcmp(s, "�����") && !myStrcmp(s, "�������") && !myStrcmp(s, "�������") && !myStrcmp(s, "�������") && !myStrcmp(s, "�������") && !myStrcmp(s, "������") && !myStrcmp(s, "������")) {
		printf("�� ����� �������� ����. ��������� ����:");
		gets_s(s, 999);
	}
	if (myStrcmp(s, "�����") || myStrcmp(s, "�����")) one->collor = blue; else
		if (myStrcmp(s, "�������") || myStrcmp(s, "�������")) one->collor = red; else
			if (myStrcmp(s, "�������") || myStrcmp(s, "�������")) one->collor = green; else
				if (myStrcmp(s, "������") || myStrcmp(s, "������")) one->collor = yellow;

	printf("����:");
	gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("�� ����� �������� �����. ��������� ����:");
		gets_s(s, 999);
		y = StrToInt(s);
	}
	one->damage = y;

	printf("��������:");
	gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("�� ����� �������� �����. ��������� ����:");
		gets_s(s, 999);
		y = StrToInt(s);
	}
	one->hp = y;

	printf("����� ������ (������ ����� �����):");
	gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("�� ����� �������� �����. ��������� ����:");
		gets_s(s, 999);
		y = StrToInt(s);
	}
	one->runtime = atof(s);

	one->next = NULL;
	add(baza, one);
}

void inc() {
	Pbd one = new arsenal;
	one->name = "��-105";
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
	one->name = "��-12LT ������";
	one->collor = red;
	one->cost = 27000;
	one->damage = 25;
	one->hp = 100;
	one->number = 60;
	one->runtime = 7.39;
	one->shock = 1000;
	one->owner = "������";
	one->next = NULL;
	add(baza, one);
}


int main()
{
	SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������

	inc();

	int com = -1,	 // ����� �������
		u = -20,	 // Just needed
		kolKom = 3;	 // ���������� ������ ����������
	char s[1000];
	while (1) {
		com = -1;
		u = -20;
		printf("������� �������:\n");
		printf("0 - ������� ���� ������ �� �����\n");
		printf("1 - �������� �������\n");
		gets_s(s, 999);
		u = StrToInt(s);
		while ((intLi(s) == 0) || (u == -1)) {
		repeat:;
			printf("�� ����� �������� ����� ��� ������. ��������� ����:");
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

