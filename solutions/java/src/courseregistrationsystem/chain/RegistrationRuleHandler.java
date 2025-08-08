package courseregistrationsystem.chain;

import courseregistrationsystem.exception.RegistrationException;

public abstract class RegistrationRuleHandler {
    private RegistrationRuleHandler next;

    public void setNext(RegistrationRuleHandler next) { this.next = next; }

    public abstract void handle(RegistrationRequest request) throws RegistrationException;

    protected void handleNext(RegistrationRequest request) throws RegistrationException {
        if (next != null) {
            next.handle(request);
        }
    }
}
