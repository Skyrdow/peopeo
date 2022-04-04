#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
 
// Por algún motivo no funciona con el ejemplo 3

int buscar(int n, int m, char matriz[n][m], int x, int y, int direccion_anterior, int acum, int camino[n*m], int *ultimo_acum, int camino_v[n*m][2]);
void buscar_e(int n, int m, char matriz[n][m], int *res);
FILE *abrir_archivo(char *nom);
void leer_dim(int *n, int *m, FILE *fp);
void leer_matriz(int n, int m, char matriz[n][m], FILE *fp);
void preparar_busqueda(char *nom_archivo);
void imprimir_matriz(int n, int m, char matriz[n][m]);

int buscar(int n, int m, char matriz[n][m], int x, int y, int direccion_anterior, int acum, int camino[n*m], int *ultimo_acum, int camino_v[n*m][2])
{
	if (acum >= n*m) // si sobrepasa el paso numero N*M se descarta
		return 0;
	camino_v[acum][0] = x;
	camino_v[acum][1] = y;
	camino[acum] = direccion_anterior;
	acum++;

	if (matriz[x][y] == 's')
	{
		// es necesario guardar este valor para imprimir correctamente el camino
		*ultimo_acum = acum;
 		return 1;
	}
	
	bool b_dir[4] = { true, true, true, true}; // 0: L 1: U 2: R 3: D
	
	if(direccion_anterior != -1) // -1 si es el primer paso
	{
		direccion_anterior = (direccion_anterior + 2) % 4 ; // obtener la dirección opuesta
		b_dir[direccion_anterior] = false; // no buscar en la dirección anterior
	}
	
	// izq
	if (y <= 0 || matriz[x][y-1] == 'x')
		b_dir[0] = false;
	// arriba
	if (x <= 0 || matriz[x-1][y] == 'x')
		b_dir[1] = false;
	// der
	if (y >= (m-1) || matriz[x][y+1] == 'x')
		b_dir[2] = false;
	// abajo
	if (x >= (n-1) || matriz[x+1][y] == 'x')
		b_dir[3] = false;
	
	int buscador;
	
	if(b_dir[0])
		if((buscador = buscar(n, m, matriz, x, y-1, 0, acum, camino, ultimo_acum, camino_v)) == 1)
			return buscador;
	if(b_dir[1])
		if((buscador = buscar(n, m, matriz, x-1, y, 1, acum, camino, ultimo_acum, camino_v)) == 1)
			return buscador;
	if(b_dir[2])
		if((buscador = buscar(n, m, matriz, x, y+1, 2, acum, camino, ultimo_acum, camino_v)) == 1)
			return buscador;
	if(b_dir[3])
		if((buscador = buscar(n, m, matriz, x+1, y, 3, acum, camino, ultimo_acum, camino_v)) == 1)
			return buscador;
	return 0; // si no hay camino retorna 0
}


void buscar_e(int n, int m, char matriz[n][m], int *res)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (matriz[i][j] == 'e')
			{
				
				res[0] = i;
				res[1] = j;
			}
		}
	}
}

FILE *abrir_archivo(char* nom)
{
	FILE *archp;
	if (archp = fopen(nom, "r"))
	{
		printf("Archivo leído correctamente\n");
		return archp;
	}
	printf("Hubo un problema al leer el archivo\n");
	return NULL;
}

void leer_dim(int *n, int *m, FILE *fp)
{
	fscanf(fp, "%d %d", n, m);
	
	printf("Dimensiones: N:%d M:%d\n", *n, *m);
}

void leer_matriz(int n, int m, char matriz[n][m], FILE *fp)
{
	char caracter;
	char *archivo;
	for (int i=0; i<n; i++)
	{
		fgets(matriz[i],m+1, fp);
		if(strlen(matriz[i]) < m-1)
			i--;
	}
}

void imprimir_matriz(int n, int m, char matriz[n][m])
{
	
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<m; j++)
		{
			printf("%c", matriz[i][j]);
		}
		printf("\n");
	}
}

void preparar_busqueda(char *nom_archivo)
{
	FILE *fp = abrir_archivo(nom_archivo);
	if(fp == NULL)
		return; // error al abrir aborta la ejecución
	
	int n,m;
	int *pn = &n, *pm = &m;
	leer_dim(pn, pm, fp);
	
	char matriz[n][m];

	// leer de archivo
	leer_matriz(n,m, matriz, fp);
	fclose(fp);
	
	// ver la matriz en consola
	imprimir_matriz(n,m,matriz);
	
	// datos necesarios para buscar
	int ultimo_acum;
	int comienzo[2];
	buscar_e(n, m, matriz, comienzo);
	printf("Punto de partida: (%d, %d)\n", comienzo[0], comienzo[1]);
	int camino[n*m];
	int camino_v[n*m][2];
	// buscar

	struct timespec begin, end;
	clock_gettime(CLOCK_REALTIME, &begin);
	int res = buscar(n, m, matriz, comienzo[0], comienzo[1], -1, 0, camino, &ultimo_acum, camino_v);
	

	clock_gettime(CLOCK_REALTIME, &end);

	long seconds = end.tv_sec - begin.tv_sec;
	long nanoseconds = end.tv_nsec - begin.tv_nsec;
	double elapsed = seconds + nanoseconds*1e-9;

	printf("tiempo iterativo %.8f\n", elapsed);
	// mostrar camino
	if (res == 1)
	{
		printf("Camino a la salida exitosamente encontrado: \n");
	
		for (int i = 0; i < (ultimo_acum); i++)
		{
			if (camino[i] == -1)
				printf("(E"); // entrada
			if (camino[i] == 0)
				printf("L");
			if (camino[i] == 1)
				printf("U");
			if (camino[i] == 2)
				printf("R");
			if (camino[i] == 3)
				printf("D");
		}
		printf(")\n");
	}
	else
	{
		printf("Camino no encontrado | no existe\n");
		return;
	}


	for (int e=0; e < ultimo_acum; e++)
	{
		printf("(%d, %d)", camino_v[e][0], camino_v[e][1]);
	}
	
	char vis;
	printf("Visualizar?: (y/n)\n");
	vis = getc(stdin);
	if(vis == 'y' || vis == 'Y')
	{
		for (int e=0; e < ultimo_acum; e++)
		{
			for (int i=0; i<n; i++)
			{
				for (int j=0; j<m; j++)
				{
					if (i == camino_v[e][0] && j == camino_v[e][1])
						printf(" ");
					else
						printf("%c", matriz[i][j]);
				}
				printf("\n");
			}
			printf("\n");
		}
	}
}

int main(int argc, char *argv[])
{
	preparar_busqueda(argv[1]);
}