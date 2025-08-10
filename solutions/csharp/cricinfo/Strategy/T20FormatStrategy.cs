class T20FormatStrategy : IMatchFormatStrategy
{
    public int GetTotalInnings() => 2;
    public int GetTotalOvers() => 20;
    public string GetFormatName() => "T20";
}