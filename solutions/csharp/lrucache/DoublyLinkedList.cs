class DoublyLinkedList<K, V>
{
    private readonly Node<K, V> head;
    private readonly Node<K, V> tail;

    public DoublyLinkedList()
    {
        head = new Node<K, V>(default(K), default(V));
        tail = new Node<K, V>(default(K), default(V));
        head.next = tail;
        tail.prev = head;
    }

    public void AddFirst(Node<K, V> node)
    {
        node.next = head.next;
        node.prev = head;
        head.next.prev = node;
        head.next = node;
    }

    public void Remove(Node<K, V> node)
    {
        node.prev.next = node.next;
        node.next.prev = node.prev;
    }

    public void MoveToFront(Node<K, V> node)
    {
        Remove(node);
        AddFirst(node);
    }

    public Node<K, V> RemoveLast()
    {
        if (tail.prev == head) return null;
        Node<K, V> last = tail.prev;
        Remove(last);
        return last;
    }
}