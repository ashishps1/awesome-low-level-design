public class NotificationServiceNaive {
    private int stepGoal = 10000;
    private boolean dailyStepGoalNotified = false;

    public void checkAndNotify(int currentSteps) {
        if (currentSteps >= stepGoal && !dailyStepGoalNotified) {
            System.out.println("NAIVE Notifier: ALERT! You've reached your " + stepGoal + " step goal!");
            dailyStepGoalNotified = true;
        }
        // ... other notification logic, e.g., inactivity alerts ...
    }
    public void resetDailyNotifications() {
        dailyStepGoalNotified = false;
    }    
}
