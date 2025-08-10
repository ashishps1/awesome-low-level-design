class Request
{
    private readonly int targetFloor;
    private readonly Direction direction;
    private readonly RequestSource source;

    public Request(int targetFloor, Direction direction, RequestSource source)
    {
        this.targetFloor = targetFloor;
        this.direction = direction;
        this.source = source;
    }

    public int GetTargetFloor() => targetFloor;
    public Direction GetDirection() => direction;
    public RequestSource GetSource() => source;

    public override string ToString()
    {
        if (source == RequestSource.EXTERNAL)
        {
            return $"{source} Request to floor {targetFloor} going {direction}";
        }
        else
        {
            return $"{source} Request to floor {targetFloor}";
        }
    }
}