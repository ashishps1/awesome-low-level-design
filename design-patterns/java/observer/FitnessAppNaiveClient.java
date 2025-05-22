public class FitnessAppNaiveClient {
    public static void main(String[] args) {
        LiveActivityDisplayNaive display = new LiveActivityDisplayNaive();
        ProgressLoggerNaive logger = new ProgressLoggerNaive();
        NotificationServiceNaive notifier = new NotificationServiceNaive();

        FitnessDataNaive fitnessData = new FitnessDataNaive(display, logger, notifier);

        fitnessData.newFitnessDataPushed(500, 5, 20);
        fitnessData.newFitnessDataPushed(9800, 85, 350);
        fitnessData.newFitnessDataPushed(10100, 90, 380); // Goal should be hit
        fitnessData.dailyReset();
    }    
}
