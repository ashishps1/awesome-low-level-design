using System;
using System.Collections.Generic;

namespace LRUCacheNamespace
{
    public class LRUCache<K, V>
    {
        private readonly int _capacity;
        private readonly Dictionary<K, Node<K, V>> _cache;
        private readonly Node<K, V> _head;
        private readonly Node<K, V> _tail;

        public LRUCache(int capacity)
        {
            _capacity = capacity;
            _cache = new Dictionary<K, Node<K, V>>(capacity);

            // Initialize head and tail dummy nodes
            _head = new Node<K, V>(default, default);
            _tail = new Node<K, V>(default, default);
            _head.Next = _tail;
            _tail.Prev = _head;
        }

        public V Get(K key)
        {
            if (!_cache.TryGetValue(key, out var node))
            {
                return default; // Key doesn't exist, return null
            }

            MoveToHead(node); // Move the accessed node to the head
            return node.Value;
        }

        public void Put(K key, V value)
        {
            if (_cache.TryGetValue(key, out var node))
            {
                node.Value = value; // Update the value
                MoveToHead(node);
            }
            else
            {
                var newNode = new Node<K, V>(key, value);
                _cache[key] = newNode;
                AddToHead(newNode);

                if (_cache.Count > _capacity)
                {
                    var removedNode = RemoveTail();
                    _cache.Remove(removedNode.Key);
                }
            }
        }

        private void AddToHead(Node<K, V> node)
        {
            node.Prev = _head;
            node.Next = _head.Next;
            _head.Next.Prev = node;
            _head.Next = node;
        }

        private void RemoveNode(Node<K, V> node)
        {
            var prevNode = node.Prev;
            var nextNode = node.Next;

            prevNode.Next = nextNode;
            nextNode.Prev = prevNode;
        }

        private void MoveToHead(Node<K, V> node)
        {
            RemoveNode(node);
            AddToHead(node);
        }

        private Node<K, V> RemoveTail()
        {
            var node = _tail.Prev;
            RemoveNode(node);
            return node;
        }
    }
}