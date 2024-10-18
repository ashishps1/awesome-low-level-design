using System;
using System.Collections.Generic;

namespace Cricinfo
{
    public class Match
    {
        private readonly string id;
        private readonly string title;
        private readonly string venue;
        private readonly DateTime startTime;
        private readonly List<Team> teams;
        private MatchStatus status;
        private Scorecard scorecard;

        public Match(string id, string title, string venue, DateTime startTime, List<Team> teams)
        {
            this.id = id;
            this.title = title;
            this.venue = venue;
            this.startTime = startTime;
            this.teams = teams;
            this.status = MatchStatus.SCHEDULED;
        }

        public string GetId()
        {
            return id;
        }

        public void SetStatus(MatchStatus status)
        {
            this.status = status;
        }

        public string GetTitle()
        {
            return title;
        }
    }
}