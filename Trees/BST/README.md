# Árbol Binario de Búsqueda (BST)

Un Árbol Binario de Búsqueda (BST) es una estructura de datos de árbol basada en nodos donde cada nodo tiene un valor comparable, a veces llamado clave. El valor de un nodo es mayor que el valor de cada nodo en su subárbol izquierdo y menor que el valor de cada nodo en su subárbol derecho.

## Propiedades

- El subárbol izquierdo de un nodo contiene solo nodos con claves menores que la clave del nodo.
- El subárbol derecho de un nodo contiene solo nodos con claves mayores que la clave del nodo.
- Los subárboles izquierdo y derecho también deben ser árboles binarios de búsqueda.
- No debe haber nodos duplicados.

## Recorridos Clave

### In-order (En orden)
Visita el subárbol izquierdo, luego el nodo raíz, y finalmente el subárbol derecho. Para un BST, este recorrido visita los nodos en orden ascendente.
**Secuencia:** Izquierda, Raíz, Derecha.

### Pre-order (Preorden)
Visita el nodo raíz, luego el subárbol izquierdo, y finalmente el subárbol derecho.
**Secuencia:** Raíz, Izquierda, Derecha.

### Post-order (Postorden)
Visita el subárbol izquierdo, luego el subárbol derecho, y finalmente el nodo raíz.
**Secuencia:** Izquierda, Derecha, Raíz.

## Complejidad

| Operación | Complejidad Promedio | Complejidad en el Peor Caso |
|-----------|----------------------|-----------------------------|
| Búsqueda  | O(log n)             | O(n)                        |
| Inserción | O(log n)             | O(n)                        |
| Eliminación| O(log n)             | O(n)                        |

El peor caso ocurre cuando el árbol se desequilibra y se asemeja a una lista enlazada.
