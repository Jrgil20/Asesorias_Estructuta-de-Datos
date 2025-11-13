# Árbol B (B-Tree)

Un Árbol B es una estructura de datos de árbol auto-balanceada que generaliza el árbol binario de búsqueda, permitiendo nodos con más de dos hijos. A diferencia de otros árboles auto-balanceados, los Árboles B son adecuados para sistemas de almacenamiento que leen y escriben grandes bloques de datos, como discos duros.

## Propiedades

- Los datos se mantienen ordenados.
- Todos los nodos hoja están a la misma altura.
- Un nodo puede tener un número variable de hijos, dentro de un rango predefinido.
- El número de claves en un nodo está relacionado con el número de hijos.

Estas propiedades reducen la altura del árbol y el número de accesos a disco necesarios para encontrar un elemento.

## Orden del Árbol B

Un Árbol B de orden `m` tiene las siguientes propiedades:
1.  Cada nodo tiene como máximo `m` hijos.
2.  Cada nodo interno (excepto la raíz) tiene al menos `⌈m/2⌉` hijos.
3.  La raíz tiene al menos 2 hijos si no es un nodo hoja.
4.  Un nodo no hoja con `k` hijos contiene `k-1` claves.
5.  Todos los nodos hoja aparecen en el mismo nivel.

## Diferencias con otros árboles

- **vs. Árboles Binarios (BST, AVL, Rojo-Negro):** Los Árboles B no son binarios. Están optimizados para accesos a disco, agrupando un gran número de claves en un solo nodo para minimizar las lecturas de disco. Los árboles binarios están optimizados para datos en memoria.

## Complejidad

| Operación | Complejidad |
|-----------|-------------|
| Búsqueda  | O(log n)    |
| Inserción | O(log n)    |
| Eliminación| O(log n)    |

Aunque la complejidad es la misma, el `log` en los Árboles B tiene una base mucho mayor (relacionada con el número de hijos por nodo), lo que resulta en árboles mucho más anchos y menos profundos.
