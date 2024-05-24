package courseregistrationsystem;

import java.sql.Timestamp;

public class Registration {
    private final Student student;
    private final Course course;
    private final Timestamp registrationTime;

    public Registration(Student student, Course course, Timestamp registrationTime) {
        this.student = student;
        this.course = course;
        this.registrationTime = registrationTime;
    }
}
