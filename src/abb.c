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
	printf("abb_crear\n");
	if (!comparador) {
		return NULL;
	}
	abb_t *abb = malloc(sizeof(abb_comparador));
	if (!abb) {
		return NULL;
	}
	abb->comparador = comparador;
	abb->tamanio = 0;
	//nodo_abb_t *nodo = nodo_abb_crear(NULL);
	abb->nodo_raiz = NULL;
	return abb;
}

nodo_abb_t *abb_insertar_nodo(nodo_abb_t *nodo, void *elemento, abb_comparador comparador) {
	//printf("abb_insertar_nodo\n");
	// printf("insertando\n");
	if (!nodo) {
		//printf("insertando\n");
		return nodo_abb_crear(elemento);
	}
	// printf("insertando\n");
	int cmp = comparador(nodo->elemento, elemento);
	// printf("cmp: %d\n", cmp);
	if (cmp < 0) {
		// printf("<0\n");
		nodo->derecha = abb_insertar_nodo(nodo->derecha, elemento, comparador);
	} else {
		// printf(">0\n");
		nodo->izquierda = abb_insertar_nodo(nodo->izquierda, elemento, comparador);
	}
	return nodo;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	printf("abb_insertar\nel elemento apunta a %p\n", elemento);
	if (!arbol) {
		return NULL;
	}
	if (elemento){
		printf("inserto %d\n", *(int*)elemento);
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
		printf("nodo tiene izquierda\n");
        nodo_abb_t *padre_predecesor = buscar_padre_predecesor_inorden(nodo->izquierda);
		if (padre_predecesor->elemento) 
			printf("el padre del predecesor es: %d\n", *(int*)padre_predecesor->elemento);
		if (padre_predecesor==nodo->izquierda && !padre_predecesor->derecha){
			//nodo->izquierda no tiene hijos derechos 1
			printf("el padre del predecesor es el nodo izquierda del nodo a borrar\t nodo->izquierda no tiene hijos derechos\n");
			padre_predecesor = nodo;
			predecesor = nodo->izquierda;
			if (predecesor->elemento)
				printf("predecesor es: %d\n",*(int*)predecesor->elemento);
			nodo_a_liberar = predecesor;
			swap_contenido_de_nodos_abb(predecesor, nodo);
			if (predecesor->elemento)
				printf("nodo a liberar es: %d\n",*(int*)predecesor->elemento);
			padre_predecesor->izquierda = predecesor->izquierda;
		} else {
			// nodo->izquierda si tiene hijos derechos
			printf("nodo->izquierda si tiene hijos derechos\n");
			predecesor = padre_predecesor->derecha;
			if (predecesor->elemento)
				printf("predecesor es: %d\n",*(int*)predecesor->elemento);
			nodo_a_liberar = predecesor;
			swap_contenido_de_nodos_abb(predecesor, nodo);
			if (predecesor->elemento)
				printf("nodo a liberar es: %d\n",*(int*)predecesor->elemento);
			padre_predecesor->derecha = predecesor->izquierda;
		}
    } else if (nodo->derecha) { 
		printf("nodo tiene derecha\n");
		// solamente tengo nodo->derecha, elijo swapear con ese nodo->derecha y nodo
		// pero podria tomar el hijo mas izquierdo del nodo->derecha
		swap_contenido_de_nodos_abb(nodo->derecha, nodo);
		nodo->izquierda = nodo->derecha->izquierda;
		nodo_a_liberar = nodo->derecha;
		nodo->derecha = nodo->derecha->derecha;
    } else {
		printf("nodo else\n");
		if (padre->derecha == nodo)
			padre->derecha = NULL;
		else
			padre->izquierda = NULL;
		nodo_a_liberar = nodo;
    }
	printf("tamanio antes: %zu\n", arbol->tamanio);
    arbol->tamanio--;
	printf("tamanio despues: %zu\n", arbol->tamanio);
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
	if (elemento) {
		printf("comparo nodo->elemento: %d con elemento_buscado: %d\n", *(int*)nodo->elemento, *(int*)elemento);
	}
	int cmp = comparador(nodo->elemento, elemento);
	if (cmp == 0) {
		if (padre->elemento) 
			printf("retorno: %d\n", *(int*)padre->elemento);
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
	if (elemento) {
		printf("abb_quitar elemento: %d\n", *(int*)elemento);
	}
	nodo_abb_t* nodo_padre = abb_padre_de_nodo_buscado(arbol->nodo_raiz, arbol->nodo_raiz, elemento, arbol->comparador);
	nodo_abb_t* nodo_buscado = NULL;
	if (nodo_padre == NULL) {
		printf("nodo_padre es NULL, no se encontró el elemento buscado\n");
		return NULL;
	} 
	if (nodo_padre->elemento) 
		printf("padre del nodo buscado es: %d\n", *(int*)(nodo_padre->elemento));	
	if (nodo_padre == arbol->nodo_raiz && arbol->comparador(nodo_padre->elemento, elemento) == 0) {
		if (nodo_padre->elemento) 		
			printf("nodo buscado es el nodo raiz: %d\n", *(int*)nodo_padre->elemento);	
		nodo_buscado = nodo_padre;
	} else if (nodo_padre->derecha != NULL && arbol->comparador(nodo_padre->derecha->elemento, elemento) == 0) {
		printf("el nodo buscado es nodo_padre->derecha: %d\n", *(int*)nodo_padre->derecha->elemento);	
		nodo_buscado = nodo_padre->derecha;
	} else {
		printf("el nodo buscado es nodo_padre->izquierda: %d\n", *(int*)nodo_padre->izquierda->elemento);	
		nodo_buscado = nodo_padre->izquierda;
	}

	return abb_quitar_nodo(nodo_buscado, nodo_padre, arbol);
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	printf("abb_buscar\n");
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
	printf("abb_vacio\n");
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
	printf("imprimo tamanio: %zu\n", arbol->tamanio);
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
	if (nodo->elemento){
		printf("destruyendo nodo: %d\n", *(int*)nodo->elemento);
	} else {
		printf("destruyendo nodo\n");
	}
	free(nodo);
}

void abb_destruir(abb_t *arbol)
{
	printf("abb_destruir\n");
	if (arbol)
		abb_destruir_nodo(arbol->nodo_raiz);
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
	printf("abb_destruir_todo\n");
	if (arbol)
		abb_destruir_todo_nodo(arbol->nodo_raiz, destructor);
	return;
}

size_t abb_preorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux) {
	if (!nodo)
		return 0;

	bool validacion = funcion(nodo->elemento, aux);
	if (nodo->elemento) 		
		printf("visito nodo: %d\n",*(int*)nodo->elemento);
	size_t contador = 0;
	size_t resu = 0;
	if (aux) {
		printf("aux vale: %d\n", *(int*)aux);
	}
	if (validacion) {
		contador++;
	}
	else {
		printf(" funcion devolvió false\n");
		return 0;
	}
	resu = abb_preorden(nodo->izquierda, funcion, aux);
	contador += resu;
	if (resu == 0) return contador;
	contador += abb_preorden(nodo->derecha, funcion, aux);
	return contador;
}
size_t abb_inorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux) {
	return 0;
}
size_t abb_postorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux) {
	return 0;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	printf("abb_con_cada_elemento\n");
	size_t cuantos = 0;
	if (!arbol || arbol->tamanio == 0) {
		return cuantos;
	}
	switch (recorrido) {
		case PREORDEN:
			cuantos = abb_preorden(arbol->nodo_raiz, funcion, aux);
			break;
		case INORDEN:
			cuantos = abb_inorden(arbol->nodo_raiz, funcion, aux);
			break;
		case POSTORDEN:
			cuantos = abb_postorden(arbol->nodo_raiz, funcion, aux);
			break;
		default:
			break;
	}
	return cuantos;
}

void imprime_array(void** array, size_t tamanio) {
	printf("imprimiendo arreglo: ");
	for(size_t i = 0; i<tamanio; i++){
		printf("%d ", *(int*)array[i]);
	}
}

size_t abb_recorrer_nodo_preorden(nodo_abb_t *nodo, void **array,
		    size_t tamanio_array, size_t* p_contador) {
	if (*p_contador == tamanio_array) {
		return (*p_contador);
	}
	array[*p_contador] = nodo->elemento;
	(*p_contador)++;
	imprime_array(array,(*p_contador));
	if (nodo->izquierda)
		(*p_contador) = abb_recorrer_nodo_preorden(nodo->izquierda, array, tamanio_array, p_contador);
	if (nodo->derecha)
		(*p_contador) = abb_recorrer_nodo_preorden(nodo->derecha, array, tamanio_array, p_contador);
	return *p_contador;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	printf("abb_recorrer\n");
	size_t contador = 0;
	if (!arbol || arbol->tamanio == 0) {
		return contador;
	}
	switch (recorrido) {
		case PREORDEN:
			contador = abb_recorrer_nodo_preorden(arbol->nodo_raiz, array, tamanio_array, &contador);
			break;
		case INORDEN:
			// contador = abb_recorrer_nodo_inorden(arbol->nodo_raiz, array, tamanio_array, &contador);
			break;
		case POSTORDEN:
			// contador = abb_recorrer_nodo_postorden(arbol->nodo_raiz, array, tamanio_array, &contador);
			break;
		default:
			break;
	}
	return contador;
}
