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
<<<<<<< HEAD
=======
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
>>>>>>> e58e9a1fca5f8796a5c2ac4c20110f7736478e60
}
void cargarDatos(Sistema *sistema) {
    FILE *archivo;
    char linea[MAX_LINEA];

    archivo = fopen(ARCHIVO_INGREDIENTES, "r");
    if (archivo != NULL) {
        fgets(linea, sizeof(linea), archivo);
        while (sistema->totalIngredientes < MAX_INGREDIENTES &&
               fgets(linea, sizeof(linea), archivo) != NULL) {
            Ingrediente *x = &sistema->ingredientes[sistema->totalIngredientes];
            if (sscanf(linea, "%19[^,],%59[^,],%f,%39[^\r\n]",
                       x->codigo, x->nombre, &x->costoUnitario, x->unidadMedida) == 4 &&
                x->costoUnitario > 0) {
                sistema->totalIngredientes++;
            }
        }
        fclose(archivo);
    }

    archivo = fopen(ARCHIVO_PLATOS, "r");
    if (archivo != NULL) {
        fgets(linea, sizeof(linea), archivo);
        while (sistema->totalPlatos < MAX_PLATOS &&
               fgets(linea, sizeof(linea), archivo) != NULL) {
            Plato *x = &sistema->platos[sistema->totalPlatos];
            if (sscanf(linea, "%19[^,],%59[^,],%39[^,],%f,%f,%f",
                       x->codigo, x->nombre, x->categoria,
                       &x->impuesto, &x->servicio, &x->ganancia) == 6) {
                sistema->totalPlatos++;
            }
        }
        fclose(archivo);
    }

    archivo = fopen(ARCHIVO_RELACIONES, "r");
    if (archivo != NULL) {
        fgets(linea, sizeof(linea), archivo);
        while (sistema->totalRelaciones < MAX_RELACIONES &&
               fgets(linea, sizeof(linea), archivo) != NULL) {
            PlatoIngrediente *x = &sistema->relaciones[sistema->totalRelaciones];
            if (sscanf(linea, "%19[^,],%19[^,],%f",
                       x->codigoPlato, x->codigoIngrediente, &x->cantidadUsada) == 3 &&
                x->cantidadUsada > 0) {
                sistema->totalRelaciones++;
            }
        }
        fclose(archivo);
    }
}

void guardarDatos(const Sistema *sistema) {
    FILE *archivo;
    int i;

    archivo = fopen(ARCHIVO_INGREDIENTES, "w");
    if (archivo != NULL) {
        fprintf(archivo, "codigo_ing,nombre_ing,costo_unitario,unidad_medida\n");
        for (i = 0; i < sistema->totalIngredientes; i++) {
            fprintf(archivo, "%s,%s,%.2f,%s\n",
                    sistema->ingredientes[i].codigo,
                    sistema->ingredientes[i].nombre,
                    sistema->ingredientes[i].costoUnitario,
                    sistema->ingredientes[i].unidadMedida);
        }
        fclose(archivo);
    }

    archivo = fopen(ARCHIVO_PLATOS, "w");
    if (archivo != NULL) {
        fprintf(archivo, "codigo_plato,nombre_plato,categoria,impuesto_porcentaje,servicio_porcentaje,ganancia_porcentaje\n");
        for (i = 0; i < sistema->totalPlatos; i++) {
            fprintf(archivo, "%s,%s,%s,%.2f,%.2f,%.2f\n",
                    sistema->platos[i].codigo,
                    sistema->platos[i].nombre,
                    sistema->platos[i].categoria,
                    sistema->platos[i].impuesto,
                    sistema->platos[i].servicio,
                    sistema->platos[i].ganancia);
        }
        fclose(archivo);
    }

    archivo = fopen(ARCHIVO_RELACIONES, "w");
    if (archivo != NULL) {
        fprintf(archivo, "codigo_plato,codigo_ing,cantidad_usada\n");
        for (i = 0; i < sistema->totalRelaciones; i++) {
            fprintf(archivo, "%s,%s,%.2f\n",
                    sistema->relaciones[i].codigoPlato,
                    sistema->relaciones[i].codigoIngrediente,
                    sistema->relaciones[i].cantidadUsada);
        }
        fclose(archivo);
    }
}

/* ---------- Ingredientes ---------- */

static void registrarIngrediente(Sistema *sistema) {
    Ingrediente nuevo;

    if (sistema->totalIngredientes >= MAX_INGREDIENTES) {
        printf("Limite de ingredientes alcanzado.\n");
        return;
    }

    leerTexto("Codigo: ", nuevo.codigo, sizeof(nuevo.codigo));
    if (buscarIngrediente(sistema, nuevo.codigo) >= 0) {
        printf("Ese codigo ya existe.\n");
        return;
    }

    leerTexto("Nombre: ", nuevo.nombre, sizeof(nuevo.nombre));
    nuevo.costoUnitario = leerFloat("Costo unitario (> 0): ", 0, 1000000, 0);
    leerTexto("Unidad de medida: ", nuevo.unidadMedida, sizeof(nuevo.unidadMedida));

    sistema->ingredientes[sistema->totalIngredientes++] = nuevo;
    printf("Ingrediente registrado.\n");
}

static void listarIngredientes(const Sistema *sistema) {
    int i;

    if (sistema->totalIngredientes == 0) {
        printf("No hay ingredientes.\n");
        return;
    }

    for (i = 0; i < sistema->totalIngredientes; i++) {
        printf("%s | %s | $%.2f | %s\n",
               sistema->ingredientes[i].codigo,
               sistema->ingredientes[i].nombre,
               sistema->ingredientes[i].costoUnitario,
               sistema->ingredientes[i].unidadMedida);
    }
}

static void buscarIngredienteMenu(const Sistema *sistema) {
    char busqueda[MAX_NOMBRE];
    int i;
    int encontrados = 0;

    leerTexto("Codigo o parte del nombre: ", busqueda, sizeof(busqueda));

    for (i = 0; i < sistema->totalIngredientes; i++) {
        if (strcmp(sistema->ingredientes[i].codigo, busqueda) == 0 ||
            contieneTexto(sistema->ingredientes[i].nombre, busqueda)) {
            printf("%s | %s | $%.2f | %s\n",
                   sistema->ingredientes[i].codigo,
                   sistema->ingredientes[i].nombre,
                   sistema->ingredientes[i].costoUnitario,
                   sistema->ingredientes[i].unidadMedida);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("No encontrado.\n");
    }
}

static void actualizarIngrediente(Sistema *sistema) {
    char codigo[MAX_CODIGO];
    int pos;

    leerTexto("Codigo del ingrediente: ", codigo, sizeof(codigo));
    pos = buscarIngrediente(sistema, codigo);

    if (pos < 0) {
        printf("Ingrediente no encontrado.\n");
        return;
    }

    leerTexto("Nuevo nombre: ", sistema->ingredientes[pos].nombre,
              sizeof(sistema->ingredientes[pos].nombre));
    sistema->ingredientes[pos].costoUnitario =
        leerFloat("Nuevo costo (> 0): ", 0, 1000000, 0);
    leerTexto("Nueva unidad: ", sistema->ingredientes[pos].unidadMedida,
              sizeof(sistema->ingredientes[pos].unidadMedida));

    printf("Ingrediente actualizado.\n");
}