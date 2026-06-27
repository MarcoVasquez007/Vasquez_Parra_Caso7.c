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
int leerEntero(const char *mensaje, int minimo, int maximo) {
    char linea[80];
    char *fin;
    long valor;

    while (1) {
        printf("%s", mensaje);

        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            clearerr(stdin);
            continue;
        }

        valor = strtol(linea, &fin, 10);
        while (isspace((unsigned char)*fin)) {
            fin++;
        }

        if (fin != linea && *fin == '\0' && valor >= minimo && valor <= maximo) {
            return (int)valor;
        }

        printf("Ingrese un numero entre %d y %d.\n", minimo, maximo);
    }
}

static float leerFloat(const char *mensaje, float minimo, float maximo, int incluyeMinimo) {
    char linea[80];
    char *fin;
    float valor;
    int minimoValido;

    while (1) {
        printf("%s", mensaje);

        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            clearerr(stdin);
            continue;
        }

        valor = strtof(linea, &fin);
        while (isspace((unsigned char)*fin)) {
            fin++;
        }

        minimoValido = incluyeMinimo ? valor >= minimo : valor > minimo;

        if (fin != linea && *fin == '\0' && minimoValido && valor <= maximo) {
            return valor;
        }

        printf("Valor invalido.\n");
    }
}

int confirmar(const char *mensaje) {
    char respuesta[10];

    while (1) {
        printf("%s (s/n): ", mensaje);

        if (fgets(respuesta, sizeof(respuesta), stdin) == NULL) {
            clearerr(stdin);
            continue;
        }

        if (respuesta[0] == 's' || respuesta[0] == 'S') {
            return 1;
        }
        if (respuesta[0] == 'n' || respuesta[0] == 'N') {
            return 0;
        }
    }
}
void pausar(void) {
    char linea[4];
    printf("Presione ENTER para continuar...");
    fgets(linea, sizeof(linea), stdin);
}

/* ---------- Busquedas ---------- */

static int contieneTexto(const char *texto, const char *busqueda) {
    char copiaTexto[MAX_NOMBRE];
    char copiaBusqueda[MAX_NOMBRE];
    int i;

    snprintf(copiaTexto, sizeof(copiaTexto), "%s", texto);
    snprintf(copiaBusqueda, sizeof(copiaBusqueda), "%s", busqueda);

    for (i = 0; copiaTexto[i] != '\0'; i++) {
        copiaTexto[i] = (char)tolower((unsigned char)copiaTexto[i]);
    }
    for (i = 0; copiaBusqueda[i] != '\0'; i++) {
        copiaBusqueda[i] = (char)tolower((unsigned char)copiaBusqueda[i]);
    }

    return strstr(copiaTexto, copiaBusqueda) != NULL;
}

static int buscarIngrediente(const Sistema *sistema, const char *codigo) {
    int i;
    for (i = 0; i < sistema->totalIngredientes; i++) {
        if (strcmp(sistema->ingredientes[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return -1;
}

static int buscarPlato(const Sistema *sistema, const char *codigo) {
    int i;
    for (i = 0; i < sistema->totalPlatos; i++) {
        if (strcmp(sistema->platos[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return -1;
}

static int buscarRelacion(const Sistema *sistema, const char *codigoPlato, const char *codigoIngrediente) {
    int i;
    for (i = 0; i < sistema->totalRelaciones; i++) {
        if (strcmp(sistema->relaciones[i].codigoPlato, codigoPlato) == 0 &&
            strcmp(sistema->relaciones[i].codigoIngrediente, codigoIngrediente) == 0) {
            return i;
        }
    }
    return -1;
}

static int ingredienteEnUso(const Sistema *sistema, const char *codigo) {
    int i;
    for (i = 0; i < sistema->totalRelaciones; i++) {
        if (strcmp(sistema->relaciones[i].codigoIngrediente, codigo) == 0) {
            return 1;
        }
    }
    return 0;
}

/* ---------- Calculos ---------- */

static float costoIngredientes(const Sistema *sistema, const char *codigoPlato) {
    float total = 0.0f;
    int i;

    for (i = 0; i < sistema->totalRelaciones; i++) {
        if (strcmp(sistema->relaciones[i].codigoPlato, codigoPlato) == 0) {
            int pos = buscarIngrediente(sistema, sistema->relaciones[i].codigoIngrediente);
            if (pos >= 0) {
                total += sistema->ingredientes[pos].costoUnitario *
                         sistema->relaciones[i].cantidadUsada;
            }
        }
    }

    return total;
}

static float costoFinal(const Sistema *sistema, const Plato *plato) {
    float base = costoIngredientes(sistema, plato->codigo);
    float porcentajes = plato->impuesto + plato->servicio + plato->ganancia;
    return base + base * porcentajes / 100.0f;
}

/* ---------- Archivos CSV ---------- */

void inicializarSistema(Sistema *sistema) {
    memset(sistema, 0, sizeof(*sistema));
}