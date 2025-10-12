package courseregistrationsystem.chain;

import courseregistrationsystem.exception.RegistrationException;

public class ScheduleConflictRuleHandler extends RegistrationRuleHandler {
    @Override
    public void handle(RegistrationRequest request) throws RegistrationException {
        boolean conflict = request.student().getRegisteredOfferings().stream()
                .anyMatch(offering -> offering.getTimeSlot().overlaps(request.offering().getTimeSlot()));
        if (conflict) {
            throw new RegistrationException("Schedule conflict detected for course " + request.offering().getCourse().getCourseCode());
        }
        handleNext(request);
    }
}
