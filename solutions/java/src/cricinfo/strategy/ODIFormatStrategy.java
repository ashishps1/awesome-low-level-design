package cricinfo.strategy;

public class ODIFormatStrategy implements MatchFormatStrategy {
    @Override
    public int getTotalInnings() { return 2; }

    @Override
    public int getTotalOvers() { return 50; }

    @Override
    public String getFormatName() { return "ODI"; }
}