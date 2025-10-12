class LinkedInSystem
{
    private static volatile LinkedInSystem instance;
    private static readonly object syncRoot = new object();

    private readonly Dictionary<string, Member> members = new Dictionary<string, Member>();
    private readonly ConnectionService connectionService;
    private readonly NewsFeedService newsFeedService;
    private readonly SearchService searchService;

    private LinkedInSystem()
    {
        connectionService = new ConnectionService(new NotificationService());
        newsFeedService = new NewsFeedService();
        searchService = new SearchService(members.Values);
    }

    public static LinkedInSystem GetInstance()
    {
        if (instance == null)
        {
            lock (syncRoot)
            {
                if (instance == null)
                {
                    instance = new LinkedInSystem();
                }
            }
        }
        return instance;
    }

    public void RegisterMember(Member member)
    {
        members[member.GetId()] = member;
        Console.WriteLine($"New member registered: {member.GetName()}");
    }

    public Member GetMember(string name)
    {
        return members.Values.FirstOrDefault(m => m.GetName() == name);
    }

    public string SendConnectionRequest(Member from, Member to)
    {
        return connectionService.SendRequest(from, to);
    }

    public void AcceptConnectionRequest(string requestId)
    {
        connectionService.AcceptRequest(requestId);
    }

    public void CreatePost(string memberId, string content)
    {
        var author = members[memberId];
        var post = new Post(author, content);
        newsFeedService.AddPost(author, post);
        Console.WriteLine($"{author.GetName()} created a new post.");
    }

    public Post GetLatestPostByMember(string memberId)
    {
        var memberPosts = newsFeedService.GetMemberPosts(members[memberId]);
        return memberPosts.LastOrDefault();
    }

    public void ViewNewsFeed(string memberId)
    {
        var member = members[memberId];
        Console.WriteLine($"\n--- News Feed for {member.GetName()} ---");
        newsFeedService.DisplayFeedForMember(member, new ChronologicalSortStrategy());
    }

    public List<Member> SearchMemberByName(string name)
    {
        return searchService.SearchByName(name);
    }
}