using System;

namespace Prototype
{
    public class Enemy : IEnemyPrototype
    {
        private string type;
        private int health;
        private double speed;
        private bool armored;
        private string weapon;

        public Enemy(string type, int health, double speed, bool armored, string weapon)
        {
            this.type = type;
            this.health = health;
            this.speed = speed;
            this.armored = armored;
            this.weapon = weapon;
        }

        public IEnemyPrototype Clone()
        {
            return new Enemy(type, health, speed, armored, weapon);
        }

        public void SetHealth(int health)
        {
            this.health = health;
        }

        public void PrintStats()
        {
            Console.WriteLine($"{type} [Health: {health}, Speed: {speed}, Armored: {armored}, Weapon: {weapon}]");
        }
    }
} 