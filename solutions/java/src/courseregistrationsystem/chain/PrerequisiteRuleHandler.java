package courseregistrationsystem.chain;

import courseregistrationsystem.exception.RegistrationException;
import courseregistrationsystem.model.Course;

import java.util.Set;

public class PrerequisiteRuleHandler extends RegistrationRuleHandler {
    @Override
    public void handle(RegistrationRequest request) throws RegistrationException {
        Set<Course> completed = request.student().getCompletedCourses();
        Set<Course> prereqs = request.offering().getCourse().getPrerequisites();
        if (!completed.containsAll(prereqs)) {
            throw new RegistrationException("Prerequisite not met for course " + request.offering().getCourse().getCourseCode());
        }
        handleNext(request);
    }
}
