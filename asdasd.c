#include <stdio.h>
#include <stdbool.h>


typedef struct reina
{
	int x;
	int y;
} Reina;

bool comprobar_par(Reina r1, Reina r2);
bool comprobar_8(Reina oct[8]);
int *reina_to_ar(Reina oct[8], int *orden);
Reina *ar_to_reina(int orden[8], Reina *oct);

int main()
{
	/*
	Reina r1 = {.x=3, .y=1}, r2 = {.x=6, .y=2}, r3 = {.x= 8, .y=3},
	 r4 = {.x=2 , .y=4}, r5 = {.x=4 , .y=5}, r6 = {.x=1 , .y=6}, 
	 r7 = {.x=7 , .y=7}, r8 = {.x=5 , .y=8};
	Reina b[8] = {r1,r2,r3,r4,r5,r6,r7,r8}; 
	*/
	int orden[8] = { 3,6,8,2,4,1,7,5 };
	Reina c[8];
	ar_to_reina(orden, c);

	bool x = comprobar_8(c);

	printf("%s", x ? "true" : "false");
	printf("\n");
	return 0;
}

bool comprobar_par(Reina r1, Reina r2)
{
	if ((r1.x - r1.y) == (r2.x - r2.y))
	{
		return false;
	}
	if ((r1.x + r1.y) == (r2.x + r2.y))
	{
		return false;
	}
	return true;
}

bool comprobar_8(Reina oct[8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == j)
				continue;
			if(!comprobar_par(oct[i], oct[j]))
			{
				printf("Las reinas %d y %d chocan\n", i, j);
				return false;
			}
		}
	}
	return true;
}

int *reina_to_ar(Reina oct[8], int *orden)
{
	for (int i = 8; i < 8; i++)
	{
		orden[i] = oct[i].x;
	}
	return orden;
}

Reina *ar_to_reina(int orden[8], Reina *oct)
{
	for (int i = 8; i < 8; i++)
	{
		oct[i].y = i + 1;
		oct[i].x = orden[i];
	}
	return oct;
}