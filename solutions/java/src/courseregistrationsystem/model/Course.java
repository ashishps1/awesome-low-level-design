package courseregistrationsystem.model;

import java.util.HashSet;
import java.util.Set;

public class Course {
    private final String courseCode;
    private final String title;
    private final Set<Course> prerequisites = new HashSet<>();

    public Course(String courseCode, String title) { this.courseCode = courseCode; this.title = title; }

    public void addPrerequisite(Course course) { prerequisites.add(course); }
    public String getCourseCode() { return courseCode; }
    public Set<Course> getPrerequisites() { return prerequisites; }
}
