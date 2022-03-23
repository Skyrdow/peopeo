#include <stdio.h>
#include <time.h>

#define ITERAR 50

unsigned long long int fibonashe_recursivo(unsigned long long int fib);
unsigned long long int fibonashe_iterativo(int entrada);

int main() // 0 1 1 2 3 5
{
	struct timespec begin, end;
	clock_gettime(CLOCK_REALTIME, &begin);

	for (int i = 1; i < ITERAR; i++)
	{
		fibonashe_iterativo(i);
	}

	clock_gettime(CLOCK_REALTIME, &end);

	long seconds = end.tv_sec - begin.tv_sec;
	long nanoseconds = end.tv_nsec - begin.tv_nsec;
	double elapsed = seconds + nanoseconds*1e-9;

	printf("tiempo iterativo %.3f\n", elapsed);

	clock_gettime(CLOCK_REALTIME, &begin);

	for (int i = 1; i < ITERAR; i++)
	{
		printf("%llu \n", fibonashe_recursivo(i));
	}

	clock_gettime(CLOCK_REALTIME, &end);
	seconds = end.tv_sec - begin.tv_sec;
	nanoseconds = end.tv_nsec - begin.tv_nsec;
	elapsed = seconds + nanoseconds*1e-9;
	printf("tiempo recursivo %.3f\n", elapsed);
}

unsigned long long int fibonashe_recursivo(unsigned long long int fib) // 0 1 1 2 3 5 8
{
	if (fib == 1)
		return 0;
	if (fib == 2)
		return 1;
	return fibonashe_recursivo(fib-1) + fibonashe_recursivo(fib-2);
}

unsigned long long int fibonashe_iterativo(int entrada)
{
	unsigned long long int fib1=0, fib2=1, acum=0;
	switch (entrada)
	{
		case 1:
			acum = 0;
			break;
		case 2:
			acum = 1;
			break;
		default:
			for (int i = 0; i < entrada-2; i++)
			{
				acum = fib1 + fib2;
				fib1 = fib2;
				fib2 = acum;
			}
			break;
	}

	printf("%llu\n", acum);

}