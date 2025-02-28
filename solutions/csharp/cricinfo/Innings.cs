using System.Collections.Generic;

namespace Cricinfo
{
    public class Innings
    {
        private readonly string id;
        private readonly string battingTeamId;
        private readonly string bowlingTeamId;
        private readonly List<Over> overs;

        public Innings(string id, string battingTeamId, string bowlingTeamId)
        {
            this.id = id;
            this.battingTeamId = battingTeamId;
            this.bowlingTeamId = bowlingTeamId;
            this.overs = new List<Over>();
        }

        public void AddOver(Over over)
        {
            this.overs.Add(over);
        }

        public string GetId()
        {
            return id;
        }

        public List<Over> GetOvers()
        {
            return overs;
        }

        public string GetBattingTeamId()
        {
            return battingTeamId;
        }

        public string GetBowlingTeamId()
        {
            return bowlingTeamId;
        }
    }
}