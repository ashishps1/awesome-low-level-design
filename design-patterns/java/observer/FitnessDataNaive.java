public class FitnessDataNaive {
    private int steps;
    private int activeMinutes;
    private int calories;

    // Direct, hardcoded references to all dependent modules!
    private LiveActivityDisplayNaive liveDisplay;
    private ProgressLoggerNaive progressLogger;
    private NotificationServiceNaive notificationService;

    public FitnessDataNaive(LiveActivityDisplayNaive ld, ProgressLoggerNaive pl, NotificationServiceNaive ns) {
        this.liveDisplay = ld;
        this.progressLogger = pl;
        this.notificationService = ns;
    }

    // This method gets called when new data arrives from the wearable
    public void newFitnessDataPushed(int newSteps, int newActiveMinutes, int newCalories) {
        this.steps = newSteps;
        this.activeMinutes = newActiveMinutes;
        this.calories = newCalories;

        System.out.println("\nFitnessDataNaive: New data received - Steps:" + steps +
                           ", ActiveMins:" + activeMinutes + ", Calories:" + calories);

        // Manually notify each dependent module
        liveDisplay.showStats(steps, activeMinutes, calories);
        progressLogger.logDataPoint(steps, activeMinutes, calories);
        notificationService.checkAndNotify(steps);
    }

    public void dailyReset() {
        // ... reset steps, etc. ...
        notificationService.resetDailyNotifications();
        System.out.println("FitnessDataNaive: Daily data reset.");
        newFitnessDataPushed(0,0,0); // Notify of reset state
    }    
}
