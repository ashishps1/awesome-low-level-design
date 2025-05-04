package courseregistrationsystem;

import java.util.HashSet;
import java.util.Set;

public class Course {
    private final String code;
    private final String name;
    private final String instructor;
    private final int maxCapacity;
    private final Set<Student> enrolledStudents;

    public Course(String code, String name, String instructor, int maxCapacity) {
        this.code = code;
        this.name = name;
        this.instructor = instructor;
        this.maxCapacity = maxCapacity;
        this.enrolledStudents = new HashSet<>();
    }

    public synchronized void enroll(Student student) {
        if (enrolledStudents.size() >= maxCapacity) {
            throw new IllegalStateException("Course is full");
        }
        enrolledStudents.add(student);
    }

    public synchronized void drop(Student student) {
        enrolledStudents.remove(student);
    }

    public boolean isCourseAvailable() {
        return enrolledStudents.size() < maxCapacity;
    }

    public String getCode() {
        return code;
    }

    public String getName() {
        return name;
    }

    public String getInstructor() {
        return instructor;
    }

    public int getMaxCapacity() {
        return maxCapacity;
    }

    public Set<Student> getEnrolledStudents() {
        return enrolledStudents;
    }
}
