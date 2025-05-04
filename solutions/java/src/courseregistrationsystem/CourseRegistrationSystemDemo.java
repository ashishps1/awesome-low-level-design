package courseregistrationsystem;

import java.util.List;

public class CourseRegistrationSystemDemo {
    public static void run() {
        CourseRegistrationSystem courseRegistrationSystem = CourseRegistrationSystem.getInstance();

        // Add courses
        Course course1 = courseRegistrationSystem.addCourse("CS101", "Introduction to Programming", "John Doe", 50);
        Course course2 = courseRegistrationSystem.addCourse("CS201", "Data Structures and Algorithms", "John Smith", 30);


        // Create students
        Student student1 = courseRegistrationSystem.registerStudent("Alice", "alice@example.com");
        Student student2 = courseRegistrationSystem.registerStudent( "Bob", "bob@example.com");

        // Search for courses
        List<Course> searchResults = courseRegistrationSystem.searchCourses("CS");
        System.out.println("Search Results:");
        for (Course course : searchResults) {
            System.out.println(course.getCode() + " - " + course.getName());
        }

        try {
            // Register courses for students
            courseRegistrationSystem.enroll(student1.getId(), course1.getCode());
            courseRegistrationSystem.enroll(student2.getId(), course1.getCode());
            courseRegistrationSystem.enroll(student1.getId(), course2.getCode());
        } catch (Exception e) {
            System.out.println("Enrollment failed: " + e.getMessage());
        }

        courseRegistrationSystem.getAvailableCourses().forEach(c ->
                System.out.println("Available: " + c.getName()));
    }
}
