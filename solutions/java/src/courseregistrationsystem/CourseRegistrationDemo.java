package courseregistrationsystem;

import java.util.ArrayList;
import java.util.List;

public class CourseRegistrationDemo {
    public static void run() {
        CourseRegistrationSystem registrationSystem = CourseRegistrationSystem.getInstance();

        // Create courses
        Course course1 = new Course("CS101", "Introduction to Programming", "John Doe", 50, 0);
        Course course2 = new Course("CS201", "Data Structures and Algorithms", "Jane Smith", 30, 0);
        registrationSystem.addCourse(course1);
        registrationSystem.addCourse(course2);

        // Create students
        Student student1 = new Student(1, "Alice", "alice@example.com", new ArrayList<>());
        Student student2 = new Student(2, "Bob", "bob@example.com", new ArrayList<>());
        registrationSystem.addStudent(student1);
        registrationSystem.addStudent(student2);

        // Search for courses
        List<Course> searchResults = registrationSystem.searchCourses("CS");
        System.out.println("Search Results:");
        for (Course course : searchResults) {
            System.out.println(course.getCode() + " - " + course.getName());
        }

        // Register courses for students
        boolean registered1 = registrationSystem.registerCourse(student1, course1);
        boolean registered2 = registrationSystem.registerCourse(student2, course1);
        boolean registered3 = registrationSystem.registerCourse(student1, course2);

        System.out.println("Registration Results:");
        System.out.println("Student 1 - Course 1: " + registered1);
        System.out.println("Student 2 - Course 1: " + registered2);
        System.out.println("Student 1 - Course 2: " + registered3);

        // Get registered courses for a student
        List<Course> registeredCourses = registrationSystem.getRegisteredCourses(student1);
        System.out.println("Registered Courses for Student 1:");
        for (Course course : registeredCourses) {
            System.out.println(course.getCode() + " - " + course.getName());
        }
    }
}
