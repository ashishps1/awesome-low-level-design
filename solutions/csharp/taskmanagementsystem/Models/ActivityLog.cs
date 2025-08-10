class ActivityLog
{
    private readonly string description;
    private readonly DateTime timestamp;

    public ActivityLog(string description)
    {
        this.description = description;
        this.timestamp = DateTime.Now;
    }

    public override string ToString()
    {
        return $"[{timestamp}] {description}";
    }
}