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