package courseregistrationsystem;

import courseregistrationsystem.chain.*;
import courseregistrationsystem.exception.RegistrationException;

public class CourseRegistrationService {
    private final RegistrationRuleHandler registrationChain;
    public CourseRegistrationService() {
        // Build the chain of responsibility
        RegistrationRuleHandler capacityHandler = new CapacityRuleHandler();
        RegistrationRuleHandler conflictHandler = new ScheduleConflictRuleHandler();
        conflictHandler.setNext(capacityHandler);
        RegistrationRuleHandler prereqHandler = new PrerequisiteRuleHandler();
        prereqHandler.setNext(conflictHandler);
        this.registrationChain = prereqHandler;
    }
    public void register(RegistrationRequest request) throws RegistrationException {
        registrationChain.handle(request);
    }
}
