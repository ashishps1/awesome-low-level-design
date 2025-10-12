import threading
from typing import TypeVar, Generic, Optional, Dict
from dll import DoublyLinkedList
from node import Node

K = TypeVar('K')
V = TypeVar('V')

class LRUCache(Generic[K, V]):
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.map: Dict[K, Node[K, V]] = {}
        self.dll: DoublyLinkedList[K, V] = DoublyLinkedList()
        self.lock = threading.Lock()

    def get(self, key: K) -> Optional[V]:
        with self.lock:
            if key not in self.map:
                return None
            node = self.map[key]
            self.dll.move_to_front(node)
            return node.value

    def put(self, key: K, value: V) -> None:
        with self.lock:
            if key in self.map:
                node = self.map[key]
                node.value = value
                self.dll.move_to_front(node)
            else:
                if len(self.map) == self.capacity:
                    lru = self.dll.remove_last()
                    if lru is not None:
                        del self.map[lru.key]
                new_node = Node(key, value)
                self.dll.add_first(new_node)
                self.map[key] = new_node

    def remove(self, key: K) -> None:
        with self.lock:
            if key not in self.map:
                return
            node = self.map[key]
            self.dll.remove(node)
            del self.map[key]