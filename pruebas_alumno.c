#include "pa2m.h"
#include <stdio.h>
#include <stdbool.h>
#include "src/abb.h"

/* Función auxiliar para comparar elementos */
int comparar_elementos(void *elemento1, void *elemento2) {
    int *elem1 = (int*) elemento1;
    int *elem2 = (int*) elemento2;

    if (*elem1 > *elem2) {
        return 1;
    } else if (*elem1 < *elem2) {
        return -1;
    } else {
        return 0;
    }
}

void test_A_crea_y_destruye_estructura_vacia()
{
	/* PRUEBAS CON LA ESTRUCTURA DE DATOS VACIA */
	pa2m_nuevo_grupo(
		"\nPRUEBA A: CREAR Y DESTRUIR LA ESTRUCTURA DE DATOS EN ESTUDIO\n");
    abb_t *arbolitos = abb_crear(comparar_elementos);
    int elemento_inexistente = 3;
	pa2m_afirmar(
		arbolitos != NULL,
		"\tLa estructura de datos pudo ser creada.\t\t\t\t\t\tarbolito != NULL");
	pa2m_afirmar(
		abb_vacio(arbolitos) == true,
		"\tLa estructura de datos está inicialmente vacía.\t\t\t\t\tabb_vacio(arbolito) == true");
	pa2m_afirmar(
		abb_quitar(arbolitos,&elemento_inexistente) == NULL,
		"\tQuitar un elemento del t.a.d. vacio devuelve NULL.\t\t\t\tabb_quitar(arbolito) == NULL");
	pa2m_afirmar(
		abb_tamanio(arbolitos) == 0,
		"\tVer el tamanio del t.a.d. vacio devuelve 0.\t\t\t\t\tabb_tamanio(arbolitos) == 0");
	abb_destruir(arbolitos);
	pa2m_afirmar(
		true,
		"\tpuedo destruir la estructura de datos recién creada:\t\t\t\tabb_destruir(arbolitos)");
}

void test_B_agrega_y_quita_un_elemento()
{
	pa2m_nuevo_grupo(
		"\nPRUEBA B: AGREGA Y QUITA UN ELEMENTO EN LA ESTRUCTURA DE DATOS EN ESTUDIO\n");
    abb_t *arbolitos = abb_crear(comparar_elementos);
    int elemento_a_insertar = 3;
    int mismo_elemento = 3;
    int otro_elemento = 4;
	pa2m_afirmar(
		abb_insertar(arbolitos, &elemento_a_insertar) != NULL,
		"\tPuede ser agregado un 'elemento_nuevo' en el tda antes vacío.\t\t\tabb_insertar(arbolitos, &elemento_nuevo) != NULL");
	pa2m_afirmar(
		abb_vacio(arbolitos) == false,
		"\t'elemento_nuevo' es el único elemento en la 'lista', entonces:\t\t\tabb_vacio(arbolitos) == false");
	pa2m_afirmar(
		*(int*)abb_buscar(arbolitos, &mismo_elemento) == elemento_a_insertar,
		"\t'elemento_nuevo' es el único elemento  en la 'lista', entonces:\t\t\tabb_buscar(arbolitos, &mismo_elemento) == elemento_nuevo");
	pa2m_afirmar(
		abb_buscar(arbolitos, &otro_elemento) == NULL,
		"\t'elemento_nuevo' es el único elemento  en la 'lista', entonces:\t\t\tabb_buscar(arbolitos, &otro_elemento) == NULL");
	pa2m_afirmar(
		abb_quitar(arbolitos, &otro_elemento) == NULL,
		"\t'elemento_nuevo' es el único elemento  en la 'lista', entonces:\t\t\tabb_quitar(arbolitos, &otro_elemento) == NULL");
	pa2m_afirmar(
		*(int*)abb_quitar(arbolitos, &mismo_elemento) == elemento_a_insertar,
		"\t'elemento_nuevo' es el único elemento  en la 'lista', entonces:\t\t\tabb_quitar(arbolitos, &mismo_elemento) == elemento_nuevo");
	pa2m_afirmar(
		abb_vacio(arbolitos) == true,
		"\tYa no hay ningún elemento en el tda, entonces:\t\t\t\t\tabb_vacio(arbolitos) == true");
	pa2m_afirmar(
		abb_quitar(arbolitos, &mismo_elemento) == NULL,
		"\tYa no hay ningún elemento en el tda, entonces:\t\t\t\t\tabb_quitar(arbolitos, &mismo_elemento) == NULL");
	abb_destruir(arbolitos);
}

void test_C_agrega_y_quita_pocos_elementos_distintos()
{
	pa2m_nuevo_grupo(
		"\nPRUEBA C: AGREGA Y QUITA POCOS ELEMENTOS DEL MISMO TIPO EN LA ESTRUCTURA DE DATOS EN ESTUDIO\n");
	
    /* Crear el árbol */
    abb_t *arbol = abb_crear(comparar_elementos);
	int vector_para_insertar_nodos[10] = {10,5,15,2,20,7,12,1,8,9};
	int mismo_vector_para_eliminar_nodos[10] = {10,9,8,5,2,1,15,12,20,7};
    int tamanio_vector = 10;
    bool validacion = true;

	pa2m_afirmar(
		abb_vacio(arbol) == true,
		"\tLa estructura de datos está vacía.\t\t\t\t\t\tabb_vacio(arbol) == true");

    /* Insertar elementos */
    for (size_t i = 0; i<10;i++){
		printf("\tInserto el elemento [%zu]= %d\n", i, vector_para_insertar_nodos[i]);
	    validacion &= abb_insertar(arbol, &vector_para_insertar_nodos[i]) == arbol;
	}

	pa2m_afirmar(
		validacion,
		"\tPuedo agregar el pocos elementos.\t\t\t\t\t\tabb_insertar(arbol, &vector_insersion[i]) == arbol");

	pa2m_afirmar(
		abb_tamanio(arbol) == tamanio_vector,
		"\tHaber insertado pocos elementos cambio el tamaño de la lista en la misma cantidad, abb_tamanio(arbol) == tamanio_vector");

    /* Eliminar elementos */
    char buffer[100];
    size_t tamanio_aux;

	for (size_t i = 0; i<10;i++){
        sprintf(buffer, "\tquito elemento el elemento: %d", mismo_vector_para_eliminar_nodos[i]);
        pa2m_afirmar(
        mismo_vector_para_eliminar_nodos[i] == *(int*)abb_quitar(arbol,&mismo_vector_para_eliminar_nodos[i]),
        buffer);
        tamanio_aux = abb_tamanio(arbol);
        pa2m_afirmar(
        (int)tamanio_aux == (int)tamanio_vector - (int)i - (int)1,
        "\t el nuevo tamanio se redujo en una unidad");
	}
	pa2m_afirmar(
		abb_vacio(arbol) == true,
		"\tLa estructura de datos está vacía.\t\t\t\t\t\tabb_vacio(arbol) == true");

    /* Destruir el árbol */
    abb_destruir(arbol);
}


/* Pruebas unitarias para la función abb_con_cada_elemento */
bool verificar_orden_creciente(void *elemento, void *aux) {
    int *valor = (int *)elemento;
    int *anterior = (int *)aux;

    if (*anterior <= *valor) {
        *(int *)aux = *(int*)elemento;
        return true;
    }
    return false;
}

bool verificar_puntero_array_y_array_tienen_mismos_elementos(void **puntero_array,int *array,size_t tamanio) {
    for (size_t i = 0; i < tamanio; i++) {
        int valor_array = array[i];
        int *valor_puntero = (int *)puntero_array[i];
        if (*valor_puntero != valor_array) {
            return false;
        }
    }
    return true;
}

void test_D_pruebas_abb_con_cada_elemento_y_recorrer() {
    pa2m_nuevo_grupo(
    "\nPRUEBA D: AGREGA Y RECORRE INORDER, PREORDER, POSTORDER LOS NODOS EN LA ESTRUCTURA DE DATOS EN ESTUDIO: \n");

    abb_t *arbol = abb_crear(comparar_elementos);
    size_t tamanio_array = 10;
    int vector_para_insertar_nodos[10] = {10, 5, 15, 2, 20, 7, 12, 1, 8, 9};
    int vector_recorrido_inorden[10] = {1, 2, 5, 7, 8, 9, 10, 12, 15, 20};
    int vector_recorrido_preorden[10] = {10, 5, 2, 1, 7, 8, 9, 15, 12, 20};
    int vector_recorrido_postorden[10] = {1, 2, 9, 8, 7, 5, 12, 20, 15, 10};
    void* puntero_array[10];

    for (size_t i = 0; i < 10; i++) {
        abb_insertar(arbol, &vector_para_insertar_nodos[i]);
    }

    int aux = 0;
    bool validado;
    size_t cuantos_se_recorrieron = 0;
    cuantos_se_recorrieron = abb_con_cada_elemento(arbol, INORDEN, verificar_orden_creciente, &aux);
    validado = (cuantos_se_recorrieron == abb_tamanio(arbol));
	pa2m_afirmar(
		validado,
		"\tabb_con_cada_elemento() recorre satisfactoriamente INORDEN todos los elementos del arbol");

    abb_recorrer(arbol, INORDEN, puntero_array, tamanio_array);
    validado = verificar_puntero_array_y_array_tienen_mismos_elementos(puntero_array, vector_recorrido_inorden, tamanio_array);
	pa2m_afirmar(
		validado,
		"\tabb_recorrer() recorre satisfactoriamente INORDEN todos los elementos del arbol");

    abb_recorrer(arbol, PREORDEN, puntero_array, tamanio_array);
    validado = verificar_puntero_array_y_array_tienen_mismos_elementos(puntero_array, vector_recorrido_preorden, tamanio_array);
	pa2m_afirmar(
		validado,
		"\tabb_recorrer() recorre satisfactoriamente PREORDEN todos los elementos del arbol");

    abb_recorrer(arbol, POSTORDEN, puntero_array, tamanio_array);
    validado = verificar_puntero_array_y_array_tienen_mismos_elementos(puntero_array, vector_recorrido_postorden, tamanio_array);
	pa2m_afirmar(
		validado,
		"\tabb_recorrer() recorre satisfactoriamente POSTORDEN todos los elementos del arbol");

    abb_destruir(arbol);
}

int main() {
    test_A_crea_y_destruye_estructura_vacia();
    test_B_agrega_y_quita_un_elemento();
    test_C_agrega_y_quita_pocos_elementos_distintos();
    test_D_pruebas_abb_con_cada_elemento_y_recorrer();
	return pa2m_mostrar_reporte();
}

