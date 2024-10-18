using System.Collections.Generic;

namespace Cricinfo
{
    public class CricinfoSystem
    {
        private readonly MatchService matchService;
        private readonly ScorecardService scorecardService;

        public CricinfoSystem()
        {
            matchService = MatchService.GetInstance();
            scorecardService = ScorecardService.GetInstance();
        }

        public void AddMatch(Match match)
        {
            matchService.AddMatch(match);
        }

        public Match GetMatch(string matchId)
        {
            return matchService.GetMatch(matchId);
        }

        public List<Match> GetAllMatches()
        {
            return matchService.GetAllMatches();
        }

        public void UpdateMatchStatus(string matchId, MatchStatus status)
        {
            matchService.UpdateMatchStatus(matchId, status);
        }

        public void CreateScorecard(Match match)
        {
            scorecardService.CreateScorecard(match);
        }

        public Scorecard GetScorecard(string scorecardId)
        {
            return scorecardService.GetScorecard(scorecardId);
        }

        public void UpdateScore(string scorecardId, string teamId, int score)
        {
            scorecardService.UpdateScore(scorecardId, teamId, score);
        }

        public void AddInnings(string scorecardId, Innings innings)
        {
            scorecardService.AddInnings(scorecardId, innings);
        }
    }
}