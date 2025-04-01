using System;
using System.Collections.Concurrent;
using System.Collections.Generic;

namespace Cricinfo
{
    public class MatchService
    {
        private static MatchService instance;
        private readonly ConcurrentDictionary<string, Match> matches;

        private MatchService()
        {
            matches = new ConcurrentDictionary<string, Match>();
        }

        public static MatchService GetInstance()
        {
            if (instance == null)
            {
                instance = new MatchService();
            }
            return instance;
        }

        public void AddMatch(Match match)
        {
            matches[match.GetId()] = match;
        }

        public Match GetMatch(string matchId)
        {
            return matches.ContainsKey(matchId) ? matches[matchId] : null;
        }

        public List<Match> GetAllMatches()
        {
            return new List<Match>(matches.Values);
        }

        public void UpdateMatchStatus(string matchId, MatchStatus status)
        {
            if (matches.ContainsKey(matchId))
            {
                matches[matchId].SetStatus(status);
            }
        }
    }
}