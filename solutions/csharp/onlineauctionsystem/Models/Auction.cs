class Auction
{
    private readonly string id;
    private readonly string itemName;
    private readonly string description;
    private readonly decimal startingPrice;
    private readonly DateTime endTime;
    private readonly List<Bid> bids;
    private readonly HashSet<IAuctionObserver> observers;
    private AuctionState state;
    private Bid winningBid;
    private readonly object lockObject = new object();

    public Auction(string itemName, string description, decimal startingPrice, DateTime endTime)
    {
        this.id = Guid.NewGuid().ToString();
        this.itemName = itemName;
        this.description = description;
        this.startingPrice = startingPrice;
        this.endTime = endTime;
        this.bids = new List<Bid>();
        this.observers = new HashSet<IAuctionObserver>();
        this.state = AuctionState.ACTIVE;
    }

    public void PlaceBid(User bidder, decimal amount)
    {
        lock (lockObject)
        {
            if (state != AuctionState.ACTIVE)
            {
                throw new InvalidOperationException("Auction is not active.");
            }
            if (DateTime.Now > endTime)
            {
                EndAuction();
                throw new InvalidOperationException("Auction has already ended.");
            }

            Bid highestBid = GetHighestBid();
            decimal currentMaxAmount = (highestBid == null) ? startingPrice : highestBid.GetAmount();

            if (amount <= currentMaxAmount)
            {
                throw new ArgumentException("Bid must be higher than the current highest bid.");
            }

            User previousHighestBidder = (highestBid != null) ? highestBid.GetBidder() : null;

            Bid newBid = new Bid(bidder, amount);
            bids.Add(newBid);
            AddObserver(bidder);

            Console.WriteLine($"SUCCESS: {bidder.GetName()} placed a bid of ${amount:F2} on '{itemName}'.");

            if (previousHighestBidder != null && !previousHighestBidder.Equals(bidder))
            {
                NotifyObserver(previousHighestBidder, $"You have been outbid on '{itemName}'! The new highest bid is ${amount:F2}.");
            }
        }
    }

    public void EndAuction()
    {
        lock (lockObject)
        {
            if (state != AuctionState.ACTIVE)
            {
                return;
            }

            state = AuctionState.CLOSED;
            winningBid = GetHighestBid();

            string endMessage;
            if (winningBid != null)
            {
                endMessage = $"Auction for '{itemName}' has ended. Winner is {winningBid.GetBidder().GetName()} with a bid of ${winningBid.GetAmount():F2}!";
            }
            else
            {
                endMessage = $"Auction for '{itemName}' has ended. There were no bids.";
            }

            Console.WriteLine($"\n{endMessage.ToUpper()}");
            NotifyAllObservers(endMessage);
        }
    }

    public Bid GetHighestBid()
    {
        if (bids.Count == 0)
        {
            return null;
        }
        return bids.Max();
    }

    public bool IsActive()
    {
        return state == AuctionState.ACTIVE;
    }

    private void AddObserver(IAuctionObserver observer)
    {
        observers.Add(observer);
    }

    private void NotifyAllObservers(string message)
    {
        foreach (IAuctionObserver observer in observers)
        {
            observer.OnUpdate(this, message);
        }
    }

    private void NotifyObserver(IAuctionObserver observer, string message)
    {
        observer.OnUpdate(this, message);
    }

    public string GetId() { return id; }
    public string GetItemName() { return itemName; }
    public List<Bid> GetBidHistory() { return new List<Bid>(bids); }
    public AuctionState GetState() { return state; }
    public Bid GetWinningBid() { return winningBid; }
}