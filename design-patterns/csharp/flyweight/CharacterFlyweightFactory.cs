using System;
using System.Collections.Generic;

namespace Flyweight
{
    public class CharacterFlyweightFactory
    {
        private static readonly Dictionary<string, ICharacterFlyweight> flyweightCache = new();

        public static ICharacterFlyweight GetFlyweight(char symbol, string fontFamily, int fontSize, string color)
        {
            string key = $"{symbol}-{fontSize}-{color}";
            if (!flyweightCache.ContainsKey(key))
            {
                flyweightCache[key] = new CharacterGlyph(symbol, fontFamily, fontSize, color);
            }
            return flyweightCache[key];
        }

        public int GetFlyweightCount()
        {
            return flyweightCache.Count;
        }
    }
} 