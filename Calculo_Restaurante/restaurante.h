#ifndef RESTAURANTE_H
#define RESTAURANTE_H

/* Limites principales del sistema. */
#define MAX_INGREDIENTES 100
#define MAX_PLATOS 100
#define MAX_RELACIONES 500
#define MAX_CODIGO 20
#define MAX_NOMBRE 60
#define MAX_TEXTO 40

/* Modelos de datos usados por el programa. */
typedef struct {
    char codigo[MAX_CODIGO];
    char nombre[MAX_NOMBRE];
    float costoUnitario;
    char unidadMedida[MAX_TEXTO];
} Ingrediente;
/* Modelos de datos usados por el programa. */
typedef struct {
    char codigo[MAX_CODIGO];
    char nombre[MAX_NOMBRE];
    char categoria[MAX_TEXTO];
    float impuesto;
    float servicio;
    float ganancia;
} Plato;

typedef struct {
    char codigoPlato[MAX_CODIGO];
    char codigoIngrediente[MAX_CODIGO];
    float cantidadUsada;
} PlatoIngrediente;