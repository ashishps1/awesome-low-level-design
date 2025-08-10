using System.Collections.Concurrent;

class AuctionService
{
    private static AuctionService instance;
    private static readonly object lockObject = new object();
    private readonly ConcurrentDictionary<string, User> users;
    private readonly ConcurrentDictionary<string, Auction> auctions;
    private readonly List<Task> scheduledTasks;
    private bool shutdown;

    private AuctionService()
    {
        users = new ConcurrentDictionary<string, User>();
        auctions = new ConcurrentDictionary<string, Auction>();
        scheduledTasks = new List<Task>();
        shutdown = false;
    }

    public static AuctionService GetInstance()
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                {
                    instance = new AuctionService();
                }
            }
        }
        return instance;
    }

    public User CreateUser(string name)
    {
        User user = new User(name);
        users.TryAdd(user.GetId(), user);
        return user;
    }

    public User GetUser(string userId)
    {
        users.TryGetValue(userId, out User user);
        return user;
    }

    public Auction CreateAuction(string itemName, string description, decimal startingPrice, DateTime endTime)
    {
        Auction auction = new Auction(itemName, description, startingPrice, endTime);
        auctions.TryAdd(auction.GetId(), auction);

        TimeSpan delay = endTime - DateTime.Now;
        if (delay.TotalMilliseconds > 0)
        {
            Task scheduledTask = Task.Run(async () =>
            {
                await Task.Delay(delay);
                if (!shutdown)
                {
                    EndAuction(auction.GetId());
                }
            });
            scheduledTasks.Add(scheduledTask);
        }

        Console.WriteLine($"New auction created for '{itemName}' (ID: {auction.GetId()}), ending at {endTime}.");
        return auction;
    }

    public List<Auction> ViewActiveAuctions()
    {
        return auctions.Values.Where(auction => auction.IsActive()).ToList();
    }

    public void PlaceBid(string auctionId, string bidderId, decimal amount)
    {
        Auction auction = GetAuction(auctionId);
        auction.PlaceBid(users[bidderId], amount);
    }

    public void EndAuction(string auctionId)
    {
        Auction auction = GetAuction(auctionId);
        auction.EndAuction();
    }

    public Auction GetAuction(string auctionId)
    {
        if (!auctions.TryGetValue(auctionId, out Auction auction))
        {
            throw new KeyNotFoundException($"Auction with ID {auctionId} not found.");
        }
        return auction;
    }

    public void Shutdown()
    {
        shutdown = true;
        Task.WaitAll(scheduledTasks.ToArray());
    }
}