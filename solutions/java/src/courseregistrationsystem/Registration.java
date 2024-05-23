package courseregistrationsystem;

import java.sql.Timestamp;

public class Registration {
    private Student student;
    private Course course;
    private Timestamp registrationTime;

    public Registration(Student student, Course course, Timestamp registrationTime) {
        this.student = student;
        this.course = course;
        this.registrationTime = registrationTime;
    }
}
