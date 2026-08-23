// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// ===== DoublyLinkedList.hpp =====
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

// ===== LRUCache.hpp =====
template<typename K, typename V>
class LRUCache {
private:
    int capacity;
    DoublyLinkedList<K,V> dll;
    unordered_map<K, Node<K,V>*> cache;

public:
    LRUCache(int capacity) : capacity(capacity) {}
    
    V get(K key) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            throw runtime_error("Key not found");
        }
        
        Node<K,V>* node = it->second;
        dll.moveToFront(node);
        return node->value;
    }
    
    void put(K key, V value) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            // Key exists, update value and move to front
            Node<K,V>* node = it->second;
            node->value = value;
            dll.moveToFront(node);
        } else {
            // Key doesn't exist, add new entry
            if (cache.size() >= capacity) {
                // Remove least recently used item
                Node<K,V>* lastNode = dll.getTail();
                cache.erase(lastNode->key);
                dll.removeNode(lastNode);
            }
            
            // Add new item to front
            Node<K,V>* newNode = dll.addToFront(key, value);
            cache[key] = newNode;
        }
    }
    
    bool contains(K key) const {
        return cache.find(key) != cache.end();
    }
    
    int getSize() const {
        return cache.size();
    }
    
    bool isEmpty() const {
        return cache.empty();
    }
    
    void clear() {
        while (!dll.isEmpty()) {
            Node<K,V>* node = dll.removeLast();
            cache.erase(node->key);
            delete node;
        }
    }
    
    void display() const {
        cout << "\nLRU Cache Contents:" << endl;
        Node<K,V>* current = dll.getHead();
        while (current) {
            cout << current->key << " -> " << current->value << endl;
            current = current->next;
        }
        cout << "Cache size: " << cache.size() << "/" << capacity << endl;
    }
};

// ===== LRUCacheDemo.cpp =====
int main() {
    // Create LRU cache with capacity 3
    LRUCache<int, string> cache(3);
    
    // Add some entries
    cout << "Adding entries to cache..." << endl;
    cache.put(1, "One");
    cache.put(2, "Two");
    cache.put(3, "Three");
    cache.display();
    
    // Try to get an entry
    cout << "\nGetting value for key 2..." << endl;
    cout << "Value: " << cache.get(2) << endl;
    cache.display();  // 2 should move to front
    
    // Add new entry when cache is full
    cout << "\nAdding new entry when cache is full..." << endl;
    cache.put(4, "Four");  // Should evict least recently used item
    cache.display();
    
    // Try to access non-existent key
    cout << "\nTrying to access non-existent key..." << endl;
    try {
        cache.get(1);  // Should throw exception
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    // Update existing entry
    cout << "\nUpdating existing entry..." << endl;
    cache.put(2, "Two Updated");
    cache.display();
    
    // Clear cache
    cout << "\nClearing cache..." << endl;
    cache.clear();
    cache.display();
    
    return 0;
} 

