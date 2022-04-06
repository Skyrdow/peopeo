#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Laberinto
{
	int n;
	int m;
	char **matriz;
} laberinto;

typedef struct Coordenada
{
	int x;
	int y;
} coord;

typedef struct Camino
{
	int largo;
	coord *lista_coords;
	
} camino;

typedef struct Conj_Caminos
{
	int largo;
	camino *lista_caminos;
} lista_caminos;


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

coord buscar_e(laberinto lab)
{
	coord res;
	for (int i = 0; i < lab.n; i++)
	{
		for (int j = 0; j < lab.m; j++)
		{
			if(lab.matriz[i][j] == 'e')
			{
				res.x = i;
				res.y = j;
				return res;
			}
		}
	}
}

camino crear_camino()
{
	camino cam;
	cam.largo = 1;
	cam.lista_coords = malloc(sizeof(coord));
}

camino camino_append(camino viejo, coord agregar)
{
	camino res;
	res.largo = viejo.largo + 1;
	res.lista_coords = malloc(sizeof(coord) * res.largo);
	res.lista_coords[res.largo] = agregar;
	return res;
}

int *buscar(laberinto lab_original)
{
	coord comienzo = buscar_e(lab_original);
	laberinto lab_recorrido = copiar_lab(lab_original);

	camino *caminos_recorridos;
	bool camino_encontrado = false, comprobando_camino = true,
			camino_viable = true;
	bool dir[4];
	int x,y;

	while (!camino_encontrado)
	{

		while (comprobando_camino)
		{
			// izq
			if (y == 0)
				if (lab_recorrido.matriz[x][y-1] == 'x')
					dir[0] = false;
			// arriba
			if (x == 0) 
				if (lab_recorrido.matriz[x-1][y] == 'x')
					dir[1] = false;
			// der
			if (y == lab_original.m)
				if (lab_recorrido.matriz[x][y+1] == 'x')
					dir[2] = false;
			// abajo
			if (x == lab_original.n)
				if (lab_recorrido.matriz[x+1][y] == 'x')
					dir[3] = false;
		}
	}
}

int main(int argc, char *argv[])
{
	FILE *fp = abrir_archivo(argv[1]);
	laberinto lab = leer_laberinto(fp);
}