# Árbol Rojo-Negro

Un Árbol Rojo-Negro es un tipo de árbol binario de búsqueda auto-balanceado. Cada nodo del árbol tiene un bit extra de almacenamiento, que a menudo se interpreta como el color (rojo o negro) del nodo. Estas propiedades de color se utilizan para asegurar que el árbol permanezca aproximadamente balanceado durante las inserciones y eliminaciones.

## Propiedades

1.  Cada nodo es rojo o negro.
2.  La raíz es siempre negra.
3.  No hay dos nodos rojos adyacentes (un nodo rojo no puede tener un padre rojo ni un hijo rojo).
4.  Cada camino desde un nodo hasta cualquiera de sus descendientes `NULL` tiene el mismo número de nodos negros (la "altura negra").

Estas reglas garantizan que el camino más largo desde la raíz hasta cualquier hoja no es más del doble de largo que el camino más corto, manteniendo el árbol balanceado.

## Diferencias con otros árboles

- **vs. AVL:** Los árboles AVL están más estrictamente balanceados que los árboles Rojo-Negro. Esto conduce a búsquedas más rápidas en los árboles AVL, pero las inserciones y eliminaciones son más lentas debido a la mayor frecuencia de rotaciones. Los árboles Rojo-Negro son preferibles cuando las inserciones y eliminaciones son frecuentes.

## Recorridos
Los recorridos (In-order, Pre-order, Post-order) son los mismos que para un árbol binario de búsqueda estándar.

## Complejidad

| Operación | Complejidad |
|-----------|-------------|
| Búsqueda  | O(log n)    |
| Inserción | O(log n)    |
| Eliminación| O(log n)    |
