class Member : INotificationObserver
{
    private readonly string id;
    private readonly string name;
    private readonly string email;
    private readonly Profile profile;
    private readonly HashSet<Member> connections = new HashSet<Member>();
    private readonly List<Notification> notifications = new List<Notification>();

    public Member(string id, string name, string email, Profile profile)
    {
        this.id = id;
        this.name = name;
        this.email = email;
        this.profile = profile;
    }

    public string GetId() { return id; }
    public string GetName() { return name; }
    public string GetEmail() { return email; }
    public HashSet<Member> GetConnections() { return connections; }
    public Profile GetProfile() { return profile; }

    public void AddConnection(Member member)
    {
        connections.Add(member);
    }

    public void DisplayProfile()
    {
        Console.WriteLine($"\n--- Profile for {name} ({email}) ---");
        profile.Display();
        Console.WriteLine($"  Connections: {connections.Count}");
    }

    public void ViewNotifications()
    {
        Console.WriteLine($"\n--- Notifications for {name} ---");
        var unreadNotifications = notifications.Where(n => !n.IsRead()).ToList();

        if (!unreadNotifications.Any())
        {
            Console.WriteLine("  No new notifications.");
            return;
        }

        foreach (var notification in unreadNotifications)
        {
            Console.WriteLine($"  - {notification.GetContent()}");
            notification.MarkAsRead();
        }
    }

    public void Update(Notification notification)
    {
        notifications.Add(notification);
        Console.WriteLine($"Notification pushed to {name}: {notification.GetContent()}");
    }
}

class MemberBuilder
{
    private readonly string id;
    private readonly string name;
    private readonly string email;
    private readonly Profile profile = new Profile();

    public MemberBuilder(string name, string email)
    {
        this.id = Guid.NewGuid().ToString();
        this.name = name;
        this.email = email;
    }

    public MemberBuilder WithSummary(string summary)
    {
        profile.SetSummary(summary);
        return this;
    }

    public MemberBuilder AddExperience(Experience experience)
    {
        profile.AddExperience(experience);
        return this;
    }

    public MemberBuilder AddEducation(Education education)
    {
        profile.AddEducation(education);
        return this;
    }

    public Member Build()
    {
        return new Member(id, name, email, profile);
    }
}