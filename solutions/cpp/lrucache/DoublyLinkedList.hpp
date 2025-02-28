#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

template<typename K, typename V>
struct Node {
    K key;
    V value;
    Node* prev;
    Node* next;
    
    Node(K key, V value) : key(key), value(value), prev(nullptr), next(nullptr) {}
};

template<typename K, typename V>
class DoublyLinkedList {
private:
    Node<K,V>* head;
    Node<K,V>* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~DoublyLinkedList() {
        while (head) {
            Node<K,V>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    Node<K,V>* addToFront(K key, V value) {
        Node<K,V>* node = new Node<K,V>(key, value);
        
        if (!head) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        
        size++;
        return node;
    }
    
    void moveToFront(Node<K,V>* node) {
        if (node == head) return;
        
        if (node == tail) {
            tail = node->prev;
            tail->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        
        node->prev = nullptr;
        node->next = head;
        head->prev = node;
        head = node;
    }
    
    void removeNode(Node<K,V>* node) {
        if (node == head) {
            head = node->next;
            if (head) head->prev = nullptr;
        } else if (node == tail) {
            tail = node->prev;
            tail->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        
        delete node;
        size--;
        
        if (size == 0) {
            head = tail = nullptr;
        }
    }
    
    Node<K,V>* removeLast() {
        if (!tail) return nullptr;
        
        Node<K,V>* node = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        
        size--;
        return node;
    }
    
    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
    Node<K,V>* getHead() const { return head; }
    Node<K,V>* getTail() const { return tail; }
};

#endif 