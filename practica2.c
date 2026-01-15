/*
 * ======================================================================
 * Enfonsar la flota
 * ======================================================================
 *
 * Descripción: Este programa implementa un juego de hundir la flota
 * donde el usuario elige una flota y juega contra un tablero generado
 * aleatoriamente. Incluye funciones para colocar barcos, disparar y
 * verificar victorias.
 *
 * Autor: Santiago Lozada Benitez
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * ======================================================================
 * ESTRUCTURAS Y CONSTANTES GLOBALES
 * ======================================================================
 */

/**
 * @brief Estructura que representa un barco en la flota.
 */
struct barco {
  char nombre[20]; // Nombre del barco
  int cantidad;    // Número de mismo tipo de barco
  int casillas;    // Longitud del barco
};

// Flotas predefinidas
struct barco flota1[] = {{"portaavions", 1, 5},
                         {"cuirassat", 1, 4},
                         {"destructors", 2, 3},
                         {"fragates", 2, 2},
                         {"submarins", 3, 1}};

struct barco flota2[] = {{"cuirassat", 1, 4},
                         {"destructors", 2, 3},
                         {"fragates", 3, 2},
                         {"submarins", 4, 1}};

struct barco flota3[] = {
    {"destructors", 2, 3}, {"fragates", 3, 2}, {"submarins", 4, 1}};

// tamaños de las flotas
int num_flota1 = sizeof(flota1) / sizeof(flota1[0]);
int num_flota2 = sizeof(flota2) / sizeof(flota2[0]);
int num_flota3 = sizeof(flota3) / sizeof(flota3[0]);

/*
 * ======================================================================
 * FUNCIONES DE UTILIDAD
 * ======================================================================
 */

/**
 * @brief Imprime el tablero de la partida
 *
 * @param tablero Tablero general de la partida
 */

void printar_tablero(int tablero[10][10]) {
  printf("   | A B C D E F G H I J\n --+---------------------\n");

  for (int i = 0; i < 10; i++) {
    printf("%2d | ", i + 1);
    for (int j = 0; j < 10; j++) {
      printf("%d ", tablero[i][j]);
    }
    printf("\n");
  }
}

/**
 * @brief Imprime el tablero de barcos de la partida
 *
 * @param tablero_conBarcos Tablero con los barcos generados aleatoriamente
 */

void printar_tablero_barcos(int tablero_conBarcos[10][10]) {
  printf("   | A B C D E F G H I J\n --+---------------------\n");

  for (int i = 0; i < 10; i++) {
    printf("%2d | ", i + 1);
    for (int j = 0; j < 10; j++) {
      printf("%d ", tablero_conBarcos[i][j]);
    }
    printf("\n");
  }
}

/**
 * @brief Coloca los barcos de forma aleatoria en el tablero y lo imprime
 *
 * @param tablero_conBarcos Tablero con los barcos generados aleatoriamente
 * @param flota Array de los barcos
 * @param num_flota Numero de barcos de la array
 */

void tablero_barcos(int tablero_conBarcos[10][10], struct barco flota[],
                    int num_barcos) {
  int id_barco = 1;

  for (int i = 0; i < num_barcos; i++) {
    for (int j = 0; j < flota[i].cantidad; j++) {
      int colocado = 0;

      while (!colocado) {
        int fila = rand() % 10;
        int columna = rand() % 10;
        int orientacion = rand() % 2; // 0 = horizontal, 1 = vertical
        int valido = 1;

        int fila_ini, fila_fin, col_ini, col_fin;

        // horizontal
        if (orientacion == 0) {
          if (columna + flota[i].casillas > 10) {
            valido = 0;
          }

          fila_ini = fila - 1;
          fila_fin = fila + 1;
          col_ini = columna - 1;
          col_fin = columna + flota[i].casillas;
        } else // vertical
        {

          if (fila + flota[i].casillas > 10) {
            valido = 0;
          }

          fila_ini = fila - 1;
          fila_fin = fila + flota[i].casillas;
          col_ini = columna - 1;
          col_fin = columna + 1;
        }

        // doble for para comprobar el alrededor de los barcos y evitar se
        // sobrepongan
        for (int r = fila_ini; r <= fila_fin && valido; r++) {
          for (int c = col_ini; c <= col_fin; c++) {
            if (r >= 0 && r < 10 && c >= 0 && c < 10) {
              if (tablero_conBarcos[r][c] != 0) {
                valido = 0;
                break;
              }
            }
          }
        }

        if (valido) {
          if (orientacion == 0) {
            for (int k = 0; k < flota[i].casillas; k++) {
              tablero_conBarcos[fila][columna + k] = id_barco;
            }
          } else {
            for (int k = 0; k < flota[i].casillas; k++) {
              tablero_conBarcos[fila + k][columna] = id_barco;
            }
          }
          colocado = 1;
          id_barco++;
        }
      }
    }
  }
}

/**
 * @brief Solicita al usuario un número entero
 *
 * @param mensaje Texto a mostrar al usuario
 * @param min Valor mínimo
 * @param max Valor máximo
 */

int enteroUser(const char *mensaje, int min, int max) {
  int valor;
  int entradaUser;

  do {
    printf("%s", mensaje);
    entradaUser = scanf("%d", &valor);

    // Limpiar buffer
    while (getchar() != '\n')
      ;

    if (entradaUser == 1 && valor >= min && valor <= max) {
      return valor;
    }

    printf("Número no valido\n");
  } while (1);
}

/**
 * @brief Solicita coordenadas al usuario
 *
 * @param fila Puntero a la fial
 * @param columna Puntero a la columna
 */

void coordenadasUser(int *fila, int *columna) {
  char coordenadas[4];
  char letra;
  int numero;

  while (1) {
    printf("\nIntrodueix coordenades (ex: A5): ");
    scanf("%3s", coordenadas);
    while (getchar() != '\n')
      ;

    letra = toupper(coordenadas[0]);

    if (letra < 'A' || letra > 'J') {
      printf("Columna incorrecta (A-J)\n");
      continue;
    }

    // atoi convierte en char a int
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

/**
 * @brief Solicita al usuario una respuesta de S/N
 *
 * @param mensaje Texto a mostrar al usuario
 * @return 'S' o 'N'
 */
char snUser(const char *mensaje) {
  char c;

  do {
    printf("%s", mensaje);
    scanf(" %c", &c);
    // Limpiar buffer
    while (getchar() != '\n')
      ;

    c = toupper(c);

    if (c == 'S' || c == 'N') {
      return c;
    }

    printf("Escriu S o N\n");
  } while (1);
}

/**
 * @brief Menu para escoger la flota con la que el usuario desea jugar
 *
 * @return Número del 1 al 3 para elegir flota
 */

int elegir_flota() {
  printf("┌──────────────────────────────────┐\n");
  printf("│        Escull una flota          │\n");
  printf("├──────────────────────────────────┤\n");
  printf("│ 1 - L'Armada Vencible            │\n");
  printf("│ 2 - Els Brivalls                 │\n");
  printf("│ 3 - La Flotilla                  │\n");
  printf("└──────────────────────────────────┘\n");

  return enteroUser("Introdueix el número de la flota (1-3): ", 1, 3);
}

/**
 * @brief Comprovacion si un barco esta hundido
 *
 * @param id_barco ID del barco en partida
 * @param tablero Tablero general de la partida
 * @param tablero_conBarcos Tablero con los barcos generados aleatoriamente
 * @return 1 si esta hundido, 0 si no
 */

int barcoHundido(int id_barco, int tablero[10][10],
                 int tablero_conBarcos[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (tablero_conBarcos[i][j] == id_barco && tablero[i][j] != 1) {
        // Barco aun vivo
        return 0;
      }
    }
  }
  // barco ya hundido
  return 1;
}

/**
 * @brief Marca el agua de alrededor del barco hundido
 *
 * @param id_barco ID del barco en partida
 * @param tablero Tablero general de la partida
 * @param tablero_conBarcos Tablero con los barcos generados aleatoriamente
 */

int marcarAgua(int id_barco, int tablero[10][10],
               int tablero_conBarcos[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      // Comprovacion de las casillas del barco hundido
      if (tablero_conBarcos[i][j] == id_barco) {
        // doble for para recorrer el perimetro del barco
        for (int x = i - 1; x <= i + 1; x++) {
          for (int z = j - 1; z <= j + 1; z++) {
            if (x >= 0 && x < 10 && z >= 0 && z < 10) {
              if (tablero[x][z] == 0 && tablero_conBarcos[x][z] == 0) {
                tablero[x][z] = 2;
              }
            }
          }
        }
      }
    }
  }
}

/**
 * @brief Controla el disparo a la partida
 *
 * @param fila Fila del tablero
 * @param columna Columna del tablero
 * @param tablero Tablero general de la partida
 * @param tablero_conBarcos Tablero con los barcos generados aleatoriamente
 * @return 1 si ha tocado al barco, 0 agua o disparo repetido
 */

int disparoBarco(int fila, int columna, int tablero[10][10],
                 int tablero_conBarcos[10][10]) {
  if (tablero[fila][columna] != 0) {
    printf(" ⚠  Ja has disparat aqui\n");
    return 0;
  }

  int id_barco = tablero_conBarcos[fila][columna];

  // Hay barco, si id > 0
  if (id_barco > 0) {
    printf(" ➜  TOCAT!\n");
    tablero[fila][columna] = 1;

    if (barcoHundido(id_barco, tablero, tablero_conBarcos)) {
      printf(" ☠  VAIXELL ENFONSAT\n");
      marcarAgua(id_barco, tablero, tablero_conBarcos);
    }

    return 1;
  } else {
    printf(" ✖  AIGUA\n");
    tablero[fila][columna] = 2;
    return 0;
  }
}

/**
 * @brief Verifica si quedan barcos vivo en la partida
 *
 * @param tablero Tablero general de la partida
 * @param tablero_conBarcos Tablero con los barcos generados aleatoriamente
 */

int barcos_restantes(int tablero[10][10], int tablero_conBarcos[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (tablero_conBarcos[i][j] > 0 && tablero[i][j] != 1) {
        // Quedan barcos restantes
        return 1;
      }
    }
  }
  // No quedan barcos
  return 0;
}

/**
 * @brief Inicia y controla el comenzamiento de la partida más el bucle del
 * juego
 *
 * @param tablero_conBarcos Tablero con los barcos generados aleatoriamente
 */

void comenzarPartida(int tablero_conBarcos[10][10]) {
  printf("\n╔══════════════════════════════════════╗\n");
  printf("║     ⚓  COMENÇA LA PARTIDA  ⚓       ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  int tablero[10][10] = {0};

  int fila, columna;
  int contador = 0;

  while (1) {
    printar_tablero(tablero);

    coordenadasUser(&fila, &columna);

    disparoBarco(fila, columna, tablero, tablero_conBarcos);

    if (!barcos_restantes(tablero, tablero_conBarcos)) {
      printar_tablero(tablero);
      printf("\n╔══════════════════════════════════════╗\n");
      printf("║        🎉  VICTÒRIA TOTAL  🎉        ║\n");
      printf("╠══════════════════════════════════════╣\n");
      printf("║  Has enfonsat tota la flota!         ║\n");
      printf("║  Tirades totals: %2d                  ║\n", contador);
      printf("╚══════════════════════════════════════╝\n\n");
      return;
    }
    contador++;
  }
}

/**
 * @brief Prepara la partida llamando a las diferentes funciones para generar
 * los tableros y poder iniciar sin problemas
 *
 * @param tablero_conBarcos Tablero con los barcos generados aleatoriamente
 * @param flota Array de los barcos
 * @param num_flota Numero de barcos de la array
 */

void prepararPartida(int tablero_conBarcos[10][10], struct barco flota[],
                     int num_flota) {

  char repetir;

  do {
    // Doble for para limpiar la tabla de barcos
    for (int x = 0; x < 10; x++) {
      for (int y = 0; y < 10; y++) {
        tablero_conBarcos[x][y] = 0;
      }
    }

    tablero_barcos(tablero_conBarcos, flota, num_flota);

    if (snUser("\nTauler generat. Vols fer trampes i veure el tauler generat? "
               "(S/N): ") == 'S') {
      printf("\n👁  Mode trampes activat\n\n");
      printar_tablero_barcos(tablero_conBarcos);
    }

    repetir = snUser("\nVols generar un nou tauler? (S/N): ");

  } while (repetir == 'S');
}

/*
 * ======================================================================
 * FUNCIÓN PRINCIPAL
 * ======================================================================
 */

/**
 * @brief Entrada del programa
 *
 * Gestion principal del juego y el bucle de las partidas
 */

int main(void) {
  srand(time(NULL));

  printf("╔════════════════════════════════════╗\n");
  printf("║        ⚓  ENFONSAR LA FLOTA  ⚓   ║\n");
  printf("╠════════════════════════════════════╣\n");
  printf("║        Joc de guerra naval         ║\n");
  printf("╚════════════════════════════════════╝\n\n");

  char jugar;

  do {
    int tablero_conBarcos[10][10] = {0};

    int flota = elegir_flota();

    switch (flota) {
    case 1:
      printf("\n⚙  Preparant tauler de la flota 1...\n");

      prepararPartida(tablero_conBarcos, flota1, num_flota1);

      break;

    case 2:
      printf("\n⚙  Preparant tauler de la flota 2... \n");

      prepararPartida(tablero_conBarcos, flota2, num_flota2);

      break;

    case 3:
      printf("\n⚙  Preparant tauler de la flota 3... \n");

      prepararPartida(tablero_conBarcos, flota3, num_flota3);

      break;
    default:
      break;
    }

    comenzarPartida(tablero_conBarcos);

    jugar = snUser("Vols jugar una nova partida? (S/N): ");
  } while (jugar == 'S');

  printf("\nGràcies per jugar a ⚓ Enfonsar la Flota ⚓\n");
  printf("Fins la pròxima capitana / capità!\n");
}