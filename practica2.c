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
        // printf("numeros barcos %d\n", num_barcos);
        // printf("Barcos restantes %d\n", num_barcos - i);
        for (int j = 0; j < flota[i].cantidad; j++)
        {
            // printf("nombre de barco: %s, cantidad total: %d, cantidad restante: %d\n", flota[i].nombre, flota[i].cantidad, flota[i].cantidad - j);
            int colocado = 0;
            
            while (!colocado) {
                int fila = rand() % 10;
                int columna = rand() % 10;
                int orientacion = rand() % 2; // 0 = horizontal, 1 = vertical
                int valido = 1;

                if (orientacion == 0)
                {
                    // Comprovar si cabe el barco en el tablero
                    if (columna + flota[i].casillas > 10)
                    {
                        valido = 0;
                    }
                    else
                    {
                        for (int k = 0; k < flota[i].casillas; k++)
                        {
                            if (tablero_conBarcos[fila][columna + k] != 0)
                            {
                                valido = 0;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    if (fila + flota[i].casillas > 10)
                    {
                        valido = 0;
                    }
                    else
                    {
                        for (int k = 0; k < flota[i].casillas; k++)
                        {
                            if (tablero_conBarcos[fila + k][columna] != 0)
                            {
                                valido = 0;
                                break;
                            }
                        }
                    }
                }

                if (valido)
                {
                    if (orientacion == 0)
                    {
                        for (int k = 0; k < flota[i].casillas; k++)
                            tablero_conBarcos[fila][columna + k] = 1;
                            printf("barco %s, colocado\n", flota[i].nombre);
                    }
                    else
                    {
                        for (int k = 0; k < flota[i].casillas; k++)
                            tablero_conBarcos[fila + k][columna] = 1;
                        printf("barco %s, colocado\n", flota[i].nombre);
                    }
                    colocado = 1;
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

void entradaUser(const char *mensaje, chat *User) {
    printf("%s", mensaje);

    
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
    int num_flota2 = sizeof(flota2) / sizeof(flota2[0]);
    int num_flota3 = sizeof(flota3) / sizeof(flota3[0]);

    // Tablero sin barcos
    // printar_tablero(tablero);

    // Tablero con barcos
    // tablero_barcos(tablero_conBarcos, flota1, num_flota1); //Se muestra correctamente

    int hecho = 0;  

    do{
        printf("┌──────────────────────────────────┐\n");
        printf("│        Escull una flota          │\n");
        printf("├──────────────────────────────────┤\n");
        printf("│ 1 - L'Armada Vencible            │\n");
        printf("│ 2 - Els Brivalls                 │\n");
        printf("│ 3 - La Flotilla                  │\n");
        printf("└──────────────────────────────────┘\n");
        printf("Introdueix el número de la flota (1-3): ");

        int opcionCorrecta = 0;
        int intValue;
        while (!opcionCorrecta)
        {
            scanf("%d", &intValue);
            if (intValue >= 1 && intValue <= 3)
            {
                switch (intValue)
                {
                case 1:
                    printar_tablero(tablero);
                    tablero_barcos(tablero_conBarcos, flota1, num_flota1);
                    break;

                case 2:
                    printar_tablero(tablero);
                    tablero_barcos(tablero_conBarcos, flota2, num_flota2);
                    break;

                case 3:
                    printar_tablero(tablero);
                    tablero_barcos(tablero_conBarcos, flota3, num_flota3);
                    break;

                default:
                    break;
                }
                opcionCorrecta = 1;
            }
            else
            {
                printf("Escull la opció 1, 2 o 3: ");
                while (getchar() != '\n')
                    ;
            }
        }

    } while (hecho == 0);
    {
         while (getchar() != '\n')
                    ;
    }
}