using System;
using System.Collections.Generic;

namespace Prototype
{
    public class EnemyRegistry
    {
        private readonly Dictionary<string, Enemy> prototypes = new Dictionary<string, Enemy>();

        public void Register(string key, Enemy prototype)
        {
            prototypes[key] = prototype;
        }

        public Enemy Get(string key)
        {
            if (prototypes.TryGetValue(key, out var prototype))
            {
                return (Enemy)prototype.Clone();
            }
            throw new ArgumentException($"No prototype registered for: {key}");
        }
    }
} 