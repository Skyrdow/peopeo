#include <stdio.h>
#define filas 3
#define columnas 4

int *Leer(int M[filas][columnas]){
    int i,j,temp;
    for (i = 0; i < filas; i++){
        for (j = 0; j < columnas; j++){
            printf("Inserte el valor de la fila %d, columna %d: ", (i+1), (j+1));
            scanf("%d", &temp);
			M[i][j]=temp;
        }
    }
    printf("%d", M[0][0]);
    return &M[0][0];
}

int main(){
    int M[filas][columnas];
    int *dir = Leer(M);
}