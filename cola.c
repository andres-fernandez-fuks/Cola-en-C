#include "cola.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct nodo {
    void* dato;  // Dato del nodo.
    struct nodo* prox;  // Próximo nodo.
}nodo_t;

typedef struct cola {
    nodo_t* primero;  // Primer elemento de la cola.
    nodo_t* ultimo;  // Último elemento de la cola.
}cola_t;

/* ******************************************************************
 *                    PRIMITIVAS DEL NODO
 * *****************************************************************/

nodo_t* crear_nodo(void* valor) {
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (!nodo) return NULL;
	nodo -> dato = valor;
	nodo -> prox = NULL;
	return nodo;
}


/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

// Crea una cola.
// Post: devuelve una nueva cola vacía.
cola_t* cola_crear(void) {
	cola_t* cola = malloc(sizeof(cola_t));
	if (!cola) return NULL;
	cola -> primero = NULL;
	cola -> ultimo = NULL;
	return cola;
}


void cola_destruir(cola_t *cola, void destruir_dato(void*)) {
	if (destruir_dato != NULL) {
		nodo_t* actual = cola -> primero;
		while (actual) {
			nodo_t* prox_nodo = actual->prox;
			destruir_dato(actual->dato);
			free(actual);
			actual = prox_nodo;
		}
	}
	else {
		while (!cola_esta_vacia(cola)){
		cola_desencolar(cola);
		}
	}
	free(cola);
}

bool cola_encolar(cola_t *cola, void* valor) {
	nodo_t* nodo = crear_nodo(valor);
	if (!nodo) return false;

	if (cola_esta_vacia(cola)) {
	cola -> primero = nodo;
	}
	else {
		cola -> ultimo -> prox = nodo;
	}

	cola -> ultimo = nodo;
	return true;
}

void* cola_ver_primero(const cola_t *cola) {
	if (cola_esta_vacia(cola)) return NULL;
	return cola -> primero -> dato;
}

// Devuelve verdadero o falso, según si la cola tiene o no elementos encolados.
// Pre: la cola fue creada.
bool cola_esta_vacia(const cola_t *cola) {
	return cola -> primero == NULL;
}

void* cola_desencolar(cola_t *cola) {
	if (cola_esta_vacia(cola)) return NULL;
	nodo_t* nodo_desencolado = cola -> primero;
	void* valor = nodo_desencolado -> dato;
	cola -> primero = nodo_desencolado -> prox;
	free(nodo_desencolado);
	return valor;
}






