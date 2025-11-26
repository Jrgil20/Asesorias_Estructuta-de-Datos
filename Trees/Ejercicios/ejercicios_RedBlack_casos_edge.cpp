/*
 * EJERCICIOS DE CASOS EDGE EN ÁRBOLES ROJO-NEGRO
 * ================================================
 * 
 * Este archivo contiene ejercicios diseñados para explotar cada uno de los casos
 * edge en árboles Rojo-Negro, específicamente durante inserción y eliminación.
 * 
 * PROPIEDADES DEL ÁRBOL ROJO-NEGRO:
 * 1. Cada nodo es rojo o negro
 * 2. La raíz siempre es negra
 * 3. No hay dos nodos rojos consecutivos (padre-hijo)
 * 4. Todo camino de un nodo a sus hojas NULL tiene el mismo número de nodos negros
 * 
 * CASOS DE INSERCIÓN:
 * - Caso 1: Tío es rojo (recolorear)
 * - Caso 2: Tío es negro y el nodo es hijo derecho (rotación izquierda)
 * - Caso 3: Tío es negro y el nodo es hijo izquierdo (rotación derecha)
 * 
 * Los casos son simétricos para el lado opuesto del árbol.
 */

#include <iostream>
#include <string>

enum Color { ROJO, NEGRO };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;
    
    Node(int data) : data(data), color(ROJO), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
private:
    Node *root;
    Node *TNULL;
    
    void initializeNULLNode(Node* node, Node* parent) {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = NEGRO;
    }
    
    void rotateLeft(Node* x) {
        std::cout << "  >> ROTACIÓN IZQUIERDA en nodo " << x->data << std::endl;
        Node* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    
    void rotateRight(Node* x) {
        std::cout << "  >> ROTACIÓN DERECHA en nodo " << x->data << std::endl;
        Node* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }
    
    void fixInsert(Node* k) {
        Node* u;
        while (k->parent != nullptr && k->parent->color == ROJO) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;  // tío
                
                // Caso 1: Tío es rojo
                if (u->color == ROJO) {
                    std::cout << "  [CASO 1: Tío rojo - Recolorear]" << std::endl;
                    u->color = NEGRO;
                    k->parent->color = NEGRO;
                    k->parent->parent->color = ROJO;
                    k = k->parent->parent;
                } else {
                    // Caso 2: Tío negro, nodo es hijo izquierdo
                    if (k == k->parent->left) {
                        std::cout << "  [CASO 2: Tío negro, nodo hijo izquierdo]" << std::endl;
                        k = k->parent;
                        rotateRight(k);
                    }
                    // Caso 3: Tío negro, nodo es hijo derecho
                    std::cout << "  [CASO 3: Tío negro, nodo hijo derecho]" << std::endl;
                    k->parent->color = NEGRO;
                    k->parent->parent->color = ROJO;
                    rotateLeft(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;  // tío
                
                // Caso 1: Tío es rojo
                if (u->color == ROJO) {
                    std::cout << "  [CASO 1 (simétrico): Tío rojo - Recolorear]" << std::endl;
                    u->color = NEGRO;
                    k->parent->color = NEGRO;
                    k->parent->parent->color = ROJO;
                    k = k->parent->parent;
                } else {
                    // Caso 2: Tío negro, nodo es hijo derecho
                    if (k == k->parent->right) {
                        std::cout << "  [CASO 2 (simétrico): Tío negro, nodo hijo derecho]" << std::endl;
                        k = k->parent;
                        rotateLeft(k);
                    }
                    // Caso 3: Tío negro, nodo es hijo izquierdo
                    std::cout << "  [CASO 3 (simétrico): Tío negro, nodo hijo izquierdo]" << std::endl;
                    k->parent->color = NEGRO;
                    k->parent->parent->color = ROJO;
                    rotateRight(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = NEGRO;
    }
    
    void printTreeHelper(Node* root, const std::string& indent, bool last) {
        if (root != TNULL) {
            std::cout << indent;
            std::string newIndent = indent;
            if (last) {
                std::cout << "└── ";
                newIndent += "    ";
            } else {
                std::cout << "├── ";
                newIndent += "│   ";
            }
            std::string sColor = (root->color == ROJO) ? "R" : "N";
            std::cout << root->data << "(" << sColor << ")" << std::endl;
            printTreeHelper(root->left, newIndent, false);
            printTreeHelper(root->right, newIndent, true);
        }
    }
    
    void preOrderHelper(Node* node) {
        if (node != TNULL) {
            std::string sColor = (node->color == ROJO) ? "R" : "N";
            std::cout << node->data << "(" << sColor << ") ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }
    
    int blackHeight(Node* node) {
        if (node == TNULL) return 1;
        int leftBH = blackHeight(node->left);
        int rightBH = blackHeight(node->right);
        int add = (node->color == NEGRO) ? 1 : 0;
        return leftBH + add;
    }
    
public:
    RBTree() {
        TNULL = new Node(0);
        TNULL->color = NEGRO;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }
    
    void insert(int key) {
        std::cout << "  Insertando: " << key << " (color inicial: ROJO)" << std::endl;
        
        Node* node = new Node(key);
        node->left = TNULL;
        node->right = TNULL;
        
        Node* y = nullptr;
        Node* x = root;
        
        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        
        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }
        
        if (node->parent == nullptr) {
            std::cout << "  [CASO: Nodo es raíz - Se colorea NEGRO]" << std::endl;
            node->color = NEGRO;
            return;
        }
        
        if (node->parent->parent == nullptr) {
            std::cout << "  [CASO: Padre es raíz - No requiere ajuste]" << std::endl;
            return;
        }
        
        fixInsert(node);
    }
    
    void printTree() {
        if (root != TNULL) {
            printTreeHelper(root, "", true);
        }
    }
    
    void preOrder() {
        preOrderHelper(root);
        std::cout << std::endl;
    }
    
    int getBlackHeight() {
        return blackHeight(root);
    }
};

/*
 * ============================================================================
 *                    EJERCICIO 1: INSERCIÓN EN ÁRBOL VACÍO
 * ============================================================================
 * Secuencia: 50
 * 
 * Cuando se inserta en un árbol vacío, el nodo se convierte en raíz
 * y se colorea de NEGRO.
 */
void ejercicio1_insercion_vacia() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 1: INSERCIÓN EN ÁRBOL VACÍO" << std::endl;
    std::cout << "Secuencia a insertar: 50" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    RBTree tree;
    tree.insert(50);
    
    std::cout << "\nÁrbol resultante:" << std::endl;
    tree.printTree();
    std::cout << "\nAltura negra: " << tree.getBlackHeight() << std::endl;
}

/*
 * ============================================================================
 *                EJERCICIO 2: CASO 1 - TÍO ROJO (RECOLOREAR)
 * ============================================================================
 * Secuencia: 50, 30, 70, 20
 * 
 * Cuando el tío del nuevo nodo es rojo, se recolorean el padre,
 * tío y abuelo, y se continúa verificando hacia arriba.
 */
void ejercicio2_caso1_tio_rojo() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 2: CASO 1 - TÍO ROJO (RECOLOREAR)" << std::endl;
    std::cout << "Secuencia a insertar: 50, 30, 70, 20" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    RBTree tree;
    int valores[] = {50, 30, 70, 20};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.printTree();
    }
}

/*
 * ============================================================================
 *            EJERCICIO 3: CASO 2 Y 3 - TÍO NEGRO CON ROTACIONES
 * ============================================================================
 * Secuencia: 50, 30, 20
 * 
 * Este caso activa las rotaciones cuando el tío es negro.
 */
void ejercicio3_caso2_3_rotaciones() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 3: CASO 2 Y 3 - TÍO NEGRO CON ROTACIONES" << std::endl;
    std::cout << "Secuencia a insertar: 50, 30, 20" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    RBTree tree;
    int valores[] = {50, 30, 20};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.printTree();
    }
}

/*
 * ============================================================================
 *            EJERCICIO 4: CASO SIMÉTRICO - LADO DERECHO
 * ============================================================================
 * Secuencia: 50, 70, 80
 * 
 * Los mismos casos pero en el lado derecho del árbol.
 */
void ejercicio4_caso_simetrico() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 4: CASO SIMÉTRICO - LADO DERECHO" << std::endl;
    std::cout << "Secuencia a insertar: 50, 70, 80" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    RBTree tree;
    int valores[] = {50, 70, 80};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.printTree();
    }
}

/*
 * ============================================================================
 *                    EJERCICIO 5: ROTACIÓN DOBLE LR
 * ============================================================================
 * Secuencia: 50, 30, 40
 * 
 * Este caso requiere una rotación izquierda seguida de una rotación derecha.
 */
void ejercicio5_rotacion_LR() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 5: ROTACIÓN DOBLE LR" << std::endl;
    std::cout << "Secuencia a insertar: 50, 30, 40" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    RBTree tree;
    int valores[] = {50, 30, 40};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.printTree();
    }
}

/*
 * ============================================================================
 *                    EJERCICIO 6: ROTACIÓN DOBLE RL
 * ============================================================================
 * Secuencia: 50, 70, 60
 * 
 * Este caso requiere una rotación derecha seguida de una rotación izquierda.
 */
void ejercicio6_rotacion_RL() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 6: ROTACIÓN DOBLE RL" << std::endl;
    std::cout << "Secuencia a insertar: 50, 70, 60" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    RBTree tree;
    int valores[] = {50, 70, 60};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.printTree();
    }
}

/*
 * ============================================================================
 *            EJERCICIO 7: MÚLTIPLES RECOLOREOS PROPAGADOS
 * ============================================================================
 * Secuencia: 50, 30, 70, 20, 40, 60, 80, 10
 * 
 * Este ejercicio muestra cómo el recoloreo puede propagarse hacia arriba
 * en el árbol.
 */
void ejercicio7_recoloreo_propagado() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 7: MÚLTIPLES RECOLOREOS PROPAGADOS" << std::endl;
    std::cout << "Secuencia a insertar: 50, 30, 70, 20, 40, 60, 80, 10" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    RBTree tree;
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.printTree();
    }
}

/*
 * ============================================================================
 *                EJERCICIO 8: SECUENCIA ASCENDENTE
 * ============================================================================
 * Secuencia: 10, 20, 30, 40, 50
 * 
 * Insertar en orden ascendente fuerza múltiples rotaciones izquierdas.
 */
void ejercicio8_secuencia_ascendente() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 8: SECUENCIA ASCENDENTE" << std::endl;
    std::cout << "Secuencia a insertar: 10, 20, 30, 40, 50" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    RBTree tree;
    int valores[] = {10, 20, 30, 40, 50};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.printTree();
    }
}

/*
 * ============================================================================
 *                EJERCICIO 9: SECUENCIA DESCENDENTE
 * ============================================================================
 * Secuencia: 50, 40, 30, 20, 10
 * 
 * Insertar en orden descendente fuerza múltiples rotaciones derechas.
 */
void ejercicio9_secuencia_descendente() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 9: SECUENCIA DESCENDENTE" << std::endl;
    std::cout << "Secuencia a insertar: 50, 40, 30, 20, 10" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    RBTree tree;
    int valores[] = {50, 40, 30, 20, 10};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.printTree();
    }
}

/*
 * ============================================================================
 *                EJERCICIO 10: SECUENCIA ZIGZAG
 * ============================================================================
 * Secuencia: 50, 30, 70, 20, 40, 35
 * 
 * Una secuencia que crea patrones zigzag requiriendo rotaciones dobles.
 */
void ejercicio10_zigzag() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 10: SECUENCIA ZIGZAG" << std::endl;
    std::cout << "Secuencia a insertar: 50, 30, 70, 20, 40, 35" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    RBTree tree;
    int valores[] = {50, 30, 70, 20, 40, 35};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.printTree();
    }
}

/*
 * ============================================================================
 *            EJERCICIO 11: ÁRBOL COMPLETO CON 15 NODOS
 * ============================================================================
 * Secuencia específica para crear un árbol Rojo-Negro completo.
 */
void ejercicio11_arbol_completo() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 11: ÁRBOL COMPLETO CON 15 NODOS" << std::endl;
    std::cout << "Secuencia a insertar: 50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56, 68, 81, 93" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    RBTree tree;
    int valores[] = {50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56, 68, 81, 93};
    
    for (int v : valores) {
        tree.insert(v);
    }
    
    std::cout << "\nÁrbol resultante:" << std::endl;
    tree.printTree();
    std::cout << "\nAltura negra: " << tree.getBlackHeight() << std::endl;
    std::cout << "Recorrido preorden: ";
    tree.preOrder();
}

/*
 * ============================================================================
 *                EJERCICIO 12: CASO EXTREMO DE PROPAGACIÓN
 * ============================================================================
 * Este ejercicio muestra el peor caso de propagación de recoloreo
 * desde una hoja hasta la raíz.
 */
void ejercicio12_propagacion_extrema() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 12: CASO EXTREMO DE PROPAGACIÓN" << std::endl;
    std::cout << "Secuencia a insertar: 40, 20, 60, 10, 30, 50, 70, 5" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    RBTree tree;
    int valores[] = {40, 20, 60, 10, 30, 50, 70, 5};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.printTree();
    }
}

int main() {
    std::cout << "\n" << std::string(70, '*') << std::endl;
    std::cout << "     EJERCICIOS DE CASOS EDGE EN ÁRBOLES ROJO-NEGRO" << std::endl;
    std::cout << std::string(70, '*') << std::endl;
    
    std::cout << "\n[MENÚ DE EJERCICIOS]" << std::endl;
    std::cout << "1.  Inserción en árbol vacío" << std::endl;
    std::cout << "2.  Caso 1: Tío rojo (recolorear)" << std::endl;
    std::cout << "3.  Caso 2 y 3: Tío negro con rotaciones" << std::endl;
    std::cout << "4.  Caso simétrico (lado derecho)" << std::endl;
    std::cout << "5.  Rotación doble LR" << std::endl;
    std::cout << "6.  Rotación doble RL" << std::endl;
    std::cout << "7.  Múltiples recoloreos propagados" << std::endl;
    std::cout << "8.  Secuencia ascendente" << std::endl;
    std::cout << "9.  Secuencia descendente" << std::endl;
    std::cout << "10. Secuencia zigzag" << std::endl;
    std::cout << "11. Árbol completo con 15 nodos" << std::endl;
    std::cout << "12. Caso extremo de propagación" << std::endl;
    std::cout << "0.  Ejecutar todos los ejercicios" << std::endl;
    
    int opcion;
    std::cout << "\nSelecciona un ejercicio (0-12): ";
    std::cin >> opcion;
    
    switch(opcion) {
        case 0:
            ejercicio1_insercion_vacia();
            ejercicio2_caso1_tio_rojo();
            ejercicio3_caso2_3_rotaciones();
            ejercicio4_caso_simetrico();
            ejercicio5_rotacion_LR();
            ejercicio6_rotacion_RL();
            ejercicio7_recoloreo_propagado();
            ejercicio8_secuencia_ascendente();
            ejercicio9_secuencia_descendente();
            ejercicio10_zigzag();
            ejercicio11_arbol_completo();
            ejercicio12_propagacion_extrema();
            break;
        case 1: ejercicio1_insercion_vacia(); break;
        case 2: ejercicio2_caso1_tio_rojo(); break;
        case 3: ejercicio3_caso2_3_rotaciones(); break;
        case 4: ejercicio4_caso_simetrico(); break;
        case 5: ejercicio5_rotacion_LR(); break;
        case 6: ejercicio6_rotacion_RL(); break;
        case 7: ejercicio7_recoloreo_propagado(); break;
        case 8: ejercicio8_secuencia_ascendente(); break;
        case 9: ejercicio9_secuencia_descendente(); break;
        case 10: ejercicio10_zigzag(); break;
        case 11: ejercicio11_arbol_completo(); break;
        case 12: ejercicio12_propagacion_extrema(); break;
        default:
            std::cout << "Opción no válida." << std::endl;
    }
    
    return 0;
}
