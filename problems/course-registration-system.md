# Designing a University Course Registration System

In this article, we explore the object-oriented design and implementation of a University Course Registration System using Java. 

The system facilitates course registration and management for students and universities.

## System Requirements

The University Course Registration System should:

1. **Student Management**: Handle student profiles and academic records.
2. **Course Management**: Manage course details, schedules, and capacities.
3. **Registration Process**: Enable students to register for courses.
4. **Prerequisite Checking**: Ensure students meet course prerequisites.
5. **Enrollment Verification**: Confirm student enrollments in courses.

## Core Use Cases

1. **Registering and Managing Student Profiles**
2. **Adding and Updating Courses**
3. **Enrolling in Courses**
4. **Checking Prerequisites**
5. **Verifying Course Enrollment**

## UML/Class Diagrams

Key Classes:

- `CourseRegistrationSystem`: Manages the system.
- `Student`: Represents a student.
- `Course`: Represents a university course.
- `Enrollment`: Manages student enrollments.

## Java Implementation

### Student Class

Manages student information and enrollment records.

```java
import java.util.HashSet;
import java.util.Set;

public class Student {
    private String studentId;
    private String name;
    private Set<String> completedCourses;
    private Set<Enrollment> enrollments;

    public Student(String studentId, String name) {
        this.studentId = studentId;
        this.name = name;
        this.completedCourses = new HashSet<>();
        this.enrollments = new HashSet<>();
    }

    public void enrollInCourse(Course course) {
        if (course.checkPrerequisites(completedCourses)) {
            Enrollment newEnrollment = new Enrollment(this, course);
            enrollments.add(newEnrollment);
            course.addStudent(this);
            return true;
        }
        return false;
    }

    public void addCompletedCourse(String courseId) {
        completedCourses.add(courseId);
    }    

    // Getters and setters...
}
```
### Course Class
Represents a university course.
```java
import java.util.HashSet;
import java.util.Set;

public class Course {
    private String courseId;
    private String title;
    private int capacity;
    private Set<String> prerequisites;
    private Set<Student> studentsEnrolled;

    public Course(String courseId, String title, int capacity) {
        this.courseId = courseId;
        this.title = title;
        this.capacity = capacity;
        this.prerequisites = new HashSet<>();
        this.studentsEnrolled = new HashSet<>();
    }

    public boolean addStudent(Student student) {
        if (studentsEnrolled.size() < capacity) {
            studentsEnrolled.add(student);
            return true;
        }
        return false;
    }

    public void addPrerequisite(String prerequisiteCourseId) {
        prerequisites.add(prerequisiteCourseId);
    }

    public boolean checkPrerequisites(Set<String> completedCourses) {
        return completedCourses.containsAll(prerequisites);
    }
    // Getters and setters...
}
```
### Enrollment Class
Manages a student's enrollment in a course.
```java
public class Enrollment {
    private Student student;
    private Course course;

    public Enrollment(Student student, Course course) {
        this.student = student;
        this.course = course;
    }

    // Getters and setters...
}
```
### CourseRegistrationSystem Class
Manages the course registration system operations.
```java
import java.util.ArrayList;
import java.util.List;

public class CourseRegistrationSystem {
    private List<Student> students;
    private List<Course> courses;

    public CourseRegistrationSystem() {
        this.students = new ArrayList<>();
        this.courses = new ArrayList<>();
    }

    public void addStudent(Student student) {
        students.add(student);
    }
    
    public void addCourse(Course course) {
        courses.add(course);
    }

    public boolean registerStudentForCourse(String studentId, String courseId) {
        Student student = findStudentById(studentId);
        Course course = findCourseById(courseId);

        if (student != null && course != null) {
            return student.enrollInCourse(course);
        }
        return false;
    }

    // Other necessary methods...
}
```
