package courseregistrationsystem;

import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;

public class CourseRegistrationSystem {
    private static CourseRegistrationSystem instance;
    private final Map<String, Course> courses;
    private final Map<Integer, Student> students;
    private final List<Registration> registrations;

    private CourseRegistrationSystem() {
        courses = new ConcurrentHashMap<>();
        students = new ConcurrentHashMap<>();
        registrations = new CopyOnWriteArrayList<>();
    }

    public static synchronized CourseRegistrationSystem getInstance() {
        if (instance == null) {
            instance = new CourseRegistrationSystem();
        }
        return instance;
    }

    public void addCourse(Course course) {
        courses.put(course.getCode(), course);
    }

    public void addStudent(Student student) {
        students.put(student.getId(), student);
    }

    public List<Course> searchCourses(String query) {
        List<Course> result = new ArrayList<>();
        for (Course course : courses.values()) {
            if (course.getCode().contains(query) || course.getName().contains(query)) {
                result.add(course);
            }
        }
        return result;
    }

    public synchronized boolean registerCourse(Student student, Course course) {
        if (course.getEnrolledStudents() < course.getMaxCapacity()) {
            Registration registration = new Registration(student, course, new Timestamp(System.currentTimeMillis()));
            registrations.add(registration);
            student.getRegisteredCourses().add(course);
            course.setEnrolledStudents(course.getEnrolledStudents() + 1);
            notifyObservers(course);
            return true;
        }
        return false;
    }

    public List<Course> getRegisteredCourses(Student student) {
        return student.getRegisteredCourses();
    }

    private void notifyObservers(Course course) {
        // Notify observers (e.g., UI) about the updated course enrollment
        // ...
    }
}
