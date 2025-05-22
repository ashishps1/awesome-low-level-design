public class ProgressLoggerNaive {
    public void logDataPoint(int steps, int activeMinutes, int calories) {
        System.out.println("NAIVE Logger: Saving data - Steps: " + steps +
                           ", Active Mins: " + activeMinutes +
                           ", Calories: " + calories);
        // ... actual database/file logging logic ...
    }    
}
