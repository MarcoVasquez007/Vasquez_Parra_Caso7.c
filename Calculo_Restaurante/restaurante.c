#include "restaurante.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO_INGREDIENTES "ingredientes.csv"
#define ARCHIVO_PLATOS "platos.csv"
#define ARCHIVO_RELACIONES "plato_ingredientes.csv"
#define MAX_LINEA 256

/* ---------- Entrada segura ---------- */

static void quitarSalto(char *texto) {
    texto[strcspn(texto, "\r\n")] = '\0';
}

static void leerTexto(const char *mensaje, char *destino, int tamano) {
    int caracter;

    while (1) {
        printf("%s", mensaje);

        if (fgets(destino, tamano, stdin) == NULL) {
            clearerr(stdin);
            continue;
        }
        if (strchr(destino, '\n') == NULL) {
            while ((caracter = getchar()) != '\n' && caracter != EOF) {
            }
        }

        quitarSalto(destino);

        if (destino[0] == '\0') {
            printf("La entrada no puede estar vacia.\n");
        } else if (strchr(destino, ',') != NULL) {
            printf("No use comas porque los datos se guardan en CSV.\n");
        } else {
            return;
        }
    }
}