#include <stdio.h>
#include "restaurante.h"

int main(void) {
    Sistema sistema;
    int opcion;

    inicializarSistema(&sistema);
    cargarDatos(&sistema);

    do {
        printf("\n===== COSTOS DE RESTAURANTE =====\n");
        printf("1. Gestion de ingredientes\n");
        printf("2. Gestion de platos\n");
        printf("3. Ingredientes por plato\n");
        printf("4. Calculos y reportes\n");
        printf("5. Guardar cambios\n");
        printf("6. Salir\n");

        opcion = leerEntero("Opcion: ", 1, 6);