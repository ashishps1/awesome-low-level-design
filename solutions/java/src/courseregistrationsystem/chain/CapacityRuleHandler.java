package courseregistrationsystem.chain;

import courseregistrationsystem.exception.RegistrationException;

public class CapacityRuleHandler extends RegistrationRuleHandler {
    @Override
    public void handle(RegistrationRequest request) throws RegistrationException {
        if (request.offering().isFull()) {
            request.offering().addToWaitlist(request.student());
            System.out.println("Course " + request.offering().getCourse().getCourseCode() + " is full. " + request.student().getName() + " added to waitlist.");
        } else {
            request.offering().addStudent(request.student());
            System.out.println(request.student().getName() + " successfully registered for " + request.offering().getCourse().getCourseCode());
        }
        handleNext(request);
    }
}
