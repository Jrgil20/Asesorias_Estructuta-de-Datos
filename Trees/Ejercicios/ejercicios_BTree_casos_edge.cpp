/*
 * EJERCICIOS DE CASOS EDGE EN ÁRBOLES B
 * ======================================
 * 
 * Este archivo contiene ejercicios diseñados para explotar cada uno de los casos
 * edge en árboles B (B-Trees), específicamente durante inserción y eliminación.
 * 
 * PROPIEDADES DEL ÁRBOL B DE ORDEN m:
 * 1. Cada nodo tiene como máximo m hijos
 * 2. Cada nodo interno (excepto raíz) tiene al menos ⌈m/2⌉ hijos
 * 3. La raíz tiene al menos 2 hijos si no es hoja
 * 4. Un nodo no hoja con k hijos contiene k-1 claves
 * 5. Todas las hojas aparecen en el mismo nivel
 * 
 * CASOS EDGE DE INSERCIÓN:
 * - Inserción en nodo con espacio
 * - División de nodo (split) cuando está lleno
 * - División que propaga hacia arriba
 * - Crecimiento de la raíz
 * 
 * CASOS EDGE DE ELIMINACIÓN:
 * - Eliminación de hoja con suficientes claves
 * - Préstamo de hermano izquierdo/derecho
 * - Fusión (merge) de nodos
 * - Reducción de altura del árbol
 * 
 * Este ejemplo usa un B-Tree de orden 3 (2-3 Tree) para simplicidad.
 */

#include <iostream>
#include <vector>

class BTreeNode {
public:
    std::vector<int> keys;
    std::vector<BTreeNode*> children;
    bool leaf;
    int t;  // grado mínimo
    
    BTreeNode(int t, bool leaf) {
        this->t = t;
        this->leaf = leaf;
    }
    
    void traverse(int level = 0) {
        std::string indent(level * 4, ' ');
        std::cout << indent << "[";
        for (size_t i = 0; i < keys.size(); i++) {
            std::cout << keys[i];
            if (i < keys.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
        
        for (auto child : children) {
            if (child != nullptr) {
                child->traverse(level + 1);
            }
        }
    }
    
    BTreeNode* search(int k);
    
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode* y);
    
    int findKey(int k);
    void remove(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPred(int idx);
    int getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
};

class BTree {
public:
    BTreeNode* root;
    int t;  // grado mínimo
    
    BTree(int t) {
        root = nullptr;
        this->t = t;
    }
    
    void traverse() {
        if (root != nullptr) {
            root->traverse();
        } else {
            std::cout << "[Árbol vacío]" << std::endl;
        }
    }
    
    BTreeNode* search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }
    
    void insert(int k);
    void remove(int k);
};

// Implementación de BTreeNode

BTreeNode* BTreeNode::search(int k) {
    size_t i = 0;
    while (i < keys.size() && k > keys[i])
        i++;
    
    if (i < keys.size() && keys[i] == k)
        return this;
    
    if (leaf)
        return nullptr;
    
    return children[i]->search(k);
}

void BTree::insert(int k) {
    std::cout << "  Insertando: " << k << std::endl;
    
    if (root == nullptr) {
        std::cout << "  [CASO: Árbol vacío - Crear raíz]" << std::endl;
        root = new BTreeNode(t, true);
        root->keys.push_back(k);
    } else {
        if ((int)root->keys.size() == 2 * t - 1) {
            std::cout << "  [CASO: Raíz llena - Dividir y crear nueva raíz]" << std::endl;
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->children[i]->insertNonFull(k);
            
            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

void BTreeNode::insertNonFull(int k) {
    int i = keys.size() - 1;
    
    if (leaf) {
        std::cout << "  [Insertando en hoja]" << std::endl;
        keys.push_back(0);
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;
        i++;
        
        if ((int)children[i]->keys.size() == 2 * t - 1) {
            std::cout << "  [CASO: Nodo hijo lleno - Dividir antes de insertar]" << std::endl;
            splitChild(i, children[i]);
            if (keys[i] < k)
                i++;
        }
        children[i]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    std::cout << "  >> DIVISIÓN (SPLIT) de nodo" << std::endl;
    
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    
    // Mover la mitad superior de las claves al nuevo nodo
    for (int j = 0; j < t - 1; j++) {
        z->keys.push_back(y->keys[j + t]);
    }
    
    // Si no es hoja, mover los hijos correspondientes
    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->children.push_back(y->children[j + t]);
        }
        y->children.resize(t);
    }
    
    // Guardar la clave mediana para subir al padre
    int mediana = y->keys[t - 1];
    y->keys.resize(t - 1);
    
    // Insertar el nuevo hijo en este nodo
    children.insert(children.begin() + i + 1, z);
    
    // Mover la clave mediana a este nodo
    keys.insert(keys.begin() + i, mediana);
    
    std::cout << "  Clave mediana " << mediana << " sube al padre" << std::endl;
}

void BTree::remove(int k) {
    if (root == nullptr) {
        std::cout << "El árbol está vacío" << std::endl;
        return;
    }
    
    std::cout << "  Eliminando: " << k << std::endl;
    root->remove(k);
    
    if (root->keys.empty()) {
        std::cout << "  [CASO: Raíz vacía - Reducir altura del árbol]" << std::endl;
        BTreeNode* tmp = root;
        if (root->leaf) {
            root = nullptr;
        } else {
            root = root->children[0];
        }
        delete tmp;
    }
}

int BTreeNode::findKey(int k) {
    int idx = 0;
    while (idx < (int)keys.size() && keys[idx] < k)
        ++idx;
    return idx;
}

void BTreeNode::remove(int k) {
    int idx = findKey(k);
    
    if (idx < (int)keys.size() && keys[idx] == k) {
        if (leaf) {
            removeFromLeaf(idx);
        } else {
            removeFromNonLeaf(idx);
        }
    } else {
        if (leaf) {
            std::cout << "  [CASO: Clave " << k << " no encontrada]" << std::endl;
            return;
        }
        
        bool flag = (idx == (int)keys.size());
        
        if ((int)children[idx]->keys.size() < t) {
            fill(idx);
        }
        
        if (flag && idx > (int)keys.size()) {
            children[idx - 1]->remove(k);
        } else {
            children[idx]->remove(k);
        }
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    std::cout << "  [CASO: Eliminar de hoja]" << std::endl;
    keys.erase(keys.begin() + idx);
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    
    if ((int)children[idx]->keys.size() >= t) {
        std::cout << "  [CASO: Reemplazar con predecesor]" << std::endl;
        int pred = getPred(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    } else if ((int)children[idx + 1]->keys.size() >= t) {
        std::cout << "  [CASO: Reemplazar con sucesor]" << std::endl;
        int succ = getSucc(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    } else {
        std::cout << "  [CASO: Fusionar hijos y eliminar]" << std::endl;
        merge(idx);
        children[idx]->remove(k);
    }
}

int BTreeNode::getPred(int idx) {
    BTreeNode* cur = children[idx];
    while (!cur->leaf) {
        cur = cur->children[cur->keys.size()];
    }
    return cur->keys[cur->keys.size() - 1];
}

int BTreeNode::getSucc(int idx) {
    BTreeNode* cur = children[idx + 1];
    while (!cur->leaf) {
        cur = cur->children[0];
    }
    return cur->keys[0];
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && (int)children[idx - 1]->keys.size() >= t) {
        std::cout << "  >> PRÉSTAMO del hermano izquierdo" << std::endl;
        borrowFromPrev(idx);
    } else if (idx != (int)keys.size() && (int)children[idx + 1]->keys.size() >= t) {
        std::cout << "  >> PRÉSTAMO del hermano derecho" << std::endl;
        borrowFromNext(idx);
    } else {
        std::cout << "  >> FUSIÓN (MERGE) de nodos" << std::endl;
        if (idx != (int)keys.size()) {
            merge(idx);
        } else {
            merge(idx - 1);
        }
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];
    
    child->keys.insert(child->keys.begin(), keys[idx - 1]);
    
    if (!child->leaf) {
        child->children.insert(child->children.begin(), sibling->children.back());
        sibling->children.pop_back();
    }
    
    keys[idx - 1] = sibling->keys.back();
    sibling->keys.pop_back();
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];
    
    child->keys.push_back(keys[idx]);
    
    if (!child->leaf) {
        child->children.push_back(sibling->children[0]);
        sibling->children.erase(sibling->children.begin());
    }
    
    keys[idx] = sibling->keys[0];
    sibling->keys.erase(sibling->keys.begin());
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];
    
    child->keys.push_back(keys[idx]);
    
    for (auto key : sibling->keys) {
        child->keys.push_back(key);
    }
    
    if (!child->leaf) {
        for (auto c : sibling->children) {
            child->children.push_back(c);
        }
    }
    
    keys.erase(keys.begin() + idx);
    children.erase(children.begin() + idx + 1);
    
    delete sibling;
}

/*
 * ============================================================================
 *                    EJERCICIO 1: INSERCIÓN EN ÁRBOL VACÍO
 * ============================================================================
 * B-Tree de orden 3 (grado mínimo t=2)
 * Secuencia: 10
 */
void ejercicio1_insercion_vacia() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 1: INSERCIÓN EN ÁRBOL VACÍO" << std::endl;
    std::cout << "B-Tree orden 3, Secuencia: 10" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    BTree tree(2);  // t=2, orden=3
    tree.insert(10);
    
    std::cout << "\nÁrbol resultante:" << std::endl;
    tree.traverse();
}

/*
 * ============================================================================
 *                EJERCICIO 2: INSERCIÓN SIN DIVISIÓN
 * ============================================================================
 * Secuencia: 10, 20, 30
 * 
 * Se insertan valores hasta llenar el nodo raíz sin división.
 */
void ejercicio2_insercion_sin_division() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 2: INSERCIÓN SIN DIVISIÓN" << std::endl;
    std::cout << "B-Tree orden 3, Secuencia: 10, 20, 30" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    BTree tree(2);
    int valores[] = {10, 20, 30};
    
    for (int v : valores) {
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.traverse();
        std::cout << std::endl;
    }
}

/*
 * ============================================================================
 *                    EJERCICIO 3: PRIMERA DIVISIÓN (SPLIT)
 * ============================================================================
 * Secuencia: 10, 20, 30, 40
 * 
 * Al insertar el 4to elemento, la raíz se divide y crece el árbol.
 */
void ejercicio3_primera_division() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 3: PRIMERA DIVISIÓN (SPLIT)" << std::endl;
    std::cout << "B-Tree orden 3, Secuencia: 10, 20, 30, 40" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    BTree tree(2);
    int valores[] = {10, 20, 30, 40};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.traverse();
    }
}

/*
 * ============================================================================
 *                EJERCICIO 4: MÚLTIPLES DIVISIONES
 * ============================================================================
 * Secuencia: 10, 20, 30, 40, 50, 60, 70
 * 
 * Varias divisiones en cascada.
 */
void ejercicio4_multiples_divisiones() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 4: MÚLTIPLES DIVISIONES" << std::endl;
    std::cout << "B-Tree orden 3, Secuencia: 10, 20, 30, 40, 50, 60, 70" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    BTree tree(2);
    int valores[] = {10, 20, 30, 40, 50, 60, 70};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.traverse();
    }
}

/*
 * ============================================================================
 *            EJERCICIO 5: DIVISIÓN PROPAGADA (SPLIT CASCADE)
 * ============================================================================
 * Secuencia: 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
 * 
 * Divisiones que propagan hacia arriba.
 */
void ejercicio5_division_propagada() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 5: DIVISIÓN PROPAGADA" << std::endl;
    std::cout << "B-Tree orden 3, Secuencia: 10, 20, 30, 40, 50, 60, 70, 80, 90, 100" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    BTree tree(2);
    int valores[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.traverse();
    }
}

/*
 * ============================================================================
 *                EJERCICIO 6: INSERCIÓN EN ORDEN ALEATORIO
 * ============================================================================
 * Secuencia: 50, 20, 70, 10, 30, 60, 80
 * 
 * Inserciones en orden no secuencial.
 */
void ejercicio6_insercion_aleatoria() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 6: INSERCIÓN EN ORDEN ALEATORIO" << std::endl;
    std::cout << "B-Tree orden 3, Secuencia: 50, 20, 70, 10, 30, 60, 80" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    BTree tree(2);
    int valores[] = {50, 20, 70, 10, 30, 60, 80};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.traverse();
    }
}

/*
 * ============================================================================
 *                EJERCICIO 7: ELIMINACIÓN DE HOJA
 * ============================================================================
 * Construir árbol y eliminar una clave de una hoja.
 */
void ejercicio7_eliminacion_hoja() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 7: ELIMINACIÓN DE HOJA" << std::endl;
    std::cout << "B-Tree orden 3" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    BTree tree(2);
    int valores[] = {10, 20, 30, 40, 50};
    
    for (int v : valores) {
        tree.insert(v);
    }
    
    std::cout << "\nÁrbol antes de eliminar:" << std::endl;
    tree.traverse();
    
    std::cout << "\n--- Eliminando 10 ---" << std::endl;
    tree.remove(10);
    
    std::cout << "\nÁrbol después de eliminar:" << std::endl;
    tree.traverse();
}

/*
 * ============================================================================
 *                EJERCICIO 8: ELIMINACIÓN CON PRÉSTAMO
 * ============================================================================
 * Eliminar una clave que requiere préstamo de un hermano.
 */
void ejercicio8_eliminacion_prestamo() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 8: ELIMINACIÓN CON PRÉSTAMO" << std::endl;
    std::cout << "B-Tree orden 3" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    BTree tree(2);
    int valores[] = {10, 20, 30, 40, 50, 60, 70};
    
    for (int v : valores) {
        tree.insert(v);
    }
    
    std::cout << "\nÁrbol antes de eliminar:" << std::endl;
    tree.traverse();
    
    std::cout << "\n--- Eliminando 60 ---" << std::endl;
    tree.remove(60);
    
    std::cout << "\nÁrbol después de eliminar:" << std::endl;
    tree.traverse();
}

/*
 * ============================================================================
 *                EJERCICIO 9: ELIMINACIÓN CON FUSIÓN
 * ============================================================================
 * Eliminar una clave que requiere fusión (merge) de nodos.
 */
void ejercicio9_eliminacion_fusion() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 9: ELIMINACIÓN CON FUSIÓN" << std::endl;
    std::cout << "B-Tree orden 3" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    BTree tree(2);
    int valores[] = {10, 20, 30, 40};
    
    for (int v : valores) {
        tree.insert(v);
    }
    
    std::cout << "\nÁrbol antes de eliminar:" << std::endl;
    tree.traverse();
    
    std::cout << "\n--- Eliminando 30 ---" << std::endl;
    tree.remove(30);
    
    std::cout << "\nÁrbol después de eliminar:" << std::endl;
    tree.traverse();
}

/*
 * ============================================================================
 *                EJERCICIO 10: ELIMINACIÓN DE NODO INTERNO
 * ============================================================================
 * Eliminar una clave de un nodo interno (no hoja).
 */
void ejercicio10_eliminacion_interno() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 10: ELIMINACIÓN DE NODO INTERNO" << std::endl;
    std::cout << "B-Tree orden 3" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    BTree tree(2);
    int valores[] = {10, 20, 30, 40, 50, 60, 70};
    
    for (int v : valores) {
        tree.insert(v);
    }
    
    std::cout << "\nÁrbol antes de eliminar:" << std::endl;
    tree.traverse();
    
    std::cout << "\n--- Eliminando 40 (nodo interno/raíz) ---" << std::endl;
    tree.remove(40);
    
    std::cout << "\nÁrbol después de eliminar:" << std::endl;
    tree.traverse();
}

/*
 * ============================================================================
 *            EJERCICIO 11: REDUCCIÓN DE ALTURA DEL ÁRBOL
 * ============================================================================
 * Eliminaciones sucesivas que reducen la altura del árbol.
 */
void ejercicio11_reduccion_altura() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 11: REDUCCIÓN DE ALTURA DEL ÁRBOL" << std::endl;
    std::cout << "B-Tree orden 3" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    BTree tree(2);
    int valores[] = {10, 20, 30, 40, 50};
    
    for (int v : valores) {
        tree.insert(v);
    }
    
    std::cout << "\nÁrbol inicial:" << std::endl;
    tree.traverse();
    
    int eliminar[] = {50, 40, 30};
    for (int v : eliminar) {
        std::cout << "\n--- Eliminando " << v << " ---" << std::endl;
        tree.remove(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.traverse();
    }
}

/*
 * ============================================================================
 *                    EJERCICIO 12: B-TREE ORDEN 5
 * ============================================================================
 * Ejemplo con un B-Tree de mayor orden.
 */
void ejercicio12_btree_orden5() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "EJERCICIO 12: B-TREE ORDEN 5" << std::endl;
    std::cout << "B-Tree orden 5 (t=3), Secuencia: 10, 20, 30, 40, 50, 60, 70, 80, 90, 100" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    BTree tree(3);  // t=3, orden=5
    int valores[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    for (int v : valores) {
        std::cout << "\n--- Insertando " << v << " ---" << std::endl;
        tree.insert(v);
        std::cout << "Árbol actual:" << std::endl;
        tree.traverse();
    }
}

int main() {
    std::cout << "\n" << std::string(70, '*') << std::endl;
    std::cout << "        EJERCICIOS DE CASOS EDGE EN ÁRBOLES B" << std::endl;
    std::cout << std::string(70, '*') << std::endl;
    
    std::cout << "\n[MENÚ DE EJERCICIOS]" << std::endl;
    std::cout << "1.  Inserción en árbol vacío" << std::endl;
    std::cout << "2.  Inserción sin división" << std::endl;
    std::cout << "3.  Primera división (split)" << std::endl;
    std::cout << "4.  Múltiples divisiones" << std::endl;
    std::cout << "5.  División propagada (split cascade)" << std::endl;
    std::cout << "6.  Inserción en orden aleatorio" << std::endl;
    std::cout << "7.  Eliminación de hoja" << std::endl;
    std::cout << "8.  Eliminación con préstamo" << std::endl;
    std::cout << "9.  Eliminación con fusión" << std::endl;
    std::cout << "10. Eliminación de nodo interno" << std::endl;
    std::cout << "11. Reducción de altura del árbol" << std::endl;
    std::cout << "12. B-Tree orden 5" << std::endl;
    std::cout << "0.  Ejecutar todos los ejercicios" << std::endl;
    
    int opcion;
    std::cout << "\nSelecciona un ejercicio (0-12): ";
    std::cin >> opcion;
    
    switch(opcion) {
        case 0:
            ejercicio1_insercion_vacia();
            ejercicio2_insercion_sin_division();
            ejercicio3_primera_division();
            ejercicio4_multiples_divisiones();
            ejercicio5_division_propagada();
            ejercicio6_insercion_aleatoria();
            ejercicio7_eliminacion_hoja();
            ejercicio8_eliminacion_prestamo();
            ejercicio9_eliminacion_fusion();
            ejercicio10_eliminacion_interno();
            ejercicio11_reduccion_altura();
            ejercicio12_btree_orden5();
            break;
        case 1: ejercicio1_insercion_vacia(); break;
        case 2: ejercicio2_insercion_sin_division(); break;
        case 3: ejercicio3_primera_division(); break;
        case 4: ejercicio4_multiples_divisiones(); break;
        case 5: ejercicio5_division_propagada(); break;
        case 6: ejercicio6_insercion_aleatoria(); break;
        case 7: ejercicio7_eliminacion_hoja(); break;
        case 8: ejercicio8_eliminacion_prestamo(); break;
        case 9: ejercicio9_eliminacion_fusion(); break;
        case 10: ejercicio10_eliminacion_interno(); break;
        case 11: ejercicio11_reduccion_altura(); break;
        case 12: ejercicio12_btree_orden5(); break;
        default:
            std::cout << "Opción no válida." << std::endl;
    }
    
    return 0;
}
