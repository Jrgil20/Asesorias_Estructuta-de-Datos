/*
 * EJERCICIOS DE CASOS EDGE EN ÁRBOLES BST
 * =========================================
 * 
 * Este archivo contiene ejercicios diseñados para explotar cada uno de los casos
 * edge en árboles binarios de búsqueda (BST), específicamente casos de eliminación.
 * 
 * CASOS DE ELIMINACIÓN EN BST:
 * 1. Eliminar nodo hoja (sin hijos)
 * 2. Eliminar nodo con un solo hijo (izquierdo)
 * 3. Eliminar nodo con un solo hijo (derecho)
 * 4. Eliminar nodo con dos hijos (sucesor inorden)
 * 5. Eliminar la raíz
 * 
 * CASOS EDGE ADICIONALES:
 * - Inserción en árbol vacío
 * - Árbol degenerado (lista enlazada)
 * - Inserción de elementos duplicados
 */

#include <iostream>

struct Node {
    int key;
    Node *left, *right;
};

Node* newNode(int item) {
    Node* temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        std::cout << root->key << " ";
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root != NULL) {
        std::cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void printTree(Node *root, const std::string& prefix = "", bool isLeft = true) {
    if (root != NULL) {
        std::cout << prefix;
        std::cout << (isLeft ? "├── " : "└── ");
        std::cout << root->key << std::endl;
        printTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
        printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
    }
}

int altura(Node* node) {
    if (node == NULL) return 0;
    int altIzq = altura(node->left);
    int altDer = altura(node->right);
    return 1 + std::max(altIzq, altDer);
}

Node* insert(Node* node, int key) {
    if (node == NULL) {
        std::cout << "  Insertando: " << key << std::endl;
        return newNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        std::cout << "  [CASO: Elemento duplicado " << key << " - No se inserta]" << std::endl;
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) {
        std::cout << "  [CASO: Elemento no encontrado]" << std::endl;
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        std::cout << "  Eliminando: " << key << std::endl;
        
        // Caso 1: Nodo hoja (sin hijos)
        if (root->left == NULL && root->right == NULL) {
            std::cout << "  [CASO: Nodo hoja - sin hijos]" << std::endl;
            delete root;
            return NULL;
        }
        
        // Caso 2: Nodo con solo hijo derecho
        if (root->left == NULL) {
            std::cout << "  [CASO: Nodo con un hijo derecho]" << std::endl;
            Node* temp = root->right;
            delete root;
            return temp;
        }
        
        // Caso 3: Nodo con solo hijo izquierdo
        if (root->right == NULL) {
            std::cout << "  [CASO: Nodo con un hijo izquierdo]" << std::endl;
            Node* temp = root->left;
            delete root;
            return temp;
        }
        
        // Caso 4: Nodo con dos hijos
        std::cout << "  [CASO: Nodo con dos hijos]" << std::endl;
        Node* temp = minValueNode(root->right);
        std::cout << "  Sucesor inorden encontrado: " << temp->key << std::endl;
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    
    return root;
}

/*
 * ============================================================================
 *                         EJERCICIO 1: INSERCIÓN BÁSICA
 * ============================================================================
 * Secuencia: 50, 30, 70, 20, 40, 60, 80
 * 
 * Crea un árbol BST balanceado manualmente.
 */
void ejercicio1_insercion_basica() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 1: INSERCIÓN BÁSICA EN BST" << std::endl;
    std::cout << "Secuencia a insertar: 50, 30, 70, 20, 40, 60, 80" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node* root = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    
    for (int v : valores) {
        root = insert(root, v);
    }
    
    std::cout << "\nÁrbol resultante:" << std::endl;
    printTree(root);
    std::cout << "\nRecorrido inorden: ";
    inorder(root);
    std::cout << "\nAltura del árbol: " << altura(root) << std::endl;
}

/*
 * ============================================================================
 *                    EJERCICIO 2: ÁRBOL DEGENERADO (LISTA)
 * ============================================================================
 * Secuencia: 10, 20, 30, 40, 50
 * 
 * Insertar valores en orden creciente crea un árbol degenerado
 * que se comporta como una lista enlazada.
 */
void ejercicio2_arbol_degenerado() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 2: ÁRBOL DEGENERADO (LISTA)" << std::endl;
    std::cout << "Secuencia a insertar: 10, 20, 30, 40, 50" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node* root = NULL;
    int valores[] = {10, 20, 30, 40, 50};
    
    for (int v : valores) {
        root = insert(root, v);
    }
    
    std::cout << "\nÁrbol resultante (degenerado hacia la derecha):" << std::endl;
    printTree(root);
    std::cout << "\nAltura del árbol: " << altura(root) << " (peor caso: n elementos)" << std::endl;
}

/*
 * ============================================================================
 *                 EJERCICIO 3: ÁRBOL DEGENERADO (INVERSO)
 * ============================================================================
 * Secuencia: 50, 40, 30, 20, 10
 * 
 * Insertar valores en orden decreciente crea un árbol degenerado
 * hacia la izquierda.
 */
void ejercicio3_arbol_degenerado_inverso() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 3: ÁRBOL DEGENERADO (INVERSO)" << std::endl;
    std::cout << "Secuencia a insertar: 50, 40, 30, 20, 10" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node* root = NULL;
    int valores[] = {50, 40, 30, 20, 10};
    
    for (int v : valores) {
        root = insert(root, v);
    }
    
    std::cout << "\nÁrbol resultante (degenerado hacia la izquierda):" << std::endl;
    printTree(root);
    std::cout << "\nAltura del árbol: " << altura(root) << " (peor caso: n elementos)" << std::endl;
}

/*
 * ============================================================================
 *                    EJERCICIO 4: ELIMINAR NODO HOJA
 * ============================================================================
 * Insertar: 50, 30, 70, 20
 * Eliminar: 20 (nodo hoja)
 */
void ejercicio4_eliminar_hoja() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 4: ELIMINAR NODO HOJA" << std::endl;
    std::cout << "Insertar: 50, 30, 70, 20" << std::endl;
    std::cout << "Eliminar: 20" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node* root = NULL;
    int valores[] = {50, 30, 70, 20};
    
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
 *                 EJERCICIO 5: ELIMINAR NODO CON UN HIJO IZQUIERDO
 * ============================================================================
 * Insertar: 50, 30, 70, 20
 * Eliminar: 30 (tiene solo hijo izquierdo)
 */
void ejercicio5_eliminar_un_hijo_izq() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 5: ELIMINAR NODO CON UN HIJO IZQUIERDO" << std::endl;
    std::cout << "Insertar: 50, 30, 70, 20" << std::endl;
    std::cout << "Eliminar: 30" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node* root = NULL;
    int valores[] = {50, 30, 70, 20};
    
    for (int v : valores) {
        root = insert(root, v);
    }
    
    std::cout << "\nÁrbol antes de eliminar:" << std::endl;
    printTree(root);
    
    std::cout << "\n--- Eliminando 30 ---" << std::endl;
    root = deleteNode(root, 30);
    
    std::cout << "\nÁrbol después de eliminar:" << std::endl;
    printTree(root);
}

/*
 * ============================================================================
 *                EJERCICIO 6: ELIMINAR NODO CON UN HIJO DERECHO
 * ============================================================================
 * Insertar: 50, 30, 70, 80
 * Eliminar: 70 (tiene solo hijo derecho)
 */
void ejercicio6_eliminar_un_hijo_der() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 6: ELIMINAR NODO CON UN HIJO DERECHO" << std::endl;
    std::cout << "Insertar: 50, 30, 70, 80" << std::endl;
    std::cout << "Eliminar: 70" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node* root = NULL;
    int valores[] = {50, 30, 70, 80};
    
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
 *                  EJERCICIO 7: ELIMINAR NODO CON DOS HIJOS
 * ============================================================================
 * Insertar: 50, 30, 70, 20, 40, 60, 80
 * Eliminar: 30 (tiene dos hijos)
 */
void ejercicio7_eliminar_dos_hijos() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 7: ELIMINAR NODO CON DOS HIJOS" << std::endl;
    std::cout << "Insertar: 50, 30, 70, 20, 40, 60, 80" << std::endl;
    std::cout << "Eliminar: 30" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node* root = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    
    for (int v : valores) {
        root = insert(root, v);
    }
    
    std::cout << "\nÁrbol antes de eliminar:" << std::endl;
    printTree(root);
    
    std::cout << "\n--- Eliminando 30 ---" << std::endl;
    root = deleteNode(root, 30);
    
    std::cout << "\nÁrbol después de eliminar (40 reemplaza a 30):" << std::endl;
    printTree(root);
}

/*
 * ============================================================================
 *                       EJERCICIO 8: ELIMINAR LA RAÍZ
 * ============================================================================
 * Insertar: 50, 30, 70, 20, 40, 60, 80
 * Eliminar: 50 (la raíz con dos hijos)
 */
void ejercicio8_eliminar_raiz() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 8: ELIMINAR LA RAÍZ" << std::endl;
    std::cout << "Insertar: 50, 30, 70, 20, 40, 60, 80" << std::endl;
    std::cout << "Eliminar: 50 (raíz)" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node* root = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    
    for (int v : valores) {
        root = insert(root, v);
    }
    
    std::cout << "\nÁrbol antes de eliminar:" << std::endl;
    printTree(root);
    
    std::cout << "\n--- Eliminando 50 (raíz) ---" << std::endl;
    root = deleteNode(root, 50);
    
    std::cout << "\nÁrbol después de eliminar (60 reemplaza a 50):" << std::endl;
    printTree(root);
}

/*
 * ============================================================================
 *                 EJERCICIO 9: ELIMINAR ELEMENTO NO EXISTENTE
 * ============================================================================
 */
void ejercicio9_eliminar_no_existe() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 9: ELIMINAR ELEMENTO NO EXISTENTE" << std::endl;
    std::cout << "Insertar: 50, 30, 70" << std::endl;
    std::cout << "Eliminar: 100" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node* root = NULL;
    int valores[] = {50, 30, 70};
    
    for (int v : valores) {
        root = insert(root, v);
    }
    
    std::cout << "\nÁrbol antes de eliminar:" << std::endl;
    printTree(root);
    
    std::cout << "\n--- Intentando eliminar 100 ---" << std::endl;
    root = deleteNode(root, 100);
    
    std::cout << "\nÁrbol después (sin cambios):" << std::endl;
    printTree(root);
}

/*
 * ============================================================================
 *                    EJERCICIO 10: INSERTAR DUPLICADOS
 * ============================================================================
 */
void ejercicio10_duplicados() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 10: INSERTAR DUPLICADOS" << std::endl;
    std::cout << "Secuencia a insertar: 50, 30, 70, 30, 50" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node* root = NULL;
    int valores[] = {50, 30, 70, 30, 50};
    
    for (int v : valores) {
        root = insert(root, v);
    }
    
    std::cout << "\nÁrbol resultante (duplicados ignorados):" << std::endl;
    printTree(root);
}

/*
 * ============================================================================
 *                 EJERCICIO 11: ELIMINAR TODOS LOS NODOS
 * ============================================================================
 */
void ejercicio11_eliminar_todos() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 11: ELIMINAR TODOS LOS NODOS" << std::endl;
    std::cout << "Insertar: 50, 30, 70" << std::endl;
    std::cout << "Eliminar: 30, 70, 50" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node* root = NULL;
    int valores[] = {50, 30, 70};
    
    for (int v : valores) {
        root = insert(root, v);
    }
    
    std::cout << "\nÁrbol inicial:" << std::endl;
    printTree(root);
    
    int eliminar[] = {30, 70, 50};
    for (int v : eliminar) {
        std::cout << "\n--- Eliminando " << v << " ---" << std::endl;
        root = deleteNode(root, v);
        if (root) {
            std::cout << "Árbol actual:" << std::endl;
            printTree(root);
        } else {
            std::cout << "Árbol vacío" << std::endl;
        }
    }
}

/*
 * ============================================================================
 *             EJERCICIO 12: ELIMINAR RAÍZ EN ÁRBOL DEGENERADO
 * ============================================================================
 */
void ejercicio12_eliminar_raiz_degenerado() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 12: ELIMINAR RAÍZ EN ÁRBOL DEGENERADO" << std::endl;
    std::cout << "Insertar: 10, 20, 30, 40" << std::endl;
    std::cout << "Eliminar: 10 (raíz)" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    Node* root = NULL;
    int valores[] = {10, 20, 30, 40};
    
    for (int v : valores) {
        root = insert(root, v);
    }
    
    std::cout << "\nÁrbol antes de eliminar:" << std::endl;
    printTree(root);
    
    std::cout << "\n--- Eliminando 10 (raíz) ---" << std::endl;
    root = deleteNode(root, 10);
    
    std::cout << "\nÁrbol después de eliminar:" << std::endl;
    printTree(root);
}

int main() {
    std::cout << "\n" << std::string(70, '*') << std::endl;
    std::cout << "        EJERCICIOS DE CASOS EDGE EN ÁRBOLES BST" << std::endl;
    std::cout << std::string(70, '*') << std::endl;
    
    std::cout << "\n[MENÚ DE EJERCICIOS]" << std::endl;
    std::cout << "1.  Inserción básica" << std::endl;
    std::cout << "2.  Árbol degenerado (orden creciente)" << std::endl;
    std::cout << "3.  Árbol degenerado inverso (orden decreciente)" << std::endl;
    std::cout << "4.  Eliminar nodo hoja" << std::endl;
    std::cout << "5.  Eliminar nodo con un hijo izquierdo" << std::endl;
    std::cout << "6.  Eliminar nodo con un hijo derecho" << std::endl;
    std::cout << "7.  Eliminar nodo con dos hijos" << std::endl;
    std::cout << "8.  Eliminar la raíz" << std::endl;
    std::cout << "9.  Eliminar elemento no existente" << std::endl;
    std::cout << "10. Insertar duplicados" << std::endl;
    std::cout << "11. Eliminar todos los nodos" << std::endl;
    std::cout << "12. Eliminar raíz en árbol degenerado" << std::endl;
    std::cout << "0.  Ejecutar todos los ejercicios" << std::endl;
    
    int opcion;
    std::cout << "\nSelecciona un ejercicio (0-12): ";
    std::cin >> opcion;
    
    switch(opcion) {
        case 0:
            ejercicio1_insercion_basica();
            ejercicio2_arbol_degenerado();
            ejercicio3_arbol_degenerado_inverso();
            ejercicio4_eliminar_hoja();
            ejercicio5_eliminar_un_hijo_izq();
            ejercicio6_eliminar_un_hijo_der();
            ejercicio7_eliminar_dos_hijos();
            ejercicio8_eliminar_raiz();
            ejercicio9_eliminar_no_existe();
            ejercicio10_duplicados();
            ejercicio11_eliminar_todos();
            ejercicio12_eliminar_raiz_degenerado();
            break;
        case 1: ejercicio1_insercion_basica(); break;
        case 2: ejercicio2_arbol_degenerado(); break;
        case 3: ejercicio3_arbol_degenerado_inverso(); break;
        case 4: ejercicio4_eliminar_hoja(); break;
        case 5: ejercicio5_eliminar_un_hijo_izq(); break;
        case 6: ejercicio6_eliminar_un_hijo_der(); break;
        case 7: ejercicio7_eliminar_dos_hijos(); break;
        case 8: ejercicio8_eliminar_raiz(); break;
        case 9: ejercicio9_eliminar_no_existe(); break;
        case 10: ejercicio10_duplicados(); break;
        case 11: ejercicio11_eliminar_todos(); break;
        case 12: ejercicio12_eliminar_raiz_degenerado(); break;
        default:
            std::cout << "Opción no válida." << std::endl;
    }
    
    return 0;
}
