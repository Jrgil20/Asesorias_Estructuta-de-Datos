# Árbol AVL

Un Árbol AVL (Adelson-Velsky y Landis) es el primer árbol binario de búsqueda auto-balanceado inventado. En un árbol AVL, las alturas de los dos subárboles hijos de cualquier nodo difieren como máximo en uno. Si en algún momento difieren en más de uno, se realizan rebalanceos (rotaciones) para restaurar esta propiedad.

## Factor de Balance

El factor de balance de un nodo es la diferencia de altura entre su subárbol izquierdo y su subárbol derecho.
`FactorBalance = altura(subárbol_izquierdo) - altura(subárbol_derecho)`
Para un árbol AVL, el factor de balance de cada nodo debe estar en el rango [-1, 1, 0].

## Rotaciones

Cuando el árbol se desequilibra, se realizan rotaciones para restaurar el balance. Hay cuatro tipos de rotaciones:

1.  **Rotación Izquierda-Izquierda (LL):** Se realiza una rotación simple a la derecha.
2.  **Rotación Derecha-Derecha (RR):** Se realiza una rotación simple a la izquierda.
3.  **Rotación Izquierda-Derecha (LR):** Se realiza una rotación a la izquierda seguida de una rotación a la derecha.
4.  **Rotación Derecha-Izquierda (RL):** Se realiza una rotación a la derecha seguida de una rotación a la izquierda.

## Diferencias con otros árboles

- **vs. BST:** A diferencia de un BST, un AVL siempre está balanceado, lo que garantiza un rendimiento de O(log n) en el peor de los casos para búsquedas, inserciones y eliminaciones.
- **vs. Árbol Rojo-Negro:** Los AVL están más estrictamente balanceados. Esto puede llevar a búsquedas más rápidas, pero a costa de operaciones de inserción y eliminación más complejas y costosas.

## Complejidad

| Operación | Complejidad |
|-----------|-------------|
| Búsqueda  | O(log n)    |
| Inserción | O(log n)    |
| Eliminación| O(log n)    |
