#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estructura del barco para almacenar su informacion
struct barco
{
    char nombre[20];
    int cantidad;
    int casillas;
};

// Funcion para printar el tablero 
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

// Funcion para printar el tablero con los barcos ya colocados de forma random
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

// Funcion para pedir numeros enteros al usuario
int enteroUser(const char *mensaje, int min, int max) {
    int valor;
    int entradaUser;

    do {
        printf("%s", mensaje);
        entradaUser = scanf("%d", &valor);

        // Limpiar buffer
        while (getchar() != '\n');

        if (entradaUser == 1 && valor >= min && valor <= max)
        {
            return valor;
        }

        printf("Número no valido\n");
    } while (1);
}

// Funcion para pedir texto al usuario (SOLAMENTE PARA LETRAS, PALABRAS Y COORDENADAS)
void charUser(const char *mensaje, char *texto, int tam) {
    printf("%s", mensaje);
    scanf("%19s", texto);
    while (getchar() != '\n');
}

// Funcion para controlar las decisiones de SI o NO del usuario
char snUser(const char *mensaje) {
    char c;

    do {
        printf("%s", mensaje);
        scanf(" %c", &c);
        // Limpiar buffer
        if (c == 'S' || c == 's')
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
    int num_flota2 = sizeof(flota2) / sizeof(flota2[0]);
    int num_flota3 = sizeof(flota3) / sizeof(flota3[0]);

 
}