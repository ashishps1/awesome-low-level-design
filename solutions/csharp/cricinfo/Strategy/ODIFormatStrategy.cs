class ODIFormatStrategy : IMatchFormatStrategy
{
    public int GetTotalInnings() => 2;
    public int GetTotalOvers() => 50;
    public string GetFormatName() => "ODI";
}