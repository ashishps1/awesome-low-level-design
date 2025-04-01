package courseregistrationsystem;

public class Course {
    private final String code;
    private final String name;
    private final String instructor;
    private final int maxCapacity;
    private int enrolledStudents;

    public Course(String code, String name, String instructor, int maxCapacity, int enrolledStudents) {
        this.code = code;
        this.name = name;
        this.instructor = instructor;
        this.maxCapacity = maxCapacity;
        this.enrolledStudents = enrolledStudents;
    }

    public void setEnrolledStudents(int enrolledStudents) {
        this.enrolledStudents = enrolledStudents;
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

    public int getEnrolledStudents() {
        return enrolledStudents;
    }
}
