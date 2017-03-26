#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct bd {
	char *name;
	int count;

	void add(char *names)
	{
		count++;
		name = names;
	}

	void myprint()
	{
			printf("%s%d\n", name, count);
	}
};




int main()
{
	struct bd *tryBD = { "name", 0; };
	tryBD[tryBD[0].count+1].add("Hui");
	tryBD[2].add("Huinya");
	tryBD[3].add("Huiyovina");

	for(int q=0;q<tryBD[0].count;q++) tryBD[q].myprint();
	return 0;
}

