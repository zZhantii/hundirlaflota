#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct barco
{
    char nombre[20];
    int cantidad;
    int casillas;
};

void printar_tablero(int tablero[10][10])
{
    printf("   | A B C D E F G H I J\n --+---------------------\n");

    for (int i = 0; i < 10; i++)
    {
        printf("%2d | ", i + 1);
        for (int j = 0; j < 10; j++)
        {
            printf("%d ", tablero[i][j]);
        }
        printf("\n");
    }
}

void tablero_barcos(int tablero_conBarcos[10][10], struct barco flota[], int num_barcos)
{
    

    for (int i = 0; i < num_barcos; i++)
    {
        for (int j = 0; j < flota[i].cantidad; j++)
        {
            int correctoFila = 0;
            int correctoColumna = 0;

            int fila = 0;
            int columna = 0;
            int orientacion = 0;
            do
            {

                fila = rand() % 10;
                columna = rand() % 10;
                orientacion = rand() % 2; // 0 = horizontal, 1 = vertical

                if (orientacion == 1)
                {
                    if (fila + flota[i].casillas <= 10)
                    {
                        correctoFila = 1;
                    }
                }
                else
                {
                    if (columna + flota[i].casillas <= 10)
                    {
                        correctoColumna = 1;
                    }
                }

            } while (correctoFila == 0 && correctoColumna == 0);

            if (orientacion == 0)
            {
                // Horizontal
                for (int k = 0; k < flota[i].casillas; k++)
                {
                    if (tablero_conBarcos[][] != 0) {
                        
                    }
                    tablero_conBarcos[fila][columna + k] = 1;
                }
            }
            else
            {
                // vertical
                for (int p = 0; p < flota[i].casillas; p++)
                {
                    tablero_conBarcos[fila + p][columna] = 1;
                }
            }
        }
    }

    printf("   | A B C D E F G H I J\n --+---------------------\n");

    for (int i = 0; i < 10; i++)
    {
        printf("%2d | ", i + 1);
        for (int j = 0; j < 10; j++)
        {
            printf("%d ", tablero_conBarcos[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    srand(time(NULL));

    struct barco flota1[] = {
        {"portaavions", 1, 5},
        {"cuirassat", 1, 4},
        {"destructors", 2, 3},
        {"fragates", 2, 2},
        {"submarins", 3, 1}};

    struct barco flota2[] =
        {
            {"cuirassat", 1, 4},
            {"destructors", 2, 3},
            {"fragates", 3, 2},
            {"submarins", 4, 1}};

    struct barco flota3[] =
        {
            {"destructors", 2, 3},
            {"fragates", 3, 2},
            {"submarins", 4, 1}};

    int tablero[10][10] = {0};
    int tablero_conBarcos[10][10] = {0};

    int num_flota1 = sizeof(flota1) / sizeof(flota1[0]);

    // printar_tablero(tablero);
    tablero_barcos(tablero_conBarcos, flota1, num_flota1);

    // int num_tipos = sizeof(flota1) / sizeof(flota1[0]);

    // for (int i = 0; i < num_tipos; i++)
    // {
    //     printf("Tipo: %s\n", flota1[i].nombre);
    //     printf("Cantidad: %d\n", flota1[i].cantidad);
    //     printf("Casillas: %d\n", flota1[i].casillas);
    // }

    // int hecho = 0;

    // do{
    //     printf("┌──────────────────────────────────┐\n");
    //     printf("│        Escull una flota          │\n");
    //     printf("├──────────────────────────────────┤\n");
    //     printf("│ 1 - L'Armada Vencible            │\n");
    //     printf("│ 2 - Els Brivalls                 │\n");
    //     printf("│ 3 - La Flotilla                  │\n");
    //     printf("└──────────────────────────────────┘\n");
    //     printf("Introdueix el número de la flota (1-3): ");

    //     while (!hecho)
    //     {
    //         scanf("%d", &intValue);
    //         if (intValue >= 1 && intValue <= 3)
    //         {

    //             hecho = 1;
    //         }
    //         else
    //         {
    //             printf("Escull la opció 1, 2 o 3: ");
    //             while (getchar() != '\n')
    //                 ;
    //         }
    //     }
    // } while (condition)
    // {
    //     /* code */
    // }
}