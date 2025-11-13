# Tablas Hash (Hash Tables)

## ¿Qué es?

Una **tabla hash** es una estructura de datos que permite almacenar y buscar información de forma muy rápida usando una **función hash** que convierte claves en índices de un arreglo.

**Analogía**: Como un diccionario donde en lugar de buscar página por página, calculas directamente dónde está la palabra.

---

## Conceptos Clave

### Componentes

- **Clave**: Identificador único (ej: "Juan")
- **Valor**: Dato almacenado (ej: edad = 25)
- **Función Hash**: Convierte clave → índice
- **Colisión**: Cuando dos claves generan el mismo índice

### Complejidad

| Operación | Promedio | Peor Caso |
|-----------|----------|-----------|
| Búsqueda  | O(1)     | O(n)      |
| Inserción | O(1)     | O(n)      |

---

## Resolución de Colisiones

### 1. Encadenamiento (Chaining)

Cada índice tiene una lista enlazada.

``` c
Índice 3: ["gato"] → ["perro"] → NULL
```

### 2. Direccionamiento Abierto

Se busca la siguiente posición libre.

```c
indice = (hash + i) % tamaño  // Sondeo lineal
```

---

## Implementación Básica (C)

```c
#define TAM 10

typedef struct Nodo {
    char* clave;
    int valor;
    struct Nodo* siguiente;
} Nodo;

typedef struct {
    Nodo* tabla[TAM];
} TablaHash;

int hash(char* clave) {
    int suma = 0;
    for (int i = 0; clave[i]; i++) 
        suma += clave[i];
    return suma % TAM;
}

void insertar(TablaHash* th, char* clave, int valor) {
    int idx = hash(clave);
    Nodo* nuevo = malloc(sizeof(Nodo));
    nuevo->clave = strdup(clave);
    nuevo->valor = valor;
    nuevo->siguiente = th->tabla[idx];
    th->tabla[idx] = nuevo;
}
```

---

## Visualizadores Interactivos

### 🎯 Recomendados

- **[USFCA - Hash Tables](https://www.cs.usfca.edu/~galles/visualization/OpenHash.html)** - Encadenamiento
- **[USFCA - Open Addressing](https://www.cs.usfca.edu/~galles/visualization/ClosedHash.html)** - Direccionamiento abierto
- **[VisuAlgo](https://visualgo.net/en/hashtable)** - Comparación de métodos
- **[CS Animations](https://www.cs.usfca.edu/~galles/visualization/Algorithms.html)** - Colección completa

---

## Referencias Adicionales

### Videos

- **[Hash Tables - CS50](https://www.youtube.com/watch?v=nvzVHwrrub0)** - Explicación clara y concisa
- **[Hash Table Animation](https://www.youtube.com/watch?v=KyUTuwz_b7Q)** - Visualización animada

### Tutoriales

- **[GeeksforGeeks - Hashing](https://www.geeksforgeeks.org/hashing-data-structure/)** - Teoría completa
- **[Programiz - Hash Table](https://www.programiz.com/dsa/hash-table)** - Con código en C

### Documentación

- **[Wikipedia - Hash Table](https://en.wikipedia.org/wiki/Hash_table)** - Referencia técnica detallada
- **[CP-Algorithms](https://cp-algorithms.com/data_structures/disjoint_set_union.html)** - Para problemas competitivos

### Libros (secciones recomendadas)

- *Introduction to Algorithms (CLRS)* - Capítulo 11
- *Data Structures and Algorithm Analysis in C* (Weiss) - Capítulo 5


