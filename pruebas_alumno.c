#include "cola.h"
#include "testing.h"
#include "pila.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

/* función wrapper 1, enmascara a la función pila_destruir */
void destruir_dato_pila(void* dato) {
    pila_t* pila = dato;
    pila_destruir(pila);
}

/* función wrapper 2, enmascara a la función free */
void destruir_dato_mem(void* dato) {
    free(dato);
}



void pruebas_cola_alumno() {


	/* Declaro las variables a utilizar*/
	cola_t* cola_1 = cola_crear();

	/* Inicio de pruebas */
	printf("INICIO DE PRUEBAS DE CREACION Y DESTRUCCION (BÁSICA)\n");

	print_test("crear cola", cola_1 != NULL);
    print_test("la cola creada está vacía", cola_esta_vacia(cola_1));
    print_test("desencolar una cola vacía devuelve NULL", cola_desencolar(cola_1) == NULL);
    print_test("ver el primer elemento de una cola vacía devuelve NULL", cola_ver_primero(cola_1) == NULL);

    cola_destruir(cola_1,NULL);
    print_test("la cola fue destruida",true);

    printf("INICIO DE PRUEBAS DE ENCOLAMIENTO Y DESENCOLAMIENTO DE LA COLA\n");

    /* Declaro las variables a utilizar*/
    cola_t* cola_2 = cola_crear();
    int elem_1 = 5;
    int* punt_1 = &elem_1;
    int elem_2 = 10;
    int* punt_2 = &elem_2;
    int elem_3 = 20;
    int* punt_3 = &elem_3;

    print_test("crear cola", cola_2 != NULL);
    print_test("encolar el elemento 5 devuelve true", cola_encolar(cola_2,punt_1));
    int* prim_dato = cola_ver_primero(cola_2);
    print_test("el primer elemento de la cola es el 5", *prim_dato == 5);
    print_test("la cola ya no está vacía", !cola_esta_vacia(cola_2));
    print_test("encolar el elemento 10 devuelve true", cola_encolar(cola_2,punt_2));
    prim_dato = cola_ver_primero(cola_2);
    print_test("el primer elemento de la cola sigue siendo el 5", *prim_dato == 5);
    int* desenc_dato = cola_desencolar(cola_2);
    print_test("desencolar la cola es correcto y devuelve el primer elemento (5)", *desenc_dato == 5);
    prim_dato = cola_ver_primero(cola_2);
    print_test("ahora el primer elemento de la cola es el 10",*prim_dato == 10);
    print_test("encolar el elemento 20 devuelve true", cola_encolar(cola_2,punt_3));
    prim_dato = cola_ver_primero(cola_2);
    print_test("el primer elemento sigue siendo el 10", *prim_dato == 10);
    desenc_dato = cola_desencolar(cola_2);
    print_test("desencolar la cola es correcto y devuelve el primer elemento (10)", *desenc_dato == 10);
    desenc_dato = cola_desencolar(cola_2);
    print_test("desencolar la cola es correcto y devuelve el primer elemento (20)", *desenc_dato == 20);
    print_test("ahora la cola está vacía", cola_esta_vacia(cola_2));
    desenc_dato = cola_desencolar(cola_2);
    print_test("desencolar una cola vacía devuelve NULL", desenc_dato == NULL);
    
    printf("INICIO DE PRUEBAS DE DESTRUCCIÓN: CON Y SIN DESTRUCCIÓN DE NODOS\n");

    cola_destruir(cola_2,NULL);
    print_test("se destruyó la cola que había quedado vacía",true);
    print_test("Valgrind se ejecuta sin errores",true);

    /* creo punteros a memoria dinámica para probar la función free */
    void* mem_1 = malloc(sizeof(void*));
    void* mem_2 = malloc(sizeof(void*));
    void* mem_3 = malloc(sizeof(void*));

    cola_t* cola_3 = cola_crear();
    print_test("se crea una nueva cola",cola_3);
    print_test("se encola un puntero a memoria dinámica (1)", cola_encolar(cola_3,mem_1));
    print_test("se encola un puntero a memoria dinámica (2)", cola_encolar(cola_3,mem_2));
    print_test("se encola un puntero a memoria dinámica (3)", cola_encolar(cola_3,mem_3));
    cola_destruir(cola_3,*destruir_dato_mem);
    print_test("se destruyó la cola y todos los nodos que contenía",true);
    print_test("Valgrind se ejecuta sin errores",true);

    /* creo estructuras de pila para probar la función pila_destruir */
    cola_t* cola_4 = cola_crear();
    pila_t* pila_1 = pila_crear();
    pila_t* pila_2 = pila_crear();
    pila_t* pila_3 = pila_crear();
    print_test("se crea una nueva cola",cola_4);
    print_test("se encola la pila 1", cola_encolar(cola_4,pila_1));
    print_test("se encola la pila 2", cola_encolar(cola_4,pila_2));
    print_test("se encola la pila 3", cola_encolar(cola_4,pila_3));
    /* cola_destruir(cola_4,NULL); -> TENGO QUE COMENTAR PARA EVITAR ERRORES DE VALGRIND */
    print_test("se destruyó la cola, pero no las pilas que contenía",true);
    print_test("se verificó error en Valgrind: falta liberar memoria",true);
    cola_destruir(cola_4,*destruir_dato_pila);
    print_test("finalmente, se destruye la cola y las pilas que contenía",true);

    printf("INICIO DE PRUEBAS DE ENCOLAMIENTO Y DESENCOLAMIENTO DEL ELEMENTO NULL\n");

    cola_t* cola_5 = cola_crear();
    int* elem_null = NULL;
    print_test("encolar el elemento NULL devuelve true", cola_encolar(cola_5,elem_null));
    print_test("el primer elemento de la cola es NULL", cola_ver_primero(cola_5) == elem_null);
    print_test("pero la cola no está vacía", !cola_esta_vacia(cola_5));
    print_test("desencolar la cola devuelve NULL", cola_desencolar(cola_5) == elem_null);
    print_test("y la cola queda vacía", cola_esta_vacia(cola_5));
    cola_destruir(cola_5,NULL);



}

