package cricinfo.strategy;

public interface MatchFormatStrategy {
    int getTotalInnings();
    int getTotalOvers();
    String getFormatName();
}
