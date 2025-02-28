using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Threading;

namespace Cricinfo
{
    public class ScorecardService
    {
        private static ScorecardService instance;
        private readonly ConcurrentDictionary<string, Scorecard> scorecards;
        private int scorecardIdCounter;

        private ScorecardService()
        {
            scorecards = new ConcurrentDictionary<string, Scorecard>();
            scorecardIdCounter = 0;
        }

        public static ScorecardService GetInstance()
        {
            if (instance == null)
            {
                instance = new ScorecardService();
            }
            return instance;
        }

        public void CreateScorecard(Match match)
        {
            string scorecardId = GenerateScorecardId(match.GetId());
            Scorecard scorecard = new Scorecard(scorecardId, match);
            scorecards[scorecardId] = scorecard;
        }

        public Scorecard GetScorecard(string scorecardId)
        {
            scorecards.TryGetValue(scorecardId, out Scorecard scorecard);
            return scorecard;
        }

        public void UpdateScore(string scorecardId, string teamId, int score)
        {
            if (scorecards.TryGetValue(scorecardId, out Scorecard scorecard))
            {
                scorecard.UpdateScore(teamId, score);
            }
        }

        public void AddInnings(string scorecardId, Innings innings)
        {
            if (scorecards.TryGetValue(scorecardId, out Scorecard scorecard))
            {
                scorecard.AddInnings(innings);
            }
        }

        private string GenerateScorecardId(string matchId)
        {
            int scorecardId = Interlocked.Increment(ref scorecardIdCounter);
            return $"SC-{matchId}-{scorecardId:D4}";
        }
    }
}