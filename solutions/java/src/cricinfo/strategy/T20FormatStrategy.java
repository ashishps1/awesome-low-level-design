package cricinfo.strategy;

public class T20FormatStrategy implements MatchFormatStrategy {
    @Override
    public int getTotalInnings() { return 2; }

    @Override
    public int getTotalOvers() { return 20; }

    @Override
    public String getFormatName() { return "T20"; }
}
