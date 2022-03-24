#include <stdio.h>
#include <stdlib.h>

struct Estudiante
{
	char nombre[10];
	int nota1;
	int nota2;
} e[4];
int main()
{
	char str[30];
	FILE *fp;
	fp = fopen("notas.txt", "r");
	while(fscanf(fp, "%s %d %d", e[0].nombre, &e[0].nota1, &e[0].nota2) != EOF)
	{
		printf("%s, %d, %d\n",  e[0].nombre, e[0].nota1, e[0].nota2);
	}
	fclose(fp);
}