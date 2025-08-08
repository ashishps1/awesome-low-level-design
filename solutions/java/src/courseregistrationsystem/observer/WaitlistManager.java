package courseregistrationsystem.observer;

import courseregistrationsystem.CourseRegistrationService;
import courseregistrationsystem.chain.RegistrationRequest;
import courseregistrationsystem.exception.RegistrationException;
import courseregistrationsystem.model.CourseOffering;

public class WaitlistManager implements CourseOfferingObserver {
    private static final WaitlistManager INSTANCE = new WaitlistManager();
    private final CourseRegistrationService courseRegistrationService = new CourseRegistrationService(); // To re-register a waitlisted student
    public static WaitlistManager getInstance() { return INSTANCE; }
    private WaitlistManager() {}

    @Override
    public void onSpotAvailable(CourseOffering offering) {
        System.out.println("OBSERVER (WaitlistManager): Spot available in " + offering.getCourse().getCourseCode() + ". Processing waitlist.");
        offering.getNextFromWaitlist().ifPresent(student -> {
            System.out.println("Promoting " + student.getName() + " from waitlist for " + offering.getCourse().getCourseCode());
            try {
                // We can re-use the registration service, but a real system might have a simplified "promote" logic
                courseRegistrationService.register(new RegistrationRequest(student, offering));
            } catch (RegistrationException e) {
                System.err.println("Failed to promote " + student.getName() + ": " + e.getMessage());
                // Handle failure: try next student or notify admin
            }
        });
    }
}
