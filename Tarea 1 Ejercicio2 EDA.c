#include <stdio.h>

#define largo_arreglo 20

void potencia(int a, int b);
void division(int a, int b);
void fibo_menor(int a, int b);

void mayor_que(int b[]);
void promedio(int b[]);
void indicar_par(int b[]);

int main()
{
	int programa;
	printf("Escoger programa 1 o programa 2:");
	scanf("%d", &programa);
	switch(programa)
	{
		case 1: // ejercicio 2.1
			printf("Hola mundo\n");
			potencia(2, 4);
			potencia(3, 4);
			division(8, 2);
			division(21, 3);
			for (int i = 1; i < 9; i++)
			{
				fibo_menor(62, i);
			}
			break;
		case 2: ; // ejercicio 2.2 | ";" añadido porque manda error al declarar este int[] sin eso
			int b[largo_arreglo];
			printf("introducir arreglo de %d elementos\n", largo_arreglo);
			for(int i = 0; i < largo_arreglo; i++)
			{
				printf("Nro%d:", i+1);
				scanf("%d", &b[i]);
			}
			mayor_que(b);
			promedio(b);
			indicar_par(b);
			break;
	}
	return 0;
}

// funciones del ejercicio 2.1
void potencia(int a, int b)
{
	int result = 1;
	for(int i = 0; i < b; i++)
		result = result * a;
	printf("potencia de %d^%d = %d\n", a, b, result);
}

void division(int a, int b)
{
	float result = a/b;
	printf("division de %d/%d = %.4f\n", a, b, result);
}

void fibo_menor(int a, int b)
{
	int fibo;
	int temp;
	
	if (a<=b)
		fibo = a;
	else
		fibo = b;
	
	if (fibo == 1)
		temp = 0;
	else if (fibo == 2)
		temp = 1;
	else
	{
		int fib1 = 0;
		int fib2 = 1;
		
		for(int i = 0; i < fibo - 2; i++)
		{
			temp = fib1 + fib2;
			fib1 = fib2;
			fib2 = temp;
		}
	}
	
	printf("el termino Nro %d de la secuencia fibonacci es: %d\n", fibo, temp); 
}

// funciones del ejercicio 2.2
void mayor_que(int b[])
{
	int max;
	int cont = 0;
	printf("Buscar numeros mayores a:");
	scanf("%d", &max);
	for(int i = 0; i < largo_arreglo; i++)
	{
		if (b[i] > max)
		{
			cont++;
		}
	}
	printf("Hay %d elementos que son mayores a %d\n", cont, max);
}

void promedio(int b[])
{
	int prom = 0;
	for (int i = 0; i < largo_arreglo; i++)
	{
		prom += b[i];
	}
	float resultado = prom / largo_arreglo;
	printf("El promedio de los elementos es: %f\n", resultado);
}

void indicar_par(int b[])
{
	int menu;
	int revisar;
	printf("Revisar paridad del numero:");
	scanf("%d", &menu);
	switch( menu )
	{
		case 1:
			revisar = 1;
			break;
		case 2:
			revisar = 2;
			break;
		case 3:
			revisar = 3;
			break;
		case 4:
			revisar = 4;
			break;
		case 5:
			revisar = 5;
			break;
		case 6:
			revisar = 6;
			break;
		case 7:
			revisar = 7;
			break;
		case 8:
			revisar = 8;
			break;
		case 9:
			revisar = 9;
			break;
		case 10:
			revisar = 10;
			break;
		case 11:
			revisar = 11;
			break;
		case 12:
			revisar = 12;
			break;
		case 13:
			revisar = 13;
			break;
		case 14:
			revisar = 14;
			break;
		case 15:
			revisar = 15;
			break;
		case 16:
			revisar = 16;
			break;
		case 17:
			revisar = 17;
			break;
		case 18:
			revisar = 18;
			break;
		case 19:
			revisar = 19;
			break;
		case 20:
			revisar = 20;
			break;
		default:
			printf("Numero Erroneo");
			break;
	}
	revisar--;
	if (b[revisar] % 2 == 0)
		printf("%d es par", b[revisar]);
	else
		printf("%d es impar", b[revisar]);
}