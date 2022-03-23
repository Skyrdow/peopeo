#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L_PROD 10

int cant_prod = 0;

struct producto
{
	char nombre[15];
	int precio;
	int stock;
} productos[L_PROD];

void lista_prod();
void crear_prod(char nom[15], int precio, int stock);
void buscar_prod(char nom[15]);
void modificar_prod(int indice);

int main()
{
	char nom_menu[15];
	int precio_menu, stock_menu, indice_menu, opcion = 0;
	while (opcion != 5)
	{
		printf("\n---- Menu ----\n1. Lista de productos\n2. Añadir un producto\n3. Buscar un producto\n4. Modificar un producto\n5. Salir\n");
		scanf("%d", &opcion);
		printf("\n");
		switch(opcion)
		{
			case 1:
				lista_prod();
				break;
			case 2:
				printf("Nombre: ");
				scanf("%s", nom_menu);

				printf("Precio: ");
				scanf("%d", &precio_menu);
				
				printf("Stock: ");
				scanf("%d", &stock_menu);
				
				crear_prod(nom_menu, precio_menu, stock_menu);
				printf("---- Producto creado ----\n\n");
				break;
			case 3:
				printf("Nombre: ");
				scanf("%s", nom_menu);
				buscar_prod(nom_menu);
				break;
			case 4:
				lista_prod();
				printf("\nÍndice del producto a modificar: ");
				scanf("%d", &indice_menu);
				modificar_prod(indice_menu);
				break;
		}
	}
}

void lista_prod()
{
	if (cant_prod == 0)
		printf("No hay productos disponibles\n");
	else
	{
		printf("---- Lista de productos ----\n");
		for (int i = 0; i < cant_prod; i++)
		{
			printf("%d. %s $%d, stock:%d\n", i+1, productos[i].nombre, 
				productos[i].precio, productos[i].stock);
		}	
	}
	printf("\n");
}

void crear_prod(char nom[15], int precio, int stock)
{
	strcpy(productos[cant_prod].nombre, nom);
	productos[cant_prod].precio = precio;
	productos[cant_prod].stock = stock;
	cant_prod++;
}

void buscar_prod(char nom[15])
{
	for (int i = 0; i < cant_prod; i++)
	{
		if (strcmp(nom, productos[i].nombre) == 0)
		{
			printf("---- Producto encontrado ----\n%d. %s $%d, stock:%d\n", i+1, productos[i].nombre, 
				productos[i].precio, productos[i].stock);
			return;
		}
	}
	printf("---- Producto %s no encontrado ----\n", nom);
}

void modificar_prod(int i)
{
	i--;
	printf("---- Se esta modificando el producto: ----\n%d. %s $%d, stock:%d\n", i+1, productos[i].nombre, 
		productos[i].precio, productos[i].stock);
	printf("Nombre: ");
	scanf("%s", productos[i].nombre);

	printf("Precio: ");
	scanf("%d", &productos[i].precio);
	
	printf("Stock: ");
	scanf("%d", &productos[i].stock);
	printf("---- Producto modificado: ----\n%d. %s $%d, stock:%d\n", i+1, productos[i].nombre, 
		productos[i].precio, productos[i].stock);
}