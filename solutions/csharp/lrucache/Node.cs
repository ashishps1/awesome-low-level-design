namespace LRUCacheNamespace
{
    public class Node<K, V>
    {
        public K Key { get; }
        public V Value { get; set; }
        public Node<K, V> Prev { get; set; }
        public Node<K, V> Next { get; set; }

        public Node(K key, V value)
        {
            Key = key;
            Value = value;
        }
    }
}