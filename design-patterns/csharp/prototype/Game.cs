using System;

namespace Prototype
{
    class Game
    {
        static void Main(string[] args)
        {
            var registry = new EnemyRegistry();

            // Register prototype enemies
            registry.Register("flying", new Enemy("FlyingEnemy", 100, 12.0, false, "Laser"));
            registry.Register("armored", new Enemy("ArmoredEnemy", 300, 6.0, true, "Cannon"));

            // Clone from registry
            Enemy e1 = registry.Get("flying");
            Enemy e2 = registry.Get("flying");
            e2.SetHealth(80); // this one is damaged

            Enemy e3 = registry.Get("armored");

            // Print enemy stats
            e1.PrintStats();
            e2.PrintStats();
            e3.PrintStats();
        }
    }
} 