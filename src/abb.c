#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

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
	abb_t *abb = malloc(sizeof(abb_comparador));
	if (!abb) {
		return NULL;
	}
	abb->comparador = comparador;
	abb->tamanio = 0;
	nodo_abb_t *nodo = nodo_abb_crear(NULL);
	abb->nodo_raiz = nodo;
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
	abb_insertar_nodo(arbol->nodo_raiz, elemento, arbol->comparador);
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
    void *elemento = nodo->elemento;
	nodo_abb_t* predecesor = NULL;
	nodo_abb_t* nodo_a_liberar = NULL;
    if (nodo->izquierda) {
        nodo_abb_t *padre_predecesor = buscar_padre_predecesor_inorden(nodo->izquierda);
		if (padre_predecesor==nodo->izquierda){
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
    }
    arbol->tamanio--;
	void* dato_del_nodo_a_liberar = nodo_a_liberar->elemento;
    free(nodo_a_liberar);
    return dato_del_nodo_a_liberar;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	nodo_abb_t* nodo = abb_buscar_nodo(arbol->nodo_raiz, elemento, arbol->comparador);
	if (!nodo) {
		return NULL;
	}

	return elemento;
}

nodo_abb_t *abb_padre_de_nodo_buscado(nodo_abb_t *nodo, void *elemento, abb_comparador comparador) {
	if (!nodo) {
		return NULL;
	}
	int cmp = comparador(nodo->elemento, elemento);
	if (cmp == 0) {
		return nodo;
	}
	if (cmp < 0) {
		return abb_buscar_nodo(nodo->derecha, elemento, comparador);
	}
	return abb_buscar_nodo(nodo->izquierda, elemento, comparador);
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	nodo_abb_t* nodo_padre = abb_padre_de_nodo_buscado(arbol->nodo_raiz, elemento, arbol->comparador);
	if (nodo_padre == NULL)
		return NULL;
	else if (nodo_padre->derecha && arbol->comparador(nodo_padre->derecha->elemento, elemento) == 0) {
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
	abb_destruir_nodo(arbol->nodo_raiz);
}

void abb_destruir_todo_nodo(nodo_abb_t *nodo, void (*destructor)(void *)) {
	if (!nodo) {
		return;
	}
	if (!nodo->derecha && !nodo->izquierda) {
		destructor(nodo->elemento);
		free(nodo);
	}
	if (!nodo->derecha){
		abb_destruir_todo_nodo(nodo->derecha, destructor);
	}
	if (!nodo->izquierda){
		abb_destruir_todo_nodo(nodo->izquierda, destructor);
	}
	return;
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	abb_destruir_todo_nodo(arbol->nodo_raiz, destructor);
	return;
}

size_t abb_preorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux) {
	bool validacion = funcion(nodo->elemento, aux);
	size_t contador = 0;
	if (validacion)
		contador++;
	if (nodo->derecha)
		contador += abb_preorden(nodo->derecha, funcion, aux);
	if (nodo->izquierda)
		contador += abb_preorden(nodo->izquierda, funcion, aux);
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
	size_t cuantos = 0;
	if (!arbol) {
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

size_t abb_recorrer_nodo_preorden(nodo_abb_t *nodo, void **array,
		    size_t tamanio_array, size_t* p_contador) {
	if (*p_contador == tamanio_array) {
		return (*p_contador);
	}
	array[*p_contador] = nodo->elemento;
	(*p_contador)++;
	if (nodo->derecha)
		(*p_contador) = abb_recorrer_nodo_preorden(nodo->derecha, array, tamanio_array, p_contador);
	if (nodo->izquierda)
		(*p_contador) = abb_recorrer_nodo_preorden(nodo->izquierda, array, tamanio_array, p_contador);
	return *p_contador;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	size_t contador = 0;
	if (!arbol) {
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
