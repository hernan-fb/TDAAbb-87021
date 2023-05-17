# Árbol Binario de Búsqueda

Se pide implementar una Árbol Binario de Búsqueda (ABB) en el lenguaje
de programación C. Para ello se brindan las firmas de las funciones
públicas a implementar y **se deja a criterio del alumno la creación de
las funciones privadas del TDA** para el correcto funcionamiento del
**ABB** cumpliendo con las buenas prácticas de programación.
Adicionalmente se pide la creación de un iterador interno que sea capaz
de realizar diferentes recorridos en el árbol y una funcione que guarda
la información almacenada en el árbol en un vector.

El TDA entregado deberá compilar y **pasar las pruebas dispuestas por la 
cátedra sin errores**, adicionalmente estas pruebas deberán ser ejecutadas
sin pérdida de memoria.

A **modo de demostración**, se brindará al alumno un archivo simple de
"ejemplo". **Este archivo no es mas que un programa mínimo de ejemplo de
utilización del TDA a implementar** y es provisto sólo a fines
ilustrativos como una ayuda extra para entender el funcionamiento del
mismo. No es necesario modificar ni entregar el archivo de minidemo,
pero si la implementación es correcta, debería correr con valgrind sin
errores de memoria.

Para la resolución de este trabajo se recomienda utilizar una
**metodología orientada a pruebas**. A tal fín, se incluye un archivo
**pruebas_alumno.c** que debe ser completado con las pruebas pertinentes de
cada una de las diferentes primitivas del TDA. **El archivo de pruebas
forma parte de la entrega y por lo tanto de la nota final.** Aún mas
importante, las pruebas van a resultar fundamentales para lograr no
sólamente una implementación correcta, si no también una experiencia de
desarrollo menos turbulenta.

# Aclaraciones de la implementación

Esta implementación de **ABB** incluye una función de comparación que
permite insertar cualquier tipo de puntero en el mismo. **El ABB no
tiene idea de qué es lo que almacena el usuario**, simplemente es un
contenedor de datos que sigue reglas definidas. Mediante el comparador
el **ABB** es capaz de establecer la relación de orden de los diferentes
punteros, sin necesidad de tener información extra. **Recuerde que los
comparadores devuelven 0, >0 o <0** según la relación de los elementos comparados
(no necesariamente 0, 1, -1).

Otra característica distintiva de esta implementación es el uso de
**funciones de destrucción**. Recuerde que el **ABB** no es mas que un
contenedor de datos y no conoce nada acerca del contenido del mismo.
Recuerde también que en **C**, quien reserva la memoria es el
responsable de liberarla. Brindándole una función de destrucción al
**ABB**, podemos pedirle al mismo que se haga cargo de destruir los
elementos que almacena una vez que este es destruido. Tenga en cuenta
que si el usuario de la implementación no quiere delegar esta
responsabilidad al **ABB** puede pasarle una función de destrucción
**NULL** o directamente invocar al destructor simple.

Por último, tenga en cuenta que las pruebas de de la cátedra suponen
que la implementación acomoda **los elementos menores del ABB del lado
izquierdo y los mayores del lado derecho**, y que al borrar nodos con dos
hijos no nulos, **se reemplaza dicho nodo con el predecesor inorden**.

# Consejos para la elaboración del trabajo
**NO** escriba código a lo loco sin compilar cada tanto. Implemente la
solución de a poco y compilando a cada paso. Dejar la compilación para
el final es uno de los peores errores que puede cometer. Para la
compilación del trabajo se provee un **Makefile**. Utilice el comando
**make** frecuentemente para compilar y correr su programa.

**NO** avance en la implementación si le quedan errores sin resolver en
alguna prueba. Cada vez que escriba una prueba implemente toda la
funcionalidad necesaria para que funcione correctamente. Esto incluye
liberar memoria y accesos inválidos a la misma. Sólamente una vez que
haya logrado que la prueba pase exitosamente es que puede comenzar a
escribir la próxima prueba para continuar el trabajo.

**NO** está permitido modificar los archivos **.h**.

# Informe

-   Explique teóricamente qué es una árbol, árbol binario y árbol
    binario de búsqueda. Explique cómo funcionan, cuáles son sus operaciones básicas
    (incluyendo el análisis de complejidad de cada una de ellas) y por qué es
    importante la distinción de cada uno de estos diferentes tipos de
    árboles. Ayúdese con diagramas para explicar.

## 1. Arbol
Un árbol es una estructura de datos jerárquica compuesta por nodos interconectados. Cada nodo puede tener cero o más nodos hijos, excepto el nodo raíz, que es el nodo principal y no tiene un nodo padre.
## 2. Arbol Binario
Un árbol binario es un tipo especial de árbol en el que cada nodo tiene como máximo dos nodos hijos: un hijo izquierdo y un hijo derecho. Cada hijo puede ser un árbol binario en sí mismo. La estructura de un árbol binario se representa mediante enlaces o punteros entre los nodos.
## 3. ABB
Un árbol binario de búsqueda (ABB) es un tipo de árbol binario en el que se cumplen dos propiedades clave:
* La propiedad de ordenación: Para cada nodo en el árbol, todos los nodos en su subárbol izquierdo tienen un valor menor que el valor del nodo y todos los nodos en su subárbol derecho tienen un valor mayor que el valor del nodo.
* La propiedad de unicidad: No puede haber dos nodos con el mismo valor en el árbol. Esta propiedad a veces es cuestión de una convención.

El ABB se utiliza principalmente para almacenar elementos de forma ordenada, lo que permite realizar búsquedas eficientes, inserciones y eliminaciones. Al cumplir con la propiedad de ordenación, se puede aplicar una estrategia de búsqueda binaria para encontrar elementos en tiempo logarítmico, lo que lo hace más eficiente que otros tipos de estructuras de datos, como las listas enlazadas o los arreglos desordenados.

Operaciones básicas en un árbol binario de búsqueda:

1. **Inserción:** Permite agregar un nuevo elemento al árbol respetando la propiedad de ordenación. La complejidad en el peor caso es O(h), donde h es la altura del árbol. En un árbol balanceado, la altura es logarítmica, por lo que la inserción es eficiente.

2. **Búsqueda:** Permite buscar un elemento en el árbol. En el peor caso, la complejidad es O(h). Nuevamente, en un árbol balanceado, la altura crece logarítmicamente, lo que garantiza una búsqueda eficiente. Es decir que en el peor caso de un arbol balanceado la complejidad es de O(log(n))

3. **Eliminación:** Permite eliminar un elemento del árbol. La complejidad en el peor caso es O(h). Si el nodo a eliminar tiene dos hijos, se requiere una estrategia especial para mantener la propiedad de ordenación. En el peor caso de un arbol balanceado la complejidad es de O(log(n)).

-   Explique su implementación y decisiones de diseño (por ejemplo, si
    tal o cuál funciones se plantearon de forma recursiva, iterativa o
    mixta y por qué, que dificultades encontró al manejar los nodos y
    punteros, reservar y liberar memoria, etc).

- Para empezar quiero mencionar que una dificultad que tuve fue en los algoritmos de búsqueda porque en internet encontré que generalmente los tda arbol contienen en cada nodo un puntero al padre del nodo, lo cual facilita bastante el movimiento de nodos dentro del árbol. Sin ese puntero, tuve que rediseñar todos las funciones de búsqueda para que se manejen con el nodo padre en lugar de el nodo en interés. Más allá de este hecho, los problemas de diseño y las decisiones que tuve que tomar fueron en resumidas las siguientes ordenado por funciones del .h
- abb_crear:
Dificultad: Manejo de memoria.
Al diseñar esta función, una de las dificultades fue asegurarse de asignar correctamente la memoria para el árbol.
- abb_insertar:
Dificultad: Inserción recursiva.
Al implementar esta función, una dificultad fue decidir si la inserción se realizaría de forma recursiva, iterativa o mixta. Se optó por una inserción recursiva para mantener la estructura de árbol binario de búsqueda. Sin embargo, esto planteó el desafío de manejar correctamente los nodos y punteros para asegurar que los elementos se insertaran en el lugar correcto según el comparador proporcionado.
- abb_quitar:
Dificultad: Eliminación de nodos con dos hijos.
Al diseñar esta función, se encontró una dificultad específica al tratar de eliminar nodos que tienen dos hijos. La estrategia seleccionada fue reemplazar el nodo con su predecesor inorden, lo cual implicó ajustar los punteros del ABB. Esto requirió un manejo de los nodos y punteros para garantizar que la estructura del árbol se mantuviera correctamente después de la eliminación.
- abb_buscar:
Dificultad: Búsqueda y comparación de elementos.
Durante la implementación de esta función, la dificultad que surgió fue bastante similar a la de las otras funciones de búsqueda / recorrido del ABB. En este caso implicó comparar los elementos a medida que se recorría el ABB y asegurarse de que se encontrara el elemento correcto. Además, se debió tener en cuenta el manejo de punteros y nodos para avanzar correctamente en el árbol durante la búsqueda.
- abb_con_cada_elemento y abb_recorrer:
Dificultad: Recorrido del árbol y control del flujo. De las más difíciles de implementar y hacer pasar las pruebas.
Al implementar esta función, se encontró la dificultad de realizar el recorrido del árbol según el tipo de recorrido especificado y llamar a la función proporcionada con cada elemento. Además, se requería controlar el flujo del recorrido, deteniéndolo si la función devolvía false y continuándolo si devolvía true. Esto fue bastante dificil porque para los distintos tipos de recorrido el punto de retorno puede desembocar en distintos resultados, con lo cual hubo que apuntar bastantes veces estas funciones. También fue necesario manejar adecuadamente los punteros y nodos para garantizar un recorrido correcto y evitar accesos inválidos a la memoria.

##Ejemplos diagramas primitivas
-Inserción: Inserción de un nuevo nodo en un árbol con varios nodos
Antes de la inserción:
       5
      / \
    3    8
   / \   /
  2   4 7
Después de la inserción del nodo 6:
       5
      / \
    3    8
   / \   /
  2   4 7
         \
          6
.Quitar nodo: utilizando la función abb_quitar

Antes de la eliminación:
       5
      / \
    3    8
   / \   /
  2   4 7
Después de eliminar el nodo 3:
       5
      / \
    2    8
     \   /
      4 7
En este caso, se eliminó el nodo 3 del árbol y se ajustaron los nodos para mantener la propiedad de orden del árbol binario de búsqueda. Según las reglas de reemplazo de nodos, en este ejemplo, el nodo 3 tenía dos hijos (2 y 4), por lo que se reemplazó por su predecesor inorden (el nodo 2 en este caso).