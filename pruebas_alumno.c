#include "pa2m.h"
#include "src/abb.h"
//typedef enum { INORDEN, PREORDEN, POSTORDEN } abb_recorrido;

/* Función auxiliar para imprimir elementos */
bool imprimir_elemento(void *elemento, void *aux) {
    int *elem = (int*) elemento;
    printf("%d - ", *elem);
	return true;
}

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

int main() {
    /* Crear el árbol */
    abb_t *arbol = abb_crear(comparar_elementos);
	//int vector[12] = {10,5,15,2,20,7,12,1,8,22,0,9};
	int vector_reordenado[12] = {10,9,8,5,2,1,15,12,20,0,22,7};
    /* Insertar elementos */
    int elem1 = 10;
    int elem2 = 5;
    int elem3 = 15;
    int elem4 = 2;
    int elem5 = 20;
    int elem6 = 7;
    int elem7 = 12;
    int elem8 = 1;
    int elem9 = 8;
    int elem10 = 9;
    printf("Inserto el elmento: 10\n");
    arbol = abb_insertar(arbol, &elem1);
    printf("Inserto el elmento: 5\n");
    arbol = abb_insertar(arbol, &elem2);
    printf("Inserto el elmento: 15\n");
    arbol = abb_insertar(arbol, &elem3);
    printf("Inserto el elmento: 2\n");
    arbol = abb_insertar(arbol, &elem4);
    printf("Inserto el elmento: 20\n");
    arbol = abb_insertar(arbol, &elem5);
    printf("Inserto el elmento: 7\n");
    arbol = abb_insertar(arbol, &elem6);
    printf("Inserto el elmento: 12\n");
    arbol = abb_insertar(arbol, &elem7);
    printf("Inserto el elmento: 1\n");
    arbol = abb_insertar(arbol, &elem8);
    printf("Inserto el elmento: 8\n");
    arbol = abb_insertar(arbol, &elem9);
    printf("Inserto el elmento: 9\n");
    arbol = abb_insertar(arbol, &elem10);

    /* Verificar tamaño y si está vacío */
    printf("Tamaño del árbol: %zu\n", abb_tamanio(arbol));
    printf("El árbol está vacío: %s\n", abb_vacio(arbol)?"true":"false");

    /* Buscar elementos */
    int *elem_buscado = abb_buscar(arbol, &elem3);
    if (elem_buscado == NULL) {
        printf("El elemento no se encuentra en el árbol\n");
    } else {
        printf("El elemento encontrado es: %d\n", *elem_buscado);
    }

    /* Recorrer el árbol con una función auxiliar */
    printf("Recorrido en orden del árbol: ");
    abb_con_cada_elemento(arbol, PREORDEN, imprimir_elemento, NULL);
    printf("\n");

    /* Eliminar elementos */
	printf("eliminar elementos:\n");
	for (size_t i = 0; i<11;i++){
		printf("\nquito elemento [%zu]= %d\n", i, vector_reordenado[i]);
	    abb_quitar(arbol, &vector_reordenado[i]);
    	abb_con_cada_elemento(arbol, PREORDEN, imprimir_elemento, NULL);
    	printf("Tamaño del árbol después de eliminar un elemento: %zu\n", abb_tamanio(arbol));
	}

    /* Destruir el árbol */
    abb_destruir(arbol);

    return 0;
}