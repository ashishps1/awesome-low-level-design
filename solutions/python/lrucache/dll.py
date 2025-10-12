from typing import TypeVar, Generic, Optional
from node import Node

K = TypeVar('K')
V = TypeVar('V')

class DoublyLinkedList(Generic[K, V]):
    def __init__(self):
        self.head: Node[K, V] = Node(None, None)  # Dummy head
        self.tail: Node[K, V] = Node(None, None)  # Dummy tail
        self.head.next = self.tail
        self.tail.prev = self.head

    def add_first(self, node: Node[K, V]) -> None:
        node.next = self.head.next
        node.prev = self.head
        self.head.next.prev = node
        self.head.next = node

    def remove(self, node: Node[K, V]) -> None:
        node.prev.next = node.next
        node.next.prev = node.prev

    def move_to_front(self, node: Node[K, V]) -> None:
        self.remove(node)
        self.add_first(node)

    def remove_last(self) -> Optional[Node[K, V]]:
        if self.tail.prev == self.head:
            return None
        last = self.tail.prev
        self.remove(last)
        return last