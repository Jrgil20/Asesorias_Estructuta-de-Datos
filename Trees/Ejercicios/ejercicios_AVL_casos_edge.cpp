/*
 * EJERCICIOS DE CASOS EDGE EN ÁRBOLES AVL
 * =========================================
 * 
 * Este archivo contiene ejercicios diseñados para explotar cada uno de los casos
 * edge en árboles AVL, específicamente las 4 rotaciones y casos de eliminación.
 * 
 * TIPOS DE ROTACIONES:
 * 1. Rotación LL (Left-Left) - Rotación simple a la derecha
 * 2. Rotación RR (Right-Right) - Rotación simple a la izquierda
 * 3. Rotación LR (Left-Right) - Doble rotación (izquierda + derecha)
 * 4. Rotación RL (Right-Left) - Doble rotación (derecha + izquierda)
 * 
 * Para cada ejercicio se proporciona:
 * - La secuencia de números a insertar/eliminar
 * - El caso edge que se activa
 * - Una explicación del estado del árbol
 */

#include <iostream>
#include <algorithm>
#include <string>

struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
};

int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

Node *rightRotate(Node *y) {
    std::cout << "  >> Ejecutando ROTACIÓN DERECHA en nodo " << y->key << std::endl;
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

Node *leftRotate(Node *x) {
    std::cout << "  >> Ejecutando ROTACIÓN IZQUIERDA en nodo " << x->key << std::endl;
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node* insert(Node* node, int key) {
    if (node == NULL) {
        std::cout << "  Insertando: " << key << std::endl;
        return(newNode(key));
    }

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // Caso Left-Left (LL)
    if (balance > 1 && key < node->left->key) {
        std::cout << "  [CASO LL] Balance=" << balance << " en nodo " << node->key << std::endl;
        return rightRotate(node);
    }

    // Caso Right-Right (RR)
    if (balance < -1 && key > node->right->key) {
        std::cout << "  [CASO RR] Balance=" << balance << " en nodo " << node->key << std::endl;
        return leftRotate(node);
    }

    // Caso Left-Right (LR)
    if (balance > 1 && key > node->left->key) {
        std::cout << "  [CASO LR] Balance=" << balance << " en nodo " << node->key << std::endl;
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Right-Left (RL)
    if (balance < -1 && key < node->right->key) {
        std::cout << "  [CASO RL] Balance=" << balance << " en nodo " << node->key << std::endl;
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        std::cout << "  Eliminando: " << key << std::endl;
        
        // Nodo con un hijo o sin hijos
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                std::cout << "  [Caso: nodo hoja sin hijos]" << std::endl;
                temp = root;
                root = NULL;
            } else {
                std::cout << "  [Caso: nodo con un hijo]" << std::endl;
                *root = *temp;
            }
            delete temp;
        } else {
            std::cout << "  [Caso: nodo con dos hijos]" << std::endl;
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + std::max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Rotaciones después de eliminar
    if (balance > 1 && getBalance(root->left) >= 0) {
        std::cout << "  [ELIMINACIÓN - CASO LL]" << std::endl;
        return rightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        std::cout << "  [ELIMINACIÓN - CASO LR]" << std::endl;
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        std::cout << "  [ELIMINACIÓN - CASO RR]" << std::endl;
        return leftRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        std::cout << "  [ELIMINACIÓN - CASO RL]" << std::endl;
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preOrder(Node *root) {
    if (root != NULL) {
        std::cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        std::cout << root->key << " ";
        inOrder(root->right);
    }
}

void printTree(Node *root, const std::string& prefix = "", bool isLeft = true) {
    if (root != NULL) {
        std::cout << prefix;
        std::cout << (isLeft ? "├── " : "└── ");
        std::cout << root->key << " (h=" << root->height << ", b=" << getBalance(root) << ")" << std::endl;
        printTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
        printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
    }
}

/*
 * ============================================================================
 *                         EJERCICIO 1: CASO LEFT-LEFT (LL)
 * ============================================================================
 * Secuencia: 30, 20, 10
 * 
 * Explicación:
 * - Insertamos 30 (raíz)
 * - Insertamos 20 (hijo izquierdo de 30)
 * - Insertamos 10 (hijo izquierdo de 20)
 * - El nodo 30 tiene balance = 2 (desequilibrado a la izquierda)
 * - Como 10 < 20 (hijo izquierdo del hijo izquierdo), es caso LL
 * - Se aplica UNA rotación simple a la derecha
 * 
 * Antes:       Después:
 *     30          20
 *    /           /  \
 *   20         10    30
 *  /
 * 10
 */
void ejercicio1_LL() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 1: CASO LEFT-LEFT (LL)" << std::endl;
    std::cout << "Secuencia a insertar: 30, 20, 10" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node *root = NULL;
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 10);
    
    std::cout << "\nÁrbol resultante (preorden): ";
    preOrder(root);
    std::cout << "\n\nEstructura del árbol:" << std::endl;
    printTree(root);
}

/*
 * ============================================================================
 *                       EJERCICIO 2: CASO RIGHT-RIGHT (RR)
 * ============================================================================
 * Secuencia: 10, 20, 30
 * 
 * Explicación:
 * - Insertamos 10 (raíz)
 * - Insertamos 20 (hijo derecho de 10)
 * - Insertamos 30 (hijo derecho de 20)
 * - El nodo 10 tiene balance = -2 (desequilibrado a la derecha)
 * - Como 30 > 20 (hijo derecho del hijo derecho), es caso RR
 * - Se aplica UNA rotación simple a la izquierda
 * 
 * Antes:       Después:
 * 10              20
 *   \            /  \
 *    20        10    30
 *      \
 *       30
 */
void ejercicio2_RR() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 2: CASO RIGHT-RIGHT (RR)" << std::endl;
    std::cout << "Secuencia a insertar: 10, 20, 30" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    
    std::cout << "\nÁrbol resultante (preorden): ";
    preOrder(root);
    std::cout << "\n\nEstructura del árbol:" << std::endl;
    printTree(root);
}

/*
 * ============================================================================
 *                       EJERCICIO 3: CASO LEFT-RIGHT (LR)
 * ============================================================================
 * Secuencia: 30, 10, 20
 * 
 * Explicación:
 * - Insertamos 30 (raíz)
 * - Insertamos 10 (hijo izquierdo de 30)
 * - Insertamos 20 (hijo derecho de 10)
 * - El nodo 30 tiene balance = 2 (desequilibrado a la izquierda)
 * - Como 20 > 10 (hijo derecho del hijo izquierdo), es caso LR
 * - Se aplican DOS rotaciones: primero izquierda en 10, luego derecha en 30
 * 
 * Antes:       Paso 1:      Después:
 *     30          30          20
 *    /           /           /  \
 *   10         20          10    30
 *     \       /
 *      20    10
 */
void ejercicio3_LR() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 3: CASO LEFT-RIGHT (LR)" << std::endl;
    std::cout << "Secuencia a insertar: 30, 10, 20" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node *root = NULL;
    root = insert(root, 30);
    root = insert(root, 10);
    root = insert(root, 20);
    
    std::cout << "\nÁrbol resultante (preorden): ";
    preOrder(root);
    std::cout << "\n\nEstructura del árbol:" << std::endl;
    printTree(root);
}

/*
 * ============================================================================
 *                       EJERCICIO 4: CASO RIGHT-LEFT (RL)
 * ============================================================================
 * Secuencia: 10, 30, 20
 * 
 * Explicación:
 * - Insertamos 10 (raíz)
 * - Insertamos 30 (hijo derecho de 10)
 * - Insertamos 20 (hijo izquierdo de 30)
 * - El nodo 10 tiene balance = -2 (desequilibrado a la derecha)
 * - Como 20 < 30 (hijo izquierdo del hijo derecho), es caso RL
 * - Se aplican DOS rotaciones: primero derecha en 30, luego izquierda en 10
 * 
 * Antes:       Paso 1:      Después:
 * 10            10            20
 *   \             \          /  \
 *    30            20      10    30
 *   /                \
 *  20                 30
 */
void ejercicio4_RL() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 4: CASO RIGHT-LEFT (RL)" << std::endl;
    std::cout << "Secuencia a insertar: 10, 30, 20" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 20);
    
    std::cout << "\nÁrbol resultante (preorden): ";
    preOrder(root);
    std::cout << "\n\nEstructura del árbol:" << std::endl;
    printTree(root);
}

/*
 * ============================================================================
 *                    EJERCICIO 5: MÚLTIPLES ROTACIONES LL
 * ============================================================================
 * Secuencia: 50, 40, 30, 20, 10
 * 
 * Este ejercicio demuestra múltiples rotaciones LL consecutivas
 * a medida que insertamos valores decrecientes.
 */
void ejercicio5_multiples_LL() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 5: MÚLTIPLES ROTACIONES LL" << std::endl;
    std::cout << "Secuencia a insertar: 50, 40, 30, 20, 10" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node *root = NULL;
    int valores[] = {50, 40, 30, 20, 10};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        root = insert(root, v);
        std::cout << "Árbol actual:" << std::endl;
        printTree(root);
    }
}

/*
 * ============================================================================
 *                    EJERCICIO 6: MÚLTIPLES ROTACIONES RR
 * ============================================================================
 * Secuencia: 10, 20, 30, 40, 50
 * 
 * Este ejercicio demuestra múltiples rotaciones RR consecutivas
 * a medida que insertamos valores crecientes.
 */
void ejercicio6_multiples_RR() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 6: MÚLTIPLES ROTACIONES RR" << std::endl;
    std::cout << "Secuencia a insertar: 10, 20, 30, 40, 50" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node *root = NULL;
    int valores[] = {10, 20, 30, 40, 50};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        root = insert(root, v);
        std::cout << "Árbol actual:" << std::endl;
        printTree(root);
    }
}

/*
 * ============================================================================
 *                    EJERCICIO 7: COMBINACIÓN DE ROTACIONES
 * ============================================================================
 * Secuencia: 50, 30, 70, 20, 40, 60, 80, 35
 * 
 * Este ejercicio muestra una combinación de casos donde
 * se activan diferentes tipos de rotaciones.
 */
void ejercicio7_combinacion() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 7: COMBINACIÓN DE ROTACIONES" << std::endl;
    std::cout << "Secuencia a insertar: 50, 30, 70, 20, 40, 60, 80, 35" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node *root = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 35};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        root = insert(root, v);
        std::cout << "Árbol actual:" << std::endl;
        printTree(root);
    }
}

/*
 * ============================================================================
 *                    EJERCICIO 8: ELIMINACIÓN CON ROTACIÓN LL
 * ============================================================================
 * Secuencia: Insertar 50, 30, 70, 20, 40, 10
 *           Luego eliminar 70
 * 
 * Al eliminar 70, el árbol se desequilibra hacia la izquierda
 * causando una rotación LL.
 */
void ejercicio8_eliminacion_LL() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 8: ELIMINACIÓN CON ROTACIÓN LL" << std::endl;
    std::cout << "Insertar: 50, 30, 70, 20, 40, 10" << std::endl;
    std::cout << "Eliminar: 70" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node *root = NULL;
    int valores[] = {50, 30, 70, 20, 40, 10};
    
    for (int v : valores) {
        root = insert(root, v);
    }
    
    std::cout << "\nÁrbol antes de eliminar:" << std::endl;
    printTree(root);
    
    std::cout << "\n--- Eliminando 70 ---" << std::endl;
    root = deleteNode(root, 70);
    
    std::cout << "\nÁrbol después de eliminar:" << std::endl;
    printTree(root);
}

/*
 * ============================================================================
 *                    EJERCICIO 9: ELIMINACIÓN CON ROTACIÓN RR
 * ============================================================================
 * Secuencia: Insertar 30, 20, 50, 40, 60, 70
 *           Luego eliminar 20
 * 
 * Al eliminar 20, el árbol se desequilibra hacia la derecha
 * causando una rotación RR.
 */
void ejercicio9_eliminacion_RR() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 9: ELIMINACIÓN CON ROTACIÓN RR" << std::endl;
    std::cout << "Insertar: 30, 20, 50, 40, 60, 70" << std::endl;
    std::cout << "Eliminar: 20" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node *root = NULL;
    int valores[] = {30, 20, 50, 40, 60, 70};
    
    for (int v : valores) {
        root = insert(root, v);
    }
    
    std::cout << "\nÁrbol antes de eliminar:" << std::endl;
    printTree(root);
    
    std::cout << "\n--- Eliminando 20 ---" << std::endl;
    root = deleteNode(root, 20);
    
    std::cout << "\nÁrbol después de eliminar:" << std::endl;
    printTree(root);
}

/*
 * ============================================================================
 *                    EJERCICIO 10: ELIMINACIÓN CON ROTACIÓN LR
 * ============================================================================
 * Secuencia: Insertar 50, 30, 60, 20, 40
 *           Luego eliminar 60
 * 
 * Al eliminar 60, necesitamos una rotación LR.
 */
void ejercicio10_eliminacion_LR() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 10: ELIMINACIÓN CON ROTACIÓN LR" << std::endl;
    std::cout << "Insertar: 50, 30, 60, 20, 40" << std::endl;
    std::cout << "Eliminar: 60" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node *root = NULL;
    int valores[] = {50, 30, 60, 20, 40};
    
    for (int v : valores) {
        root = insert(root, v);
    }
    
    std::cout << "\nÁrbol antes de eliminar:" << std::endl;
    printTree(root);
    
    std::cout << "\n--- Eliminando 60 ---" << std::endl;
    root = deleteNode(root, 60);
    
    std::cout << "\nÁrbol después de eliminar:" << std::endl;
    printTree(root);
}

/*
 * ============================================================================
 *                    EJERCICIO 11: ELIMINACIÓN DE NODO CON DOS HIJOS
 * ============================================================================
 * Este ejercicio demuestra la eliminación de un nodo con dos hijos,
 * donde se debe encontrar el sucesor inorden.
 */
void ejercicio11_eliminacion_dos_hijos() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 11: ELIMINACIÓN DE NODO CON DOS HIJOS" << std::endl;
    std::cout << "Insertar: 50, 30, 70, 20, 40, 60, 80" << std::endl;
    std::cout << "Eliminar: 50 (raíz con dos hijos)" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node *root = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    
    for (int v : valores) {
        root = insert(root, v);
    }
    
    std::cout << "\nÁrbol antes de eliminar:" << std::endl;
    printTree(root);
    
    std::cout << "\n--- Eliminando 50 ---" << std::endl;
    root = deleteNode(root, 50);
    
    std::cout << "\nÁrbol después de eliminar:" << std::endl;
    printTree(root);
}

/*
 * ============================================================================
 *                    EJERCICIO 12: SECUENCIA ZIGZAG
 * ============================================================================
 * Secuencia: 50, 30, 40, 60, 55
 * 
 * Esta secuencia crea patrones zigzag que activan rotaciones dobles.
 */
void ejercicio12_zigzag() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 12: SECUENCIA ZIGZAG" << std::endl;
    std::cout << "Secuencia a insertar: 50, 30, 40, 60, 55" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node *root = NULL;
    int valores[] = {50, 30, 40, 60, 55};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        root = insert(root, v);
        std::cout << "Árbol actual:" << std::endl;
        printTree(root);
    }
}

int main() {
    std::cout << "\n" << std::string(70, '*') << std::endl;
    std::cout << "        EJERCICIOS DE CASOS EDGE EN ÁRBOLES AVL" << std::endl;
    std::cout << std::string(70, '*') << std::endl;
    
    std::cout << "\n[MENÚ DE EJERCICIOS]" << std::endl;
    std::cout << "1.  Caso LL (Left-Left) - Rotación simple derecha" << std::endl;
    std::cout << "2.  Caso RR (Right-Right) - Rotación simple izquierda" << std::endl;
    std::cout << "3.  Caso LR (Left-Right) - Rotación doble" << std::endl;
    std::cout << "4.  Caso RL (Right-Left) - Rotación doble" << std::endl;
    std::cout << "5.  Múltiples rotaciones LL consecutivas" << std::endl;
    std::cout << "6.  Múltiples rotaciones RR consecutivas" << std::endl;
    std::cout << "7.  Combinación de rotaciones" << std::endl;
    std::cout << "8.  Eliminación con rotación LL" << std::endl;
    std::cout << "9.  Eliminación con rotación RR" << std::endl;
    std::cout << "10. Eliminación con rotación LR" << std::endl;
    std::cout << "11. Eliminación de nodo con dos hijos" << std::endl;
    std::cout << "12. Secuencia zigzag (rotaciones dobles)" << std::endl;
    std::cout << "0.  Ejecutar todos los ejercicios" << std::endl;
    
    int opcion;
    std::cout << "\nSelecciona un ejercicio (0-12): ";
    std::cin >> opcion;
    
    switch(opcion) {
        case 0:
            ejercicio1_LL();
            ejercicio2_RR();
            ejercicio3_LR();
            ejercicio4_RL();
            ejercicio5_multiples_LL();
            ejercicio6_multiples_RR();
            ejercicio7_combinacion();
            ejercicio8_eliminacion_LL();
            ejercicio9_eliminacion_RR();
            ejercicio10_eliminacion_LR();
            ejercicio11_eliminacion_dos_hijos();
            ejercicio12_zigzag();
            break;
        case 1: ejercicio1_LL(); break;
        case 2: ejercicio2_RR(); break;
        case 3: ejercicio3_LR(); break;
        case 4: ejercicio4_RL(); break;
        case 5: ejercicio5_multiples_LL(); break;
        case 6: ejercicio6_multiples_RR(); break;
        case 7: ejercicio7_combinacion(); break;
        case 8: ejercicio8_eliminacion_LL(); break;
        case 9: ejercicio9_eliminacion_RR(); break;
        case 10: ejercicio10_eliminacion_LR(); break;
        case 11: ejercicio11_eliminacion_dos_hijos(); break;
        case 12: ejercicio12_zigzag(); break;
        default:
            std::cout << "Opción no válida." << std::endl;
    }
    
    return 0;
}
