using System.Collections.Generic;

namespace Cricinfo
{
    public class Scorecard
    {
        private readonly string id;
        private readonly Match match;
        private readonly Dictionary<string, int> teamScores;
        private readonly List<Innings> innings;

        public Scorecard(string id, Match match)
        {
            this.id = id;
            this.match = match;
            this.teamScores = new Dictionary<string, int>();
            this.innings = new List<Innings>();
        }

        public void UpdateScore(string teamId, int score)
        {
            teamScores[teamId] = score;
        }

        public void AddInnings(Innings innings)
        {
            this.innings.Add(innings);
        }

        public string GetId()
        {
            return id;
        }

        public Match GetMatch()
        {
            return match;
        }

        public Dictionary<string, int> GetTeamScores()
        {
            return teamScores;
        }

        public List<Innings> GetInnings()
        {
            return innings;
        }
    }
}