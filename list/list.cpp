#include <iostream>


/*creamos la estructura*/
struct Node {
    int data;
    Node* next;
};

/*creamos la clase LinkedList*/
class LinkedList {
public:
    /*constructor de la clase*/
    Node* head;

    LinkedList() : head(nullptr) {}

    /*metodo para agregar un nodo*/
    void addNode(int value) {
        Node* newNode = new Node(); //creamos un nuevo nodo
        newNode->data = value;   //asignamos el valor al nodo
        newNode->next = nullptr; //asignamos el siguiente nodo como nulo

        if (head == nullptr) { //si la lista esta vacia el nuevo nodo es cabeza
            head = newNode; 
        } else {    //si no recorremos la lista hasta el final y agregamos el nuevo nodo
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode; //agregamos el nuevo nodo al final
        }
    }

    void addNodeinHead(int value) {
        Node* newNode = new Node(); //creamos un nuevo nodo
        newNode->data = value;   //asignamos el valor al nodo
        newNode->next = head; //asignamos el siguiente nodo como nulo

        head = newNode; //si la lista esta vacia el nuevo nodo es cabeza
    }


    /*metodo para imprimir la lista*/
    void printList() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

/*funcion principal: example*/
int main() {
    LinkedList list1;
    list1.addNode(1);
    list1.addNode(2);
    list1.addNodeinHead(0);
    list1.printList(); // Output: 0 1 2

    LinkedList list2;
    list2.addNode(10);
    list2.addNode(20);
    list2.addNodeinHead(5);
    list2.printList(); // Output: 5 10 20

    return 0;
}