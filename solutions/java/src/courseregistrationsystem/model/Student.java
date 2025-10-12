package courseregistrationsystem.model;

import java.util.HashSet;
import java.util.Set;

public class Student {
    private final String id;
    private final String name;
    private final Set<Course> completedCourses = new HashSet<>();
    private final Set<CourseOffering> registeredOfferings = new HashSet<>();

    public Student(String id, String name) { this.id = id; this.name = name; }

    public String getId() { return id; }
    public String getName() { return name; }
    public Set<Course> getCompletedCourses() { return completedCourses; }
    public Set<CourseOffering> getRegisteredOfferings() { return registeredOfferings; }
    public void addCompletedCourse(Course course) { completedCourses.add(course); }
    public void enroll(CourseOffering offering) { registeredOfferings.add(offering); }
    public void drop(CourseOffering offering) { registeredOfferings.remove(offering); }
}
