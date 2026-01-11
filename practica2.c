#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

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
    int id_barco = 1;
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
                        for (int k = 0; k < flota[i].casillas; k++) {
                            tablero_conBarcos[fila][columna + k] = id_barco;
                            // printf("barco %s, colocado, con id:%d\n", flota[i].nombre, id_barco);
                        }
                    }
                    else
                    {
                        for (int k = 0; k < flota[i].casillas; k++) {
                            tablero_conBarcos[fila + k][columna] = id_barco;
                            // printf("barco %s, colocado, con id:%d\n", flota[i].nombre, id_barco);
                        }                            
                    }
                    colocado = 1;
                    id_barco++;
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
void coordenadasUser(int *fila, int *columna) {
    char coordenadas[4];
    char letra;
    int numero;

    while(1) {
        printf("Introdueix coordenades (ex: A5): ");
        scanf("%3s", coordenadas);
        while (getchar() != '\n');

        letra = toupper(coordenadas[0]);

        if (letra < 'A' || letra > 'j') {
            printf("Columna incorrecta (A-J)\n");
            continue;
        }
        
        numero = atoi(&coordenadas[1]);

        if (numero < 1 || numero > 10) {
            printf("Fila incorrecta (1-10)\n");
            continue;
        }

        *fila = numero - 1;
        *columna = letra - 'A';
        return;
    }
}

// Funcion para controlar las decisiones de SI o NO del usuario
char snUser(const char *mensaje) {
    char c;

    do {
        printf("%s", mensaje);
        scanf(" %c", &c);
        // Limpiar buffer
        while(getchar() != '\n');

        c = toupper(c);

        if (c == 'S' || c == 'N') {
            return c;
        }

        printf("Escriu S o N\n");
    } while (1);
}

// Funcion para elegir flota
int elegir_flota()
{
    printf("┌──────────────────────────────────┐\n");
    printf("│        Escull una flota          │\n");
    printf("├──────────────────────────────────┤\n");
    printf("│ 1 - L'Armada Vencible            │\n");
    printf("│ 2 - Els Brivalls                 │\n");
    printf("│ 3 - La Flotilla                  │\n");
    printf("└──────────────────────────────────┘\n");

    return enteroUser("Introdueix el número de la flota (1-3): ", 1, 3);
}

int disparoBarco(int fila, int columna, int tablero[10][10], int tablero_conBarcos[10][10]) {
    if (tablero[fila][columna] != 0) {
        printf("Ja has disparat aqui\n");
        return 0;
    }

    // Hay barco, si id > 0
    if (tablero_conBarcos[fila][columna] > 0) {
        printf("TOCAT!\n");
        tablero[fila][columna] = 1;

        int id_barco = tablero_conbarcos[fila][columna;]
        return id_barco;
    } else {
        printf("Aigua\n");
        tablero[fila][columna] = 2;
        return 0;
    }
}

// Funcion para comenzar la partida
void comenzarPartida(int tablero_conBarcos[10][10]) {
    printf("Comença la partida...\n");

    int tablero[10][10] = {0};
    int fila, columna;

    while (1) {
        printar_tablero(tablero);
        
        coordenadasUser(&fila, &columna);

        disparoBarco(fila, columna, tablero, tablero_conBarcos);

        

        continue;
    }


}

int barcoHundido(int id_barco, int tablero[10][10], int tablero_conBarcos[10][10]) {
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (tablero_conBarcos[i][j] == id_barco && tablero[i][j] != 1) {

            }
        }
    }
}

int main(void)
{
    srand(time(NULL));
    int tablero_conBarcos[10][10] = {0};

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

    int num_flota1 = sizeof(flota1) / sizeof(flota1[0]);
    int num_flota2 = sizeof(flota2) / sizeof(flota2[0]);
    int num_flota3 = sizeof(flota3) / sizeof(flota3[0]);

    int flota = elegir_flota();

    switch (flota)
    {
    case 1:
        printf("Preparant tauler de la flota 1... \n");

        if (snUser("Tauler generat. Vols fer trampes i veure el tauler generat? (S/N): ") == 'S') {
            tablero_barcos(tablero_conBarcos, flota1, num_flota1);
        }

        if (snUser("Vols generar un nou tauler? (S/N): ") == 'N')
        {
            tablero_barcos(tablero_conBarcos, flota1, num_flota1);

            comenzarPartida(tablero_conBarcos);
        }

        break;
    
    default:
        break;
    }

 
}