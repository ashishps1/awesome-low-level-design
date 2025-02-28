using System;
using System.Collections.Generic;

namespace Cricinfo
{
    public class Team
    {
        private readonly string id;
        private readonly string name;
        private readonly List<Player> players;

        public Team(string id, string name, List<Player> players)
        {
            this.id = id;
            this.name = name;
            this.players = players;
        }
    }
}