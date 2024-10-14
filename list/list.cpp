#include <iostream>

struct Node {
    int data;
    Node* next;
};
s
class LinkedList {
public:
    LinkedList() : head(nullptr) {}

    void insert(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }

    void display() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

private:
    Node* head;
};

int main() {
    LinkedList list;
    list.insert(10);
    list.insert(20);
    list.insert(30);

    list.display();

    return 0;
}