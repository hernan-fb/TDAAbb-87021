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

    /* Insertar elementos */
    int elem1 = 1;
    int elem2 = 2;
    int elem3 = 3;
    int elem4 = 4;
    printf("Inserto el elmento: 2\n");
    arbol = abb_insertar(arbol, &elem2);
    printf("Inserto el elmento: 1\n");
    arbol = abb_insertar(arbol, &elem1);
    printf("Inserto el elmento: 4\n");
    arbol = abb_insertar(arbol, &elem4);
    printf("Inserto el elmento: 3\n");
    arbol = abb_insertar(arbol, &elem3);

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
    abb_quitar(arbol, &elem3);
    printf("Tamaño del árbol después de eliminar un elemento: %zu\n", abb_tamanio(arbol));

    /* Destruir el árbol */
    abb_destruir(arbol);

    return 0;
}