class ConnectionService
{
    private readonly NotificationService notificationService;
    private readonly Dictionary<string, Connection> connectionRequests = new Dictionary<string, Connection>();
    private readonly object lockObj = new object();

    public ConnectionService(NotificationService notificationService)
    {
        this.notificationService = notificationService;
    }

    public string SendRequest(Member from, Member to)
    {
        var connection = new Connection(from, to);
        string requestId = Guid.NewGuid().ToString();
        
        lock (lockObj)
        {
            connectionRequests[requestId] = connection;
        }

        Console.WriteLine($"{from.GetName()} sent a connection request to {to.GetName()}.");

        var notification = new Notification(
            to.GetId(),
            NotificationType.CONNECTION_REQUEST,
            $"{from.GetName()} wants to connect with you. Request ID: {requestId}"
        );
        notificationService.SendNotification(to, notification);

        return requestId;
    }

    public void AcceptRequest(string requestId)
    {
        lock (lockObj)
        {
            if (connectionRequests.TryGetValue(requestId, out var request) && 
                request.GetStatus() == ConnectionStatus.PENDING)
            {
                request.SetStatus(ConnectionStatus.ACCEPTED);

                var from = request.GetFromMember();
                var to = request.GetToMember();

                from.AddConnection(to);
                to.AddConnection(from);

                Console.WriteLine($"{to.GetName()} accepted the connection request from {from.GetName()}.");
                connectionRequests.Remove(requestId);
            }
            else
            {
                Console.WriteLine("Invalid or already handled request ID.");
            }
        }
    }
}