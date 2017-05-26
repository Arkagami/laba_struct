#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

int ID = -1; //ID ���������� �������� ����


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
char *coloris[]{ "�����", "�������" , "�������" , "������" };

union charging {
	int percent;
	char *status = "��������";
	void news() {
		percent = NULL;
		status = NULL;
	}
};

struct arsenal {
	int id = -1;						// ID
	char name[20] = "";					// �������� ����������
	short number = -1;					// �����
	colors collor = blue;				// ���� 
	int damage = 25;					// ����
	int hp = 100;						// ��������
	float runtime = 0.0;				// ����� ������ (������� ����)
	union charging charge;				// ������ ������������
	int what = 2;						// ����� ��� union
	long long cost = 0;					// ��������� (� ������)
	short shock = 0;					// ����� ���� (��)
	char owner[14] = "��� ���������";	// ��� ��������� (��� ���������, ���� �������)

										/*ID					3
										�������� ���������� 20
										�����				6
										����				8
										����				5
										��������			9
										����� ������	    13
										������ ������������	10
										���������		    10
										���				    5
										��� ���������		14*/

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
	if (Head == NULL) { // ���� ������ ����,
		AddFirst(Head, Newbd); // ��������� ������ �������
		putID(Head);
		return;
	}
	Pbd e;
	while (q->next != NULL) q = q->next; // ���� ��������� �������
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
		printf("���� �����.\n");
		return;
	}
	char s[1000];
	printf("������� ID ��������:");
	s[0] = '\0'; gets_s(s, 999);
	int id = StrToInt(s);
	while ((intLi(s) == 0) || (id < 0) || (id > ID)) {
		printf("�� ����� �������� �����. ��������� ����:");
		s[0] = '\0'; gets_s(s, 999);
		id = StrToInt(s);
	}
	delet(baza, id);
}

void outs() {
	Pbd base = baza;
	printf("���� ������:\nID|�������� ����������|�����|����   |����|��������|����� ������|�������   |���������|��� |��� ���������|\n");
	while (base != NULL) {
		base->out();
		base = base->next;
	}
}

void ins() {
	Pbd one = new arsenal;


	char s[1000];

	printf("�������� ���������� (����� 19 ���� ����������):");
	s[0] = '\0'; gets_s(s, 999);
	s[19] = '\0';
	strcpy(one->name, s);

	printf("����� (����� 5 ���� ����������):");
	s[0] = '\0'; gets_s(s, 999);
	int y = StrToInt(s);
	while (intLi(s) == 0) {
		printf("�� ����� �������� �����. ��������� ����:");
		s[0] = '\0'; gets_s(s, 999);
		y = StrToInt(s);
	}
	s[5] = '\0';
	y = StrToInt(s);
	one->number = y % 100000;

	printf("���� (�����, ������� , ������� , ������):");
	s[0] = '\0'; gets_s(s, 999);
	myStrcmp(s, "�����");
	while (!myStrcmp(s, "�����") && !myStrcmp(s, "�����") && !myStrcmp(s, "�������") && !myStrcmp(s, "�������") && !myStrcmp(s, "�������") && !myStrcmp(s, "�������") && !myStrcmp(s, "������") && !myStrcmp(s, "������")) {
		printf("�� ����� �������� ����. ��������� ����:");
		s[0] = '\0'; gets_s(s, 999);
	}
	if (myStrcmp(s, "�����") || myStrcmp(s, "�����")) one->collor = blue; else
		if (myStrcmp(s, "�������") || myStrcmp(s, "�������")) one->collor = red; else
			if (myStrcmp(s, "�������") || myStrcmp(s, "�������")) one->collor = green; else
				if (myStrcmp(s, "������") || myStrcmp(s, "������")) one->collor = yellow;

	printf("���� (����� 4 ���� ����������):");
	s[0] = '\0'; gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("�� ����� �������� �����. ��������� ����:");
		s[0] = '\0'; gets_s(s, 999);
		y = StrToInt(s);
	}
	s[4] = '\0';
	y = StrToInt(s);
	one->damage = y % 10000;

	printf("�������� (����� 4 ���� ����������):");
	s[0] = '\0'; gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("�� ����� �������� �����. ��������� ����:");
		s[0] = '\0'; gets_s(s, 999);
		y = StrToInt(s);
	}
	s[4] = '\0';
	y = StrToInt(s);
	one->hp = y % 10000;

	printf("����� ������ (������ ����� ����� �� ����� 8 ��������):");
	s[0] = '\0'; gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("�� ����� �������� �����. ��������� ����:");
		s[0] = '\0'; gets_s(s, 999);
		y = StrToInt(s);
	}
	s[8] = '\0';
	one->runtime = atof(s);

	printf("����� ������������ (����� 2 ���� ����������; �������� ������� \"�������\", \"����������\", \"��������\"):");
	s[0] = '\0'; gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("�� ����� �������� �����. ��������� ����:");
		s[0] = '\0'; gets_s(s, 999);
		if (s[0] == '�') s[0] = '�';
		if (s[0] == '�') s[0] = '�';
		if ((myStrcmp(s, "�������") == 1) || (myStrcmp(s, "����������") == 1) || (myStrcmp(s, "��������") == 1)) {
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
		one->charge.status = "�������";
	}
	if (y <= 5) {
		one->what = 2;
		one->charge.news();
		one->charge.status = "��������";
	}
	outss:;

	printf("��������� � ������ (����� 9 ���� ����������):");
	s[0] = '\0'; gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("�� ����� �������� �����. ��������� ����:");
		s[0] = '\0'; gets_s(s, 999);
		y = StrToInt(s);
	}
	s[9] = '\0';
	y = StrToInt(s);
	one->cost = y % 1000000000;

	printf("��� � �� (����� 4 ���� ����������):");
	s[0] = '\0'; gets_s(s, 999);
	y = StrToInt(s);
	while ((intLi(s) == 0) || (y == -1)) {
		printf("�� ����� �������� �����. ��������� ����:");
		s[0] = '\0'; gets_s(s, 999);
		y = StrToInt(s);
	}
	s[4] = '\0';
	y = StrToInt(s);
	one->shock = y % 10000;

	printf("��� ��������� (����� 13 ���� ����������):");
	s[0] = '\0'; gets_s(s, 999);
	s[13] = '\0';
	if (myStrcmp(s, "") == 0) strcpy(one->owner, s);

	one->next = NULL;
	add(baza, one);
}

void inc() {
	Pbd one = new arsenal;
	strcpy(one->name, "��-105");
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
	strcpy(one->name, "��-12LT ������");
	one->collor = red;
	one->cost = 27000;
	one->damage = 25;
	one->hp = 100;
	one->number = 60;
	one->runtime = 7.39;
	one->charge.news();
	one->charge.status = "�������";
	one->what = 2;
	one->shock = 1000;
	strcpy(one->owner, "Mixno");
	one->next = NULL;
	add(baza, one);
}

void finds() {
	Pbd base = baza;
	int count = 0;
	printf("������� ����� �������� ������:");
	int com = -1,	 // ����� �������
		u = -20,	 // Just needed
		kolKom = 11;	 // ���������� ������ ����������
	char s[1000];
	com = -1;
	u = -20;
	printf("0 - ID\n");
	printf("1 - �������� ����������\n");
	printf("2 - �����\n");
	printf("3 - ����\n");
	printf("4 - ����\n");
	printf("5 - ��������\n");
	printf("6 - ����� ������\n");
	printf("7 - ����� ������������\n");
	printf("8 - ���������\n");
	printf("9 - ���\n");
	printf("10 - ��� ���������\n");
	s[0] = '\0'; gets_s(s, 999);
	u = StrToInt(s);
	while ((intLi(s) == 0) || (u == -1)) {
	repeats:;
		printf("�� ����� �������� ����� ��� ������. ��������� ����:");
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
				printf("�� ����� �������� �����. ��������� ����:");
				s[0] = '\0'; gets_s(s, 999);
				id = StrToInt(s);
			}
			printf("���� ������:\nID|�������� ����������|�����|����   |����|��������|����� ������|�������   |���������|��� |��� ���������|\n");
			while (base != NULL) {
				if (base->id == id) {
					count++; base->out();
				} base = base->next;
			}
			if (count == 0) printf("������� �� ������.\n");
		}
	if (u == 1) {
		printf("�������� ���������� (����� 19 ���� ����������):");
		s[0] = '\0'; gets_s(s, 999);
		s[19] = '\0';
		printf("���� ������:\nID|�������� ����������|�����|����   |����|��������|����� ������|�������   |���������|��� |��� ���������|\n");
		while (base != NULL) {
			if (myStrcmp(s, base->name)) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("������� �� ������.\n");
	}
	if (u == 2) {
		printf("����� (����� 5 ���� ����������):");
		s[0] = '\0'; gets_s(s, 999);
		int y = StrToInt(s);
		while (intLi(s) == 0) {
			printf("�� ����� �������� �����. ��������� ����:");
			s[0] = '\0'; gets_s(s, 999);
			y = StrToInt(s);
		}
		s[5] = '\0';
		y = StrToInt(s);
		y = y % 100000;
		printf("���� ������:\nID|�������� ����������|�����|����   |����|��������|����� ������|�������   |���������|��� |��� ���������|\n");
		while (base != NULL) {
			if (base->number == y) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("������� �� ������.\n");
	}
	if (u == 3) {
		printf("����:");
		s[0] = '\0'; gets_s(s, 999);
		myStrcmp(s, "�����");
		while (!myStrcmp(s, "�����") && !myStrcmp(s, "�����") && !myStrcmp(s, "�������") && !myStrcmp(s, "�������") && !myStrcmp(s, "�������") && !myStrcmp(s, "�������") && !myStrcmp(s, "������") && !myStrcmp(s, "������")) {
			printf("�� ����� �������� ����. ��������� ����:");
			s[0] = '\0'; gets_s(s, 999);
		}
		colors collor;
		if (myStrcmp(s, "�����") || myStrcmp(s, "�����")) collor = blue; else
			if (myStrcmp(s, "�������") || myStrcmp(s, "�������"))collor = red; else
				if (myStrcmp(s, "�������") || myStrcmp(s, "�������")) collor = green; else
					if (myStrcmp(s, "������") || myStrcmp(s, "������")) collor = yellow;
		printf("���� ������:\nID|�������� ����������|�����|����   |����|��������|����� ������|�������   |���������|��� |��� ���������|\n");
		while (base != NULL) {
			if (base->collor == collor) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("������� �� ������.\n");
	}
	if (u == 4) {
		printf("���� (����� 4 ���� ����������):");
		s[0] = '\0'; gets_s(s, 999);
		int y = StrToInt(s);
		while ((intLi(s) == 0) || (y == -1)) {
			printf("�� ����� �������� �����. ��������� ����:");
			s[0] = '\0'; gets_s(s, 999);
			y = StrToInt(s);
		}
		s[4] = '\0';
		y = StrToInt(s);
		y = y % 10000;
		printf("���� ������:\nID|�������� ����������|�����|����   |����|��������|����� ������|�������   |���������|��� |��� ���������|\n");
		while (base != NULL) {
			if (base->damage == y) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("������� �� ������.\n");
	}
	if (u == 5) {
		printf("�������� (����� 4 ���� ����������):");
		s[0] = '\0'; gets_s(s, 999);
		int y = StrToInt(s);
		while ((intLi(s) == 0) || (y == -1)) {
			printf("�� ����� �������� �����. ��������� ����:");
			s[0] = '\0'; gets_s(s, 999);
			y = StrToInt(s);
		}
		s[4] = '\0';
		y = StrToInt(s);
		y = y % 10000;
		printf("���� ������:\nID|�������� ����������|�����|����   |����|��������|����� ������|�������   |���������|��� |��� ���������|\n");
		while (base != NULL) {
			if (base->hp == y) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("������� �� ������.\n");
	}
	if (u == 6) {
		printf("����� ������ (������ ����� ����� �� ����� 8 ��������):");
		s[0] = '\0'; gets_s(s, 999);
		int y = StrToInt(s);
		while ((intLi(s) == 0) || (y == -1)) {
			printf("�� ����� �������� �����. ��������� ����:");
			s[0] = '\0'; gets_s(s, 999);
			y = StrToInt(s);
		}
		s[8] = '\0';
		double f = atof(s);
		printf("���� ������:\nID|�������� ����������|�����|����   |����|��������|����� ������|�������   |���������|��� |��� ���������|\n");
		while (base != NULL) {
			if (base->runtime == f) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("������� �� ������.\n");
	}
	if (u == 7) {
		printf("����� ������������ (����� 2 ���� ����������; �������� ������� \"�������\", \"����������\", \"��������\"):");
		s[0] = '\0'; gets_s(s, 999);
		int y = StrToInt(s);
		if (s[0] == '�') s[0] = '�';
		if (s[0] == '�') s[0] = '�';
		if ((myStrcmp(s, "�������") == 1) || (myStrcmp(s, "����������") == 1) || (myStrcmp(s, "��������") == 1)) {
			printf("���� ������:\nID|�������� ����������|�����|����   |����|��������|����� ������|�������   |���������|��� |��� ���������|\n");
			while (base != NULL) {
				if ((base->what == 2) && myStrcmp(s, base->charge.status)) {
					count++; base->out();
				} base = base->next;
			}
			if (count == 0) printf("������� �� ������.\n");
			goto outsa;
		}
		while ((intLi(s) == 0) || (y == -1)) {
			printf("�� ����� �������� �����. ��������� ����:");
			s[0] = '\0'; gets_s(s, 999);
			if (s[0] == '�') s[0] = '�';
			if (s[0] == '�') s[0] = '�';
			if ((myStrcmp(s, "�������") == 1) || (myStrcmp(s, "����������") == 1) || (myStrcmp(s, "��������") == 1)) {
				printf("���� ������:\nID|�������� ����������|�����|����   |����|��������|����� ������|�������   |���������|��� |��� ���������|\n");
				while (base != NULL) {
					if ((base->what == 2) && myStrcmp(s, base->charge.status)) {
						count++; base->out();
					} base = base->next;
				}
				if (count == 0) printf("������� �� ������.\n");
				goto outsa;
			}
			y = StrToInt(s);
		}
		s[2] = '\0';
		y = StrToInt(s);
		printf("���� ������:\nID|�������� ����������|�����|����   |����|��������|����� ������|�������   |���������|��� |��� ���������|\n");
		while (base != NULL) {
			if ((base->what == 1) && (base->charge.percent == y)) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("������� �� ������.\n");
	outsa:;
	}
	if (u == 8) {
		printf("��������� � ������ (����� 9 ���� ����������):");
		s[0] = '\0'; gets_s(s, 999);
		int y = StrToInt(s);
		while ((intLi(s) == 0) || (y == -1)) {
			printf("�� ����� �������� �����. ��������� ����:");
			s[0] = '\0'; gets_s(s, 999);
			y = StrToInt(s);
		}
		s[9] = '\0';
		y = StrToInt(s);
		y = y % 1000000000;
		printf("���� ������:\nID|�������� ����������|�����|����   |����|��������|����� ������|�������   |���������|��� |��� ���������|\n");
		while (base != NULL) {
			if (base->cost == y) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("������� �� ������.\n");
	}
	if (u == 9) {
		printf("��� � �� (����� 4 ���� ����������):");
		s[0] = '\0'; gets_s(s, 999);
		int y = StrToInt(s);
		while ((intLi(s) == 0) || (y == -1)) {
			printf("�� ����� �������� �����. ��������� ����:");
			s[0] = '\0'; gets_s(s, 999);
			y = StrToInt(s);
		}
		s[4] = '\0';
		y = StrToInt(s);
		y = y % 10000;
		printf("���� ������:\nID|�������� ����������|�����|����   |����|��������|����� ������|�������   |���������|��� |��� ���������|\n");
		while (base != NULL) {
			if (base->shock == y) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("������� �� ������.\n");
	}
	if (u == 10) {
		printf("��� ��������� (����� 13 ���� ����������):");
		s[0] = '\0'; gets_s(s, 999);
		s[13] = '\0';
		printf("���� ������:\nID|�������� ����������|�����|����   |����|��������|����� ������|�������   |���������|��� |��� ���������|\n");
		while (base != NULL) {
			if (myStrcmp(s, base->owner)) {
				count++; base->out();
			} base = base->next;
		}
		if (count == 0) printf("������� �� ������.\n");
	}
	else printf("\n");
	u = -1;
}


int main()
{
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD maxWindow = GetLargestConsoleWindowSize(out_handle); // ������ ������ �������� ���������� ����������� ����
	SMALL_RECT srctWindow = { 0, 0, maxWindow.X - 92, maxWindow.Y - 24 };
	SMALL_RECT minWindow = { 0, 0, 0, 0 };
	SetConsoleWindowInfo(out_handle, true, &minWindow);
	SetConsoleScreenBufferSize(out_handle, maxWindow);
	SetConsoleWindowInfo(out_handle, true, &srctWindow);


	SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������

	inc();

	int com = -1,	 // ����� �������
		u = -20,	 // Just needed
		kolKom = 5;	 // ���������� ������ ����������
	char s[1000];
	while (1) {
		com = -1;
		u = -20;
		printf("������� �������:\n");
		printf("0 - ������� ���� ������ �� �����\n");
		printf("1 - �������� �������\n");
		printf("2 - ����� �������\n");
		printf("3 - ������� �������\n");
		printf("4 - ������� ��� ����\n");
		s[0] = '\0'; gets_s(s, 999);
		u = StrToInt(s);
		while ((intLi(s) == 0) || (u == -1)) {
		repeat:;
			printf("�� ����� �������� ����� ��� ������. ��������� ����:");
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