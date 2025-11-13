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

Node* insert(Node* node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

int main() {
    Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    std::cout << "Recorrido inorden del arbol: ";
    inorder(root);
    std::cout << std::endl;

    return 0;
}
