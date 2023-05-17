#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

nodo_abb_t *nodo_abb_crear(void *elemento) {
	nodo_abb_t *nodo = malloc(sizeof(nodo_abb_t));
	if (!nodo) {
		return NULL;
	}
	nodo->elemento = elemento;
	nodo->izquierda = NULL;
	nodo->derecha = NULL;
	return nodo;
}

abb_t *abb_crear(abb_comparador comparador)
{
	if (!comparador) {
		return NULL;
	}
	abb_t *abb = malloc(sizeof(abb_t));
	if (!abb) {
		return NULL;
	}
	abb->comparador = comparador;
	abb->tamanio = 0;
	abb->nodo_raiz = NULL;
	return abb;
}

nodo_abb_t *abb_insertar_nodo(nodo_abb_t *nodo, void *elemento, abb_comparador comparador) {
	if (!nodo) {
		return nodo_abb_crear(elemento);
	}
	int cmp = comparador(nodo->elemento, elemento);
	if (cmp < 0) {
		nodo->derecha = abb_insertar_nodo(nodo->derecha, elemento, comparador);
	} else {
		nodo->izquierda = abb_insertar_nodo(nodo->izquierda, elemento, comparador);
	}
	return nodo;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol) {
		return NULL;
	}
	arbol->nodo_raiz = abb_insertar_nodo(arbol->nodo_raiz, elemento, arbol->comparador);
	arbol->tamanio++;
	return arbol;
}

nodo_abb_t *buscar_padre_predecesor_inorden(nodo_abb_t *nodo) {
    nodo_abb_t *predecesor = nodo;
	nodo_abb_t *padre_predecesor = nodo;
    while (predecesor->derecha) {
		padre_predecesor = predecesor;
        predecesor = padre_predecesor->derecha;
    }
    return padre_predecesor;
}

nodo_abb_t *buscar_predecesor(nodo_abb_t *nodo) {
    if (!nodo->derecha) return nodo;
    return buscar_predecesor(nodo->derecha);
}

void swap_contenido_de_nodos_abb(nodo_abb_t* nodo_original, nodo_abb_t* nodo_nuevo) {
	void *dato = nodo_original->elemento;
	nodo_original->elemento = nodo_nuevo->elemento;
	nodo_nuevo->elemento = dato;
}

void *abb_quitar_nodo(nodo_abb_t *nodo, nodo_abb_t *padre, abb_t *arbol) {
	nodo_abb_t* predecesor = NULL;
	nodo_abb_t* nodo_a_liberar = NULL;
    if (nodo->izquierda) {
        nodo_abb_t *padre_predecesor = buscar_padre_predecesor_inorden(nodo->izquierda);
		if (padre_predecesor==nodo->izquierda && !padre_predecesor->derecha){
			//nodo->izquierda no tiene hijos derechos 1
			padre_predecesor = nodo;
			predecesor = nodo->izquierda;
			nodo_a_liberar = predecesor;
			swap_contenido_de_nodos_abb(predecesor, nodo);
			padre_predecesor->izquierda = predecesor->izquierda;
		} else {
			// nodo->izquierda si tiene hijos derechos
			predecesor = padre_predecesor->derecha;
			nodo_a_liberar = predecesor;
			swap_contenido_de_nodos_abb(predecesor, nodo);
			padre_predecesor->derecha = predecesor->izquierda;
		}
    } else if (nodo->derecha) { 
		// solamente tengo nodo->derecha, elijo swapear con ese nodo->derecha y nodo
		// pero podria tomar el hijo mas izquierdo del nodo->derecha
		swap_contenido_de_nodos_abb(nodo->derecha, nodo);
		nodo->izquierda = nodo->derecha->izquierda;
		nodo_a_liberar = nodo->derecha;
		nodo->derecha = nodo->derecha->derecha;
    } else {
		if (padre->derecha == nodo)
			padre->derecha = NULL;
		else
			padre->izquierda = NULL;
		nodo_a_liberar = nodo;
    }
    arbol->tamanio--;
	void* dato_del_nodo_a_liberar = nodo_a_liberar->elemento;
    free(nodo_a_liberar);
	if(arbol->tamanio==0){
		arbol->nodo_raiz = NULL;
	}
    return dato_del_nodo_a_liberar;
}

nodo_abb_t *abb_padre_de_nodo_buscado(nodo_abb_t *nodo, nodo_abb_t *padre, void *elemento, abb_comparador comparador) {
	if (!nodo) {
		return NULL;
	}
	int cmp = comparador(nodo->elemento, elemento);
	if (cmp == 0) {
		return padre;
	}
	if (cmp < 0) {
		return abb_padre_de_nodo_buscado(nodo->derecha, nodo, elemento, comparador);
	}
	return abb_padre_de_nodo_buscado(nodo->izquierda, nodo, elemento, comparador);
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (!arbol) {
		return NULL;
	}
	nodo_abb_t* nodo_padre = abb_padre_de_nodo_buscado(arbol->nodo_raiz, arbol->nodo_raiz, elemento, arbol->comparador);
	nodo_abb_t* nodo_buscado = NULL;
	if (nodo_padre == NULL) {
		return NULL;
	} 
	if (nodo_padre == arbol->nodo_raiz && arbol->comparador(nodo_padre->elemento, elemento) == 0) {
		nodo_buscado = nodo_padre;
	} else if (nodo_padre->derecha != NULL && arbol->comparador(nodo_padre->derecha->elemento, elemento) == 0) {
		nodo_buscado = nodo_padre->derecha;
	} else {
		nodo_buscado = nodo_padre->izquierda;
	}

	return abb_quitar_nodo(nodo_buscado, nodo_padre, arbol);
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (!arbol) {
		return NULL;
	}
	nodo_abb_t* nodo_padre = abb_padre_de_nodo_buscado(arbol->nodo_raiz, arbol->nodo_raiz, elemento, arbol->comparador);
	if (nodo_padre == NULL)
		return NULL;
	else if (nodo_padre == arbol->nodo_raiz && arbol->comparador(nodo_padre->elemento, elemento) == 0) {
		return nodo_padre->elemento;
	} else if (nodo_padre->derecha && arbol->comparador(nodo_padre->derecha->elemento, elemento) == 0) {
		return nodo_padre->derecha->elemento;
	} else {
		return nodo_padre->izquierda->elemento;
	}
}

bool abb_vacio(abb_t *arbol)
{
	if (!arbol) {
		return true;
	}
	return arbol->tamanio == 0;
}

size_t abb_tamanio(abb_t *arbol)
{
	if (!arbol) {
		return 0;
	}
	return arbol->tamanio;
}

void abb_destruir_nodo(nodo_abb_t *nodo)
{
	if (!nodo) {
		return;
	}
	if (nodo->derecha)
		abb_destruir_nodo(nodo->derecha);
	if (nodo->izquierda)
		abb_destruir_nodo(nodo->izquierda);
	free(nodo);
}

void abb_destruir(abb_t *arbol)
{
	if (arbol)
		abb_destruir_nodo(arbol->nodo_raiz);
	free(arbol);
}

void abb_destruir_todo_nodo(nodo_abb_t *nodo, void (*destructor)(void *)) {
	if (!nodo) {
		return;
	}
	if (nodo->derecha){ //nodo->izquierda
		abb_destruir_todo_nodo(nodo->derecha, destructor);
	}
	if (nodo->izquierda){
		abb_destruir_todo_nodo(nodo->izquierda, destructor);
	}
	if (destructor)
		destructor(nodo->elemento);
	free(nodo);
	return;
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol)
		abb_destruir_todo_nodo(arbol->nodo_raiz, destructor);
	free(arbol);
	return;
}

size_t abb_preorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, bool* ejecucion) {
	if (!nodo || !(*ejecucion)) {
		return 0;
	}
	size_t contador = 0;
	if (funcion == NULL || funcion(nodo->elemento, aux) ) {
		contador++;
	}
	else {
		*ejecucion = false;
		return 1;
	}
	contador += abb_preorden(nodo->izquierda, funcion, aux, ejecucion);
	contador += abb_preorden(nodo->derecha, funcion, aux, ejecucion);
	return contador;
}
size_t abb_inorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, bool* ejecucion) {
	if (!nodo) {
		return 0;
	}
	if (!(*ejecucion)) {
		return 0;
	}
	size_t contador = 0;
	contador += abb_inorden(nodo->izquierda, funcion, aux, ejecucion);
	if ((*ejecucion) && (funcion == NULL || funcion(nodo->elemento, aux) )) {
		contador++;
	}
	else {
		*ejecucion = false;
		return ++contador;
	}
	contador += abb_inorden(nodo->derecha, funcion, aux, ejecucion);
	return contador;
}
size_t abb_postorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, bool* ejecucion) {
	if (!nodo) {
		return 0;
	}
	if (!(*ejecucion)) {
		return 0;
	}
	size_t contador = 0;
	contador += abb_postorden(nodo->izquierda, funcion, aux, ejecucion);
	contador += abb_postorden(nodo->derecha, funcion, aux, ejecucion);
	if ((*ejecucion) && funcion(nodo->elemento, aux) ) {
		contador++;
	}
	else {
		*ejecucion = false;
		return ++contador;
	}
	return contador;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	size_t cuantos = 0;
	bool ejecucion = true;
	if (!arbol || arbol->tamanio == 0 || !funcion) {
		return cuantos;
	}
	switch (recorrido) {
		case PREORDEN:
			cuantos = abb_preorden(arbol->nodo_raiz, funcion, aux, &ejecucion);
			break;
		case INORDEN:
			cuantos = abb_inorden(arbol->nodo_raiz, funcion, aux, &ejecucion);
			break;
		case POSTORDEN:
			cuantos = abb_postorden(arbol->nodo_raiz, funcion, aux, &ejecucion);
			break;
		default:
			break;
	}
	return cuantos;
}

/*void imprime_array(void** array, size_t tamanio) {
	printf("imprimiendo arreglo: ");
	for(size_t i = 0; i<tamanio; i++){
		printf("%d ", *(int*)array[i]);
	}
	printf("\n");
}*/

size_t abb_recorrer_nodo_preorden(nodo_abb_t *nodo, void **array,
		    size_t tamanio_array, size_t* p_contador, bool* ejecucion) {
	if (!nodo || *p_contador == tamanio_array || !(*ejecucion)) {
		return (*p_contador);
	}
	array[*p_contador] = nodo->elemento;
	(*p_contador)++;
	//imprime_array(array,(*p_contador));
	(*p_contador) = abb_recorrer_nodo_preorden(nodo->izquierda, array, tamanio_array, p_contador, ejecucion);
	(*p_contador) = abb_recorrer_nodo_preorden(nodo->derecha, array, tamanio_array, p_contador, ejecucion);
	return *p_contador;
}
size_t abb_recorrer_nodo_inorden(nodo_abb_t *nodo, void **array,
		    size_t tamanio_array, size_t* p_contador, bool* ejecucion) {
	if (!nodo || *p_contador == tamanio_array || !(*ejecucion)) {
		return (*p_contador);
	}
	(*p_contador) = abb_recorrer_nodo_inorden(nodo->izquierda, array, tamanio_array, p_contador, ejecucion);
	array[*p_contador] = nodo->elemento;
	(*p_contador)++;
	//imprime_array(array,(*p_contador));
	(*p_contador) = abb_recorrer_nodo_inorden(nodo->derecha, array, tamanio_array, p_contador, ejecucion);
	return *p_contador;
}
size_t abb_recorrer_nodo_postorden(nodo_abb_t *nodo, void **array,
		    size_t tamanio_array, size_t* p_contador, bool* ejecucion) {
	if (!nodo) 
		return (*p_contador);
	(*p_contador) = abb_recorrer_nodo_postorden(nodo->izquierda, array, tamanio_array, p_contador, ejecucion);
	(*p_contador) = abb_recorrer_nodo_postorden(nodo->derecha, array, tamanio_array, p_contador, ejecucion);
	if(*ejecucion) {
		array[*p_contador] = nodo->elemento;
		(*p_contador)++;
	}
	if ( (*p_contador) >= tamanio_array || !(*ejecucion)) {
		(*ejecucion) = false;
		return (*p_contador);
	}
	//imprime_array(array,(*p_contador));
	return *p_contador;
}

bool funcioncita(void* elemento, void* aux) {
	if ( *(size_t*)aux == 0 ){
		printf("imprimiendo arreglo: ");
		*(size_t*)aux = 1;
	}
	printf("%d  ", *(int*)elemento);
	return true;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	size_t contador = 0;
	bool ejecucion = true;
	if (!arbol || arbol->tamanio == 0) {
		return contador;
	}
	switch (recorrido) {
		case PREORDEN:
			contador = abb_recorrer_nodo_preorden(arbol->nodo_raiz, array, tamanio_array, &contador, &ejecucion);
			break;
		case INORDEN:
			contador = abb_recorrer_nodo_inorden(arbol->nodo_raiz, array, tamanio_array, &contador, &ejecucion);
			break;
		case POSTORDEN:
			contador = abb_recorrer_nodo_postorden(arbol->nodo_raiz, array, tamanio_array, &contador, &ejecucion);
			break;
		default:
			break;
	}
	return contador;
}
