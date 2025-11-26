# Ejercicios de Casos Edge - Árboles y Tablas Hash

Este directorio contiene ejercicios interactivos diseñados para explotar cada uno de los **casos edge** (casos límite) en estructuras de datos de árboles y tablas hash.

## 📋 Contenido

### Árboles (Trees/Ejercicios/)

| Archivo | Estructura | Casos Edge Cubiertos |
|---------|------------|---------------------|
| `ejercicios_AVL_casos_edge.cpp` | Árbol AVL | Rotaciones LL, RR, LR, RL; Eliminaciones con rebalanceo |
| `ejercicios_BST_casos_edge.cpp` | Árbol BST | Árboles degenerados, eliminación de nodos con 0/1/2 hijos |
| `ejercicios_RedBlack_casos_edge.cpp` | Árbol Rojo-Negro | Recoloreo, rotaciones, propagación hacia raíz |
| `ejercicios_BTree_casos_edge.cpp` | Árbol B | Split de nodos, merge, préstamo entre hermanos |

### Tablas Hash (HashTables/Ejercicios/)

| Archivo | Estructura | Casos Edge Cubiertos |
|---------|------------|---------------------|
| `ejercicios_HashTable_casos_edge.cpp` | Tabla Hash | Colisiones, clustering, tombstones, factor de carga |

---

## 🎯 Objetivos de Aprendizaje

### Árboles AVL
Los ejercicios de AVL están diseñados para forzar cada tipo de rotación:

1. **Caso LL (Left-Left)**: Secuencia `30, 20, 10` - Rotación simple derecha
2. **Caso RR (Right-Right)**: Secuencia `10, 20, 30` - Rotación simple izquierda
3. **Caso LR (Left-Right)**: Secuencia `30, 10, 20` - Rotación doble (izq + der)
4. **Caso RL (Right-Left)**: Secuencia `10, 30, 20` - Rotación doble (der + izq)

### Árboles BST
Los ejercicios de BST demuestran:

1. **Árbol degenerado**: Insertar en orden creciente/decreciente crea una "lista"
2. **Eliminación de nodo hoja**: Caso más simple
3. **Eliminación con un hijo**: Reemplazar con el hijo
4. **Eliminación con dos hijos**: Buscar sucesor inorden

### Árboles Rojo-Negro
Los ejercicios demuestran los casos de balanceo:

1. **Caso 1 - Tío rojo**: Solo recolorear
2. **Caso 2 y 3 - Tío negro**: Rotaciones necesarias
3. **Propagación**: Recoloreo que se propaga hacia la raíz

### Árboles B
Los ejercicios demuestran:

1. **Split (División)**: Cuando un nodo está lleno
2. **Merge (Fusión)**: Cuando un nodo tiene pocas claves
3. **Préstamo**: Redistribución de claves entre hermanos

### Tablas Hash
Los ejercicios demuestran:

1. **Colisiones**: Múltiples claves con mismo hash
2. **Encadenamiento vs Sondeo**: Diferentes resoluciones de colisión
3. **Clustering**: Problema de agrupamiento en sondeo lineal
4. **Tombstones**: Marcadores de eliminación en sondeo abierto
5. **Factor de carga**: Impacto en rendimiento

---

## 🔧 Compilación y Ejecución

### Compilar un ejercicio:

```bash
# Ejemplo para AVL
g++ -o avl Trees/Ejercicios/ejercicios_AVL_casos_edge.cpp
./avl

# Ejemplo para Hash Tables
g++ -o hash HashTables/Ejercicios/ejercicios_HashTable_casos_edge.cpp
./hash
```

### Compilar todos:

```bash
# Desde la raíz del repositorio
g++ -o avl Trees/Ejercicios/ejercicios_AVL_casos_edge.cpp
g++ -o bst Trees/Ejercicios/ejercicios_BST_casos_edge.cpp
g++ -o redblack Trees/Ejercicios/ejercicios_RedBlack_casos_edge.cpp
g++ -o btree Trees/Ejercicios/ejercicios_BTree_casos_edge.cpp
g++ -o hashtable HashTables/Ejercicios/ejercicios_HashTable_casos_edge.cpp
```

---

## 📖 Guía de Uso

Cada programa presenta un **menú interactivo**:

```
[MENÚ DE EJERCICIOS]
1.  Caso LL (Left-Left) - Rotación simple derecha
2.  Caso RR (Right-Right) - Rotación simple izquierda
...
0.  Ejecutar todos los ejercicios

Selecciona un ejercicio (0-12):
```

- Selecciona `0` para ejecutar **todos los ejercicios** secuencialmente
- Selecciona un número específico para ver un **caso particular**

---

## 📝 Secuencias de Ejemplo

### AVL - Forzar Rotación LL (Izquierda-Izquierda)
```
Insertar: 30, 20, 10

     30          20
    /           /  \
   20    →    10    30
  /
 10
```

### AVL - Forzar Rotación LR (Izquierda-Derecha)
```
Insertar: 30, 10, 20

   30          30          20
  /           /           /  \
 10    →    20    →    10    30
   \       /
    20    10
```

### Hash - Colisión con Sondeo Lineal
```
Tabla tamaño 10
Insertar: 5, 15, 25, 35 (todos hash a índice 5)

[5]: 5
[6]: 15  (colisión, sondeo a 5+1)
[7]: 25  (colisión, sondeo a 5+2)
[8]: 35  (colisión, sondeo a 5+3)
```

---

## 🔍 Visualización

Cada ejercicio muestra:

1. **Estado inicial** del árbol/tabla
2. **Operación realizada** (inserción/eliminación)
3. **Caso detectado** (tipo de rotación, colisión, etc.)
4. **Estado final** con visualización gráfica

Ejemplo de salida para AVL:
```
[CASO LL] Balance=2 en nodo 30
  >> Ejecutando ROTACIÓN DERECHA en nodo 30

Estructura del árbol:
└── 20 (h=2, b=0)
    ├── 10 (h=1, b=0)
    └── 30 (h=1, b=0)
```

---

## 📚 Referencias

- [Visualizador de AVL](https://www.cs.usfca.edu/~galles/visualization/AVLtree.html)
- [Visualizador de Rojo-Negro](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)
- [Visualizador de B-Tree](https://www.cs.usfca.edu/~galles/visualization/BTree.html)
- [Visualizador de Hash Tables](https://www.cs.usfca.edu/~galles/visualization/OpenHash.html)
