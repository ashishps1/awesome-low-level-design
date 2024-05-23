package courseregistrationsystem;

public class Course {
    private String code;
    private String name;
    private String instructor;
    private int maxCapacity;
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
