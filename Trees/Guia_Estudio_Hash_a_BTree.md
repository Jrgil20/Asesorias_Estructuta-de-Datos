# Guía intuitiva: de Hash Tables a B-Trees (con enfoque en C++)

Este plan de estudio está estructurado secuencialmente para construir el conocimiento desde la gestión de memoria directa (Hash) hasta las estructuras jerárquicas balanceadas (Árboles).  
Al ser conceptos de ingeniería, el enfoque está en la mecánica de los punteros/referencias y el costo computacional.

---

## Módulo 1: Tablas Hash (Mapas de dispersión)

El objetivo es comprender cómo transformar una clave en un índice de memoria para lograr accesos en \(O(1)\) promedio, y cómo resolver las colisiones cuando dos claves generan el mismo índice.

### Hashing Abierto (Encadenamiento Separado)

- **Concepto:** El arreglo principal no guarda los elementos directamente, sino punteros a listas enlazadas (o árboles). Si hay colisión, el nuevo elemento se añade a la lista correspondiente a ese índice.
- **Insertar:** Se calcula el hash de la clave para obtener el índice \(i\). Se inserta el nodo al principio o final de la lista enlazada en `arreglo[i]`.
- **Eliminar:** Se calcula el índice, se recorre la lista enlazada buscando la clave y se reasignan los punteros para extraer el nodo.

### Hashing Cerrado (Direccionamiento Abierto)

- **Concepto:** Todos los elementos se almacenan en el mismo arreglo. Si hay colisión, se busca la siguiente celda libre usando una secuencia de sondeo (Sondeo Lineal, Cuadrático o Doble Hashing).
- **Insertar:** Calcular índice. Si está ocupado, aplicar la función de sondeo hasta encontrar un espacio vacío (`nullptr` o `tombstone`).
- **Eliminar (Lápidas / Tombstones):** **Concepto crítico.** No se puede simplemente borrar el elemento (`nullptr`), ya que rompería la cadena de búsqueda para elementos que colisionaron y se insertaron después. Se debe marcar la celda con una bandera especial (`isDeleted`).

```cpp
// Frame: Resolución de colisión por Sondeo Lineal (Hashing Cerrado)
int search(int key) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (table[index] != NULL) {
        if (table[index]->key == key && !table[index]->isDeleted)
            return table[index]->value;

        index = (index + 1) % TABLE_SIZE; // Sondeo lineal
        if (index == originalIndex) break; // Vuelta completa
    }
    return -1; // No encontrado
}
```

---

## Módulo 2: Árbol Binario de Búsqueda (BST)

El BST es la base estructural. Su rendimiento depende de que los datos no se inserten ordenados, para evitar que se degenere en una lista enlazada (\(O(n)\)).

- **Concepto:** Cada nodo tiene máximo dos hijos. El subárbol izquierdo contiene valores menores que la raíz; el derecho, valores mayores. Las búsquedas toman \(O(h)\), donde \(h\) es la altura.
- **Insertar:** Se compara el valor con la raíz. Si es menor, se navega a la izquierda; si es mayor, a la derecha. Se repite hasta encontrar un puntero `nullptr` y allí se enlaza el nuevo nodo.
- **Eliminar (3 casos):**
  1. **Nodo hoja:** Simplemente se elimina y se actualiza el puntero del padre a `nullptr`.
  2. **Nodo con 1 hijo:** Se elimina el nodo y se enlaza su padre directamente con su único hijo.
  3. **Nodo con 2 hijos:** Se busca el **sucesor in-order** (el valor más pequeño del subárbol derecho) o el **predecesor in-order** (el más grande del izquierdo). Se copia ese valor al nodo actual y luego se elimina el sucesor/predecesor original (que cae en caso 1 o 2).

```cpp
// Frame: Inserción recursiva clásica en BST
Node* insert(Node* root, int key) {
    if (root == nullptr) return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}
```

---

## Módulo 3: Árboles Autorbalanceables (en memoria)

Aquí el objetivo es dominar las **rotaciones**. Ambos árboles garantizan operaciones en \(O(\log n)\) manteniendo la altura controlada.

### AVL Tree (Balanceo estricto)

- **Concepto:** Mantiene un factor de balance (`altura_izq - altura_der`) que solo puede ser -1, 0 o 1 en cada nodo.
- **Insertar/Eliminar:** Se opera como BST regular. Luego se recalcula el factor de balance subiendo hacia la raíz. Si un nodo se desbalancea, se aplica una rotación (LL, RR, LR o RL).
- **Ventaja:** Consultas muy rápidas por su baja altura.

### Red-Black Tree (Balanceo relajado)

- **Concepto:** Usa propiedades de color (Rojo/Negro) para asegurar que el camino más largo de la raíz a una hoja no sea más del doble del más corto.
  - La raíz es negra.
  - Los nodos rojos no pueden tener hijos rojos.
  - Todos los caminos desde un nodo a sus hojas tienen igual cantidad de nodos negros (black-height).
- **Insertar/Eliminar:** Se inserta como BST pintando de rojo. Luego se corrige con **recoloreo** y, si no basta, con **rotaciones**.
- **Ventaja:** Menos rotaciones que AVL durante inserciones/eliminaciones; buena opción con alta escritura.

```cpp
// Frame: Rotación a la Derecha (Core para AVL y Red-Black)
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Realizar rotación
    x->right = y;
    y->left = T2;

    // (En AVL aquí se actualizarían las alturas)
    return x; // Nueva raíz del subárbol
}
```

---

## Módulo 4: B-Tree (Orientado a disco)

A diferencia de los árboles binarios, los B-Trees están diseñados para aprovechar la arquitectura del hardware, minimizando lecturas de disco (I/O) al hacer que el tamaño del nodo coincida con el tamaño de página (por ejemplo, 4KB).

- **Concepto:** Árbol de búsqueda n-ario y auto-balanceado. Un nodo puede contener múltiples claves y múltiples hijos. Todas las hojas están en el mismo nivel.
- **Insertar:** Siempre se inserta en una hoja. Si se llena, ocurre un **split**: el nodo se divide y la clave mediana sube al padre. Si el padre se llena, el split se propaga hacia arriba.
- **Eliminar:** Si un nodo cae por debajo del mínimo de claves, ocurre **underflow**. Se intenta **pedir prestado** a un hermano; si no es posible, se hace **merge** con un hermano y baja una clave desde el padre.

```cpp
// Frame: Estructura conceptual de un Nodo en B-Tree
struct BTreeNode {
    int *keys;          // Arreglo de claves
    int t;              // Grado mínimo (define rango de claves)
    BTreeNode **C;      // Arreglo de punteros a los hijos
    int n;              // Cantidad actual de claves
    bool leaf;          // ¿Es una hoja?
};
```

---

## Desglose de mecánicas de reestructuración (C++)

Esta sección aterriza las operaciones críticas que realmente mantienen el rendimiento logarítmico.

### 1) AVL: detectar patrón y rotar

Idea mental:
- Si el desbalance ocurre por la izquierda de la izquierda: **LL**.
- Si ocurre por la derecha de la derecha: **RR**.
- Si es zig-zag izquierda-derecha: **LR**.
- Si es zig-zag derecha-izquierda: **RL**.

```cpp
// Frame: Rebalanceo AVL tras insertar
Node* rebalance(Node* node, int key) {
    int bf = height(node->left) - height(node->right);

    // LL
    if (bf > 1 && key < node->left->key) return rightRotate(node);
    // RR
    if (bf < -1 && key > node->right->key) return leftRotate(node);
    // LR
    if (bf > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL
    if (bf < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
```

### 2) B-Tree: split de un hijo lleno

Idea mental:
- Nunca bajes a un hijo lleno sin antes dividirlo.
- Promueves la mediana al padre.
- Redistribuyes claves e hijos en dos nodos hermanos.

```cpp
// Frame: Split de hijo lleno en B-Tree (esquema clásico)
void splitChild(BTreeNode* parent, int i, BTreeNode* fullChild) {
    BTreeNode* z = new BTreeNode(fullChild->t, fullChild->leaf);
    z->n = fullChild->t - 1;

    // Copiar segunda mitad de claves al nuevo nodo
    for (int j = 0; j < fullChild->t - 1; j++)
        z->keys[j] = fullChild->keys[j + fullChild->t];

    // Copiar hijos si no es hoja
    if (!fullChild->leaf)
        for (int j = 0; j < fullChild->t; j++)
            z->C[j] = fullChild->C[j + fullChild->t];

    fullChild->n = fullChild->t - 1;

    // Mover hijos del padre para abrir espacio
    for (int j = parent->n; j >= i + 1; j--)
        parent->C[j + 1] = parent->C[j];
    parent->C[i + 1] = z;

    // Mover claves del padre para insertar mediana
    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[i] = fullChild->keys[fullChild->t - 1];

    parent->n += 1;
}
```

### 3) B-Tree: merge cuando no se puede prestar

Idea mental:
- Tomas una clave del padre.
- Unes dos hermanos alrededor de esa clave.
- Reduces cantidad de hijos en el padre.

```cpp
// Frame: Merge conceptual de dos hijos consecutivos en B-Tree
void merge(BTreeNode* parent, int idx) {
    BTreeNode* left = parent->C[idx];
    BTreeNode* right = parent->C[idx + 1];
    int t = left->t;

    // Baja la clave separadora del padre
    left->keys[t - 1] = parent->keys[idx];

    // Copia claves del hermano derecho
    for (int i = 0; i < right->n; i++)
        left->keys[i + t] = right->keys[i];

    // Copia hijos del hermano derecho
    if (!left->leaf)
        for (int i = 0; i <= right->n; i++)
            left->C[i + t] = right->C[i];

    left->n += right->n + 1;

    // Cierra huecos en el padre
    for (int i = idx + 1; i < parent->n; i++)
        parent->keys[i - 1] = parent->keys[i];
    for (int i = idx + 2; i <= parent->n; i++)
        parent->C[i - 1] = parent->C[i];

    parent->n--;
    delete right;
}
```

---

## Recomendación de práctica

1. Implementa primero BST y valida inserción/búsqueda/eliminación.
2. Reutiliza su base para AVL y verifica manualmente cada caso LL, RR, LR, RL.
3. Pasa a B-Tree con foco en `splitChild`, luego inserción completa, y por último eliminación con préstamo/merge.
4. Mide operaciones y altura para observar por qué cada estructura cumple (o no) su complejidad esperada.
