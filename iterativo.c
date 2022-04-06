#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Laberinto
{
	int n;
	int m;
	char **matriz;
} laberinto;

laberinto crear_lab(int n, int m)
{
	laberinto lab;
	lab.n = n;
	lab.m = m;
	lab.matriz = malloc(sizeof(char *) * n);
	for (int i = 0; i < n; i++)
	{
		lab.matriz[i] = malloc(sizeof(char)*m);
	}
	return lab;
}

laberinto copiar_lab(laberinto copiar)
{
	laberinto lab;
	lab.n = copiar.n;
	lab.m = copiar.m;
	for (int i = 0; i < lab.n; i++)
	{
		for (int j = 0; j < lab.m; j++)
		{
			lab.matriz[i][j] = copiar.matriz[i][j];
		}
	}
	return lab;
}

void imprimir_laberinto(laberinto lab)
{

	for (int i = 0; i < lab.n; i++)
	{
		for (int j = 0; j < lab.m; j++)
		{
			printf("%c",lab.matriz[i][j]);
		}
		printf("\n");
	}
}

int *buscar()
{

}

FILE *abrir_archivo(char *nom)
{
	FILE *fp = fopen(nom, "r");
	if( fp == NULL)
	{
		printf("Problema con el archivo\n");
		return NULL;
	}
	else
	{
		printf("Archivo leido\n");
		return fp;
	}
}

laberinto leer_laberinto(FILE *fp)
{
	int n, m;
	fscanf(fp, "%d %d\n", &n, &m);
	laberinto lab = crear_lab(n, m);
	printf("n:%d m:%d\n", lab.n, lab.m);

	for (int i=0; i<n; i++)
	{
		fgets(lab.matriz[i],m+1, fp);
		if(strlen(lab.matriz[i]) < m-1)
			i--;
	}

	imprimir_laberinto(lab);
}

int main(int argc, char *argv[])
{
	FILE *fp = abrir_archivo(argv[1]);
	laberinto lab = leer_laberinto(fp);
}