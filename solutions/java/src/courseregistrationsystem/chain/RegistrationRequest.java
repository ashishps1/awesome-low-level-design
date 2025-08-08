package courseregistrationsystem.chain;

import courseregistrationsystem.model.CourseOffering;
import courseregistrationsystem.model.Student;

public record RegistrationRequest(Student student, CourseOffering offering) {}
