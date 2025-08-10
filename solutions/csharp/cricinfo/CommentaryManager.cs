class CommentaryManager
{
    private static volatile CommentaryManager instance;
    private static readonly object lockObject = new object();
    private readonly Dictionary<string, List<string>> commentaryTemplates;
    private readonly Random random;

    private CommentaryManager()
    {
        commentaryTemplates = new Dictionary<string, List<string>>();
        random = new Random();
        InitializeTemplates();
    }

    public static CommentaryManager GetInstance()
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                {
                    instance = new CommentaryManager();
                }
            }
        }
        return instance;
    }

    private void InitializeTemplates()
    {
        commentaryTemplates["RUNS_0"] = new List<string>
        {
            "%s defends solidly.",
            "No run, good fielding by the cover fielder.",
            "A dot ball to end the over.",
            "Pushed to mid-on, but no run."
        };

        commentaryTemplates["RUNS_1"] = new List<string>
        {
            "Tucked away to the leg side for a single.",
            "Quick single taken by %s.",
            "Pushed to long-on for one."
        };

        commentaryTemplates["RUNS_2"] = new List<string>
        {
            "Two runs taken!",
            "Quick double taken by %s.",
            "Pushed to mid-on for two."
        };

        commentaryTemplates["RUNS_4"] = new List<string>
        {
            "FOUR! %s smashes it through the covers!",
            "Beautiful shot! That's a boundary.",
            "Finds the gap perfectly. Four runs."
        };

        commentaryTemplates["RUNS_6"] = new List<string>
        {
            "SIX! That's out of the park!",
            "%s sends it sailing over the ropes!",
            "Massive hit! It's a maximum."
        };

        commentaryTemplates["WICKET_BOWLED"] = new List<string>
        {
            "BOWLED HIM! %s misses completely and the stumps are shattered!",
            "Cleaned up! A perfect yorker from %s."
        };

        commentaryTemplates["WICKET_CAUGHT"] = new List<string>
        {
            "CAUGHT! %s skies it and the fielder takes a comfortable catch.",
            "Out! A brilliant catch in the deep by %s."
        };

        commentaryTemplates["WICKET_LBW"] = new List<string>
        {
            "LBW! That one kept low and struck %s right in front.",
            "%s completely misjudged the line and pays the price."
        };

        commentaryTemplates["WICKET_STUMPED"] = new List<string>
        {
            "STUMPED! %s misses it, and the keeper does the rest!",
            "Gone! Lightning-fast work by the keeper to stump %s."
        };

        commentaryTemplates["EXTRA_WIDE"] = new List<string>
        {
            "That's a wide. The umpire signals an extra run.",
            "Too far down the leg side, that'll be a wide."
        };

        commentaryTemplates["EXTRA_NO_BALL"] = new List<string>
        {
            "No ball! %s has overstepped. It's a free hit.",
            "It's a no-ball for overstepping."
        };
    }

    public string GenerateCommentary(Ball ball)
    {
        string key = GetEventKey(ball);
        var templates = commentaryTemplates.ContainsKey(key) ? 
                       commentaryTemplates[key] : 
                       new List<string> { "Just a standard delivery." };

        string template = templates[random.Next(templates.Count)];

        string batsmanName = ball.GetFacedBy()?.GetName() ?? "";

        return template.Replace("%s", batsmanName);
    }

    private string GetEventKey(Ball ball)
    {
        if (ball.IsWicket())
        {
            return $"WICKET_{ball.GetWicket().GetWicketType()}";
        }

        if (ball.GetExtraType().HasValue)
        {
            return $"EXTRA_{ball.GetExtraType().Value}";
        }

        int runs = ball.GetRunsScored();
        if (runs >= 0 && runs <= 6)
        {
            return $"RUNS_{runs}";
        }

        return "DEFAULT";
    }
}