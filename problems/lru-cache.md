# Designing a Cache in Java [LRU eviction policy]

This article explores the design and implementation of a basic Cache system using Java, following object-oriented design principles.

A Cache is a high speed data storage layer, which allows storing a subset of the original data (usually the most frequently queried data), so that future requests made for that data can be served up faster. This guide outlines the design and implementation of a Cache from a generic perspective.


## Understanding the Requirements
The system will enable:
- Storing some data as a key-value pair.
- Retrieving some data based on the provided key.
- Eviction of data when the cache reaches its capacity.

## Core Use Cases
- **Storing Frequently Accessed Data**: The consumers of this class can choose to store frequently accessed data as a key-value pair.
- **Retrieving Data**: Consumers of this cache can retrieve the stored data with the correct key value.
- **Eviction Policy**: The cache automatically evicts when the storage reaches its capacity. Here using the **LRU Eviction Policy**.

## Key Classes:
- **Cache Class**: Responsible for managing the storing and retrieval of data.
- **Storage Class**: Responsible for storing the data.
- **Eviction Class**: Responsible for using an eviction policy to suggest eviction of the oldest data. 
- **Node**: Represent a Doubly Linked List's Node, which will be used to store the keys.
- **Doubly Linked List**: Responsible for detaching a node from the list, adding a new node at the end of the list.


## Java Implementation

1. The Cache interface for managing the cache functions :
```java
package Cache.cacheManager;

import Cache.exceptions.KeyNotFoundException;
import Cache.exceptions.NullElementException;

public interface CacheManager {

    void addData(String key, String value) throws NullElementException;

    String getData(String key) throws KeyNotFoundException, NullElementException;

}
```

```java
package Cache.cacheManager;

import Cache.eviction.Eviction;
import Cache.exceptions.KeyNotFoundException;
import Cache.exceptions.NullElementException;
import Cache.storage.Storage;

DefaultCacheManager implements CacheManager{

    private final Storage storageService;
    private final Eviction evictionService;

    public DefaultCacheManager(Storage storageService, Eviction evictionService) {
        this.storageService = storageService;
        this.evictionService = evictionService;
    }

    @Override
    public void addData(String key, String value) throws NullElementException {
            storageService.storeData(key,value);
    }

    @Override
    public String getData(String key) throws KeyNotFoundException, NullElementException {
        return storageService.getData(key);
    }
}

```
2. The Storage interface for managing the storage and retrieval functions :

```java
package Cache.storage;

import Cache.exceptions.KeyNotFoundException;
import Cache.exceptions.NullElementException;

public interface Storage {

    void storeData(String key, String value) throws NullElementException;

    String getData(String key) throws KeyNotFoundException, NullElementException;

    void removeData(String key);


}

```
```java
package Cache.storage;

import Cache.eviction.DefaultLRUEvictionService;
import Cache.eviction.Eviction;
import Cache.exceptions.KeyNotFoundException;
import Cache.exceptions.NullElementException;

import java.util.HashMap;
import java.util.Map;

public class DefaultStorage implements Storage{

    private final int DEFAULT_CAPACITY = 5;
    private Integer capacity;
    private final Map<String, String> storageMap;
    private Eviction evictionService;

    public DefaultStorage(Integer capacity, Eviction evictionService) {
        this.capacity = capacity == 0 ? DEFAULT_CAPACITY : capacity;
        storageMap = new HashMap<>(capacity);
        this.evictionService = evictionService;
    }

    public DefaultStorage() {
        this.capacity = DEFAULT_CAPACITY;
        storageMap = new HashMap<>(capacity);
        this.evictionService = new DefaultLRUEvictionService();
    }

    @Override
    public void storeData(String key, String value) throws NullElementException {
        if (storageMap.size() == capacity) {
            String removalKey = evictionService.evictData();
            removeData(removalKey);
        }
        storageMap.put(key,value);
        evictionService.setAccessedKey(key);
    }

    @Override
    public String getData(String key) throws KeyNotFoundException, NullElementException {
        if (!storageMap.containsKey(key)) throw new KeyNotFoundException();
        evictionService.setAccessedKey(key);
        return storageMap.get(key);
    }

    @Override
    public void removeData(String key) {
        if (!storageMap.containsKey(key)) return;
        storageMap.remove(key);
    }
}

```
3. The Eviction Service for coming up with the data to evict

```java
package Cache.eviction;

import Cache.exceptions.NullElementException;

public interface Eviction {

    void setAccessedKey(String key) throws NullElementException;

    String evictData();

}

```
```java
package Cache.eviction;

import Cache.algorithms.DoublyLinkedList.DoublyLinkedList;
import Cache.algorithms.LinkedListNode.Node;
import Cache.exceptions.NullElementException;

import java.util.HashMap;
import java.util.Map;

public class DefaultLRUEvictionService implements Eviction{

    DoublyLinkedList doublyLinkedList;
    Map<String, Node> dllMapper;

    public DefaultLRUEvictionService() {
        this.doublyLinkedList = new DoublyLinkedList();
        this.dllMapper = new HashMap<>();
    }

    @Override
    public void setAccessedKey(String key) throws NullElementException {
        if (dllMapper.containsKey(key)){
            doublyLinkedList.detachNode(dllMapper.get(key));
            doublyLinkedList.addElementAtLast(key);
        }else{
            Node newNode = doublyLinkedList.addElementAtLast(key);
            dllMapper.put(key, newNode);

        }
    }

    @Override
    public String evictData() {
        Node first = doublyLinkedList.getFirstNode();
        if(first == null) {
            return null;
        }
        doublyLinkedList.detachNode(first);
        return first.getElement();
    }
}

```
4. The data in the eviction service is stored as a Node. The LRU eviction policy is implemented using a Doubly Linked List and a Map of key & Node. 

```java
package Cache.algorithms.LinkedListNode;

public class Node {
    public String element;
    public Node previous;
    public Node next;

    public Node(String element) {
        this.element = element;
        previous = null;
        next = null;
    }

    public String getElement() {
        return element;
    }

    public Node getPrevious() {
        return previous;
    }

    public Node getNext() {
        return next;
    }
}

```
```java
package Cache.algorithms.DoublyLinkedList;

import Cache.algorithms.LinkedListNode.Node;
import Cache.exceptions.NullElementException;

public class DoublyLinkedList {
/**
 * The first and the last represent the two pointers, head and tail that are in a doubly linkedlist
 * */
    private Node first;
    private Node last;

    public DoublyLinkedList() {
        this.first = new Node(null);
        this.last = new Node(null);
        first.next = last;
        last.previous = first;
    }

    public Node addElementAtLast(String element) throws NullElementException {
        if (element == null || element.isEmpty()) {
            throw new NullElementException();
        }
        Node node = new Node(element);
        Node lastPrevious = last.previous;
        lastPrevious.next = node;
        node.next= last;
        last.previous = node;
        node.previous = lastPrevious;

        return node;
    }

    public void detachNode(Node node) {
        if (node == null) return;
        node.previous.next = node.next;
        node.next.previous = node.previous;
    }

    public boolean isItemPresent() {
        return first.next != last;
    }

    public Node getFirstNode()  {
        if (!isItemPresent()) {
            return null;
        }
        return first.next;
    }

    public Node getLastNode() {
        if (!isItemPresent()) {
            return null;
        }
        return last.previous;
    }


}

```









