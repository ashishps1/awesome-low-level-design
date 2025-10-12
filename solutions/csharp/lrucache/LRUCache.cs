class LRUCache<K, V>
{
    private readonly int capacity;
    private readonly Dictionary<K, Node<K, V>> map;
    private readonly DoublyLinkedList<K, V> dll;
    private readonly object lockObject = new object();

    public LRUCache(int capacity)
    {
        this.capacity = capacity;
        this.map = new Dictionary<K, Node<K, V>>();
        this.dll = new DoublyLinkedList<K, V>();
    }

    public V Get(K key)
    {
        lock (lockObject)
        {
            if (!map.ContainsKey(key)) return default(V);
            Node<K, V> node = map[key];
            dll.MoveToFront(node);
            return node.value;
        }
    }

    public void Put(K key, V value)
    {
        lock (lockObject)
        {
            if (map.ContainsKey(key))
            {
                Node<K, V> node = map[key];
                node.value = value;
                dll.MoveToFront(node);
            }
            else
            {
                if (map.Count == capacity)
                {
                    Node<K, V> lru = dll.RemoveLast();
                    if (lru != null) map.Remove(lru.key);
                }
                Node<K, V> newNode = new Node<K, V>(key, value);
                dll.AddFirst(newNode);
                map[key] = newNode;
            }
        }
    }

    public void Remove(K key)
    {
        lock (lockObject)
        {
            if (!map.ContainsKey(key)) return;
            Node<K, V> node = map[key];
            dll.Remove(node);
            map.Remove(key);
        }
    }
}