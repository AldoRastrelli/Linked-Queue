#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#define GRAN_CANTIDAD 100000
#define CONST1 1
#define CONST2 7
#define CONST3 15
#define CONST4 17
#define CAPACIDAD_DATOS 6

/* ******************************************************************
*                   PRUEBAS UNITARIAS ALUMNO
* *****************************************************************/

void pruebas_cola_vacia(cola_t* cola){
    printf("\n**PRUEBAS CON COLA VACÍA**\n");
    cola_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL: ", ejemplo == NULL);

    print_test("Crear cola: ", cola != NULL);
    print_test("Cola está vacía: ", cola_esta_vacia(cola));
    print_test("Desencolar cola vacía: ", cola_desencolar(cola) == NULL);
    print_test("Ver primer elemento de cola vacía: ", cola_ver_primero(cola) == NULL);

    int i = CONST1;
    print_test("Encolar cola vacía", cola_encolar(cola, &i));

    cola_destruir(cola,NULL);
    print_test("Destruir cola con destruir_dato = NULL: ", true);
}

bool es_fifo(void** vector, int n, cola_t* cola); // definida al final
void pruebas_cola_algunos_elementos(){
    printf("\n**PRUEBAS CON ALGUNOS ELEMENTOS**\n");

    cola_t* cola = cola_crear();
    print_test("Crear cola", cola != NULL);

    int i = CONST1;
    int j = CONST2;
    int k = CONST3;
    int l = CONST4;

    printf("encolar %d en cola:", i);
    print_test("", cola_encolar(cola, &i));
    printf("%d primero en la cola:", i);
    print_test("", cola_ver_primero(cola) == &i);

    printf("encolar %d en cola:", j);
    print_test("", cola_encolar(cola, &j));
    printf("%d primero en la cola:", i);
    print_test("", cola_ver_primero(cola) == &i);
    

    printf("encolar %d en cola:", k);
    print_test("", cola_encolar(cola, &k));
    printf("%d primero en la cola:", i);
    print_test("", cola_ver_primero(cola) == &i);

    printf("encolar %d en cola:", l);
    print_test("", cola_encolar(cola, &l));
    printf("%d primero en la cola:", i);
    print_test("", cola_ver_primero(cola) == &i);

    void* vector[4] = {&i,&j,&k,&l};

    bool cola_fifo = es_fifo( vector, 4, cola);
    print_test("Cola fifo: ", cola_fifo);
    printf("*La cola se encuentra vacía*\n");

    void* n = NULL;
    print_test("Encolar NULL en cola: ", cola_encolar(cola, n));
    print_test("NULL primero en la cola: ", cola_ver_primero(cola) == n);
    print_test("desencolar NULL", cola_desencolar(cola) == n);

    cola_destruir(cola, NULL);
    print_test("Destruir cola con destruir_dato = NULL: ", true);
}

bool vaciar_cola(cola_t* cola);
cola_t* chequear_capacidad(cola_t* cola);
void pruebas_cola_gran_cantidad_elementos(){
    printf("\n**PRUEBAS CON GRANDES CANTIDADES DE ELEMENTOS**\n");

    cola_t* cola = cola_crear();
    print_test("Crear cola", cola != NULL);
    
    bool encolado = true;
    void* vector[GRAN_CANTIDAD];
    // Guardo en cada posición de memoria un puntero que apunta a su respectiva posición de memoria
    for (int i = 0; i < GRAN_CANTIDAD && encolado; i++){ 

        vector[i] = &vector[i]; 
    }
    // Encolo las direcciones de las posiciones de memoria del vector en la cola
    for (int i = 0; i < GRAN_CANTIDAD && encolado; i++){
        
        encolado = cola_encolar(cola, &vector[i]);
    }
    
    printf("encolado de %d elementos:",GRAN_CANTIDAD);
    print_test("",encolado);

    bool cola_fifo = es_fifo(vector, GRAN_CANTIDAD, cola);
    print_test("cola fifo: ", cola_fifo);
    printf("*La cola se encuentra vacía*\n");

    // Comprueba que una cola encolada y luego desencolada hasta vaciarse se comporte como cola vacía
    printf("\nSE COMPRUEBA QUE COLA ENCOLADA Y LUEGO DESENCOLADA SE COMPORTA COMO COLA VACÍA:");
    pruebas_cola_vacia(cola);
}
void pila_destruir_wrapper (void* pila);
void pruebas_cola_diferentes_estructuras(){
    printf("\n**PRUEBAS ENCOLANDO ESTRUCTURAS PARTICULARES**\n");

    cola_t* cola = cola_crear();
    print_test("Crear cola", cola != NULL);
    
    pila_t* pila1 = pila_crear();
    pila_t* pila2 = pila_crear();
    pila_t* pila3 = pila_crear();
    pila_t* pila4 = pila_crear();

    print_test("Encolar pila1 en cola: ", cola_encolar(cola, pila1));
    print_test("Encolar pila2 en cola: ", cola_encolar(cola, pila2));
    print_test("Encolar pila3 en cola: ", cola_encolar(cola, pila3));
    print_test("Encolar pila4 en cola: ", cola_encolar(cola, pila4));

    cola_destruir(cola, pila_destruir_wrapper);
    print_test("Cola_destruir con destruir_dato != NULL: ", true);
}

bool vaciar_cola(cola_t* cola){ //vacía la cola chequeando que el primero sea igual al elemento que se desencola posteriormente  
    void* primero;
    void* desencolado;
    bool son_diferentes = false;

    while (!(cola_esta_vacia(cola)) && !(son_diferentes)){
        
        primero = cola_ver_primero(cola);
        desencolado = cola_desencolar(cola);
        son_diferentes = (primero != desencolado);
    }
    return !(son_diferentes);
}

bool es_fifo(void** vector, int n, cola_t* cola){ // verifica la invariante de cola dado un vector con n elementos
    int i = 0;
    bool condicion_fifo = true;

    while (i < n && condicion_fifo){
        void* elemento_correspondiente = vector[i];
        void* desencolado = cola_desencolar(cola);
        condicion_fifo = (elemento_correspondiente == desencolado);
        i++;
    }
    return condicion_fifo;
}

void pila_destruir_wrapper (void* pila){
    pila_destruir((pila_t*) pila);
}

void pruebas_cola_alumno(){
    cola_t* cola = cola_crear();

    pruebas_cola_vacia(cola);
    pruebas_cola_algunos_elementos();
    pruebas_cola_gran_cantidad_elementos();
    pruebas_cola_diferentes_estructuras();
    return;
}
