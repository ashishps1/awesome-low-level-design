using System;

namespace StackOverflow
{
    public class Tag
    {
        public int Id { get; }
        public string Name { get; }

        public Tag(string name)
        {
            Id = GenerateId();
            Name = name;
        }

        private int GenerateId()
        {
            return (int)(DateTime.Now.Ticks % int.MaxValue);
        }
    }
}