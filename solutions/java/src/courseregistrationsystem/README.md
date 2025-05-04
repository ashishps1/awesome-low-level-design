# Course Registration System (LLD)

## Problem Statement

Design and implement a Course Registration System that allows students to register for courses, manages course capacity, and tracks student enrollments.

---

## Requirements

- **Student Registration:** Students can register for courses.
- **Course Management:** The system manages courses, each with a unique code, name, and capacity.
- **Capacity Enforcement:** Students cannot register for a course if it is full.
- **Duplicate Prevention:** A student cannot register for the same course more than once.
- **Enrollment Tracking:** The system tracks which students are enrolled in which courses.
- **Extensibility:** Easy to add new features such as course prerequisites, waitlists, or drop functionality.

---

## Core Entities

- **CourseRegistrationSystem:** Main class that manages students, courses, and registrations.
- **Student:** Represents a student with a unique ID and name.
- **Course:** Represents a course with a unique code, name, and capacity.
- **Registration:** Represents a registration record of a student in a course.

---

## Class Design

### 1. CourseRegistrationSystem
- **Fields:** Map<String, Course> courses, Map<Integer, Student> students, List<Registration> registrations
- **Methods:** registerStudent(Student), addCourse(Course), register(int studentId, String courseCode), getStudentCourses(int studentId), getCourseStudents(String courseCode), etc.

### 2. Student
- **Fields:** int id, String name

### 3. Course
- **Fields:** String code, String name, int capacity, List<Student> enrolledStudents
- **Methods:** enrollStudent(Student), isFull(), getEnrolledStudents()

### 4. Registration
- **Fields:** Student student, Course course

---

## Example Usage

```java
CourseRegistrationSystem system = new CourseRegistrationSystem();
system.registerStudent(new Student(1, "Alice"));
system.registerStudent(new Student(2, "Bob"));
system.addCourse(new Course("CS101", "Intro to CS", 2));
system.addCourse(new Course("MATH101", "Calculus I", 1));

system.register(1, "CS101"); // Alice registers for CS101
system.register(2, "CS101"); // Bob registers for CS101
system.register(1, "MATH101"); // Alice registers for MATH101

// List courses for Alice
List<Course> aliceCourses = system.getStudentCourses(1);
// List students in CS101
List<Student> cs101Students = system.getCourseStudents("CS101");
```

---

## Demo

See `CourseRegistrationSystemDemo.java` for a sample usage and simulation of the course registration system.

---

## Extending the Framework

- **Add course prerequisites:** Track and enforce prerequisites for course registration.
- **Add waitlists:** Allow students to join a waitlist if a course is full.
- **Add drop functionality:** Allow students to drop courses.

---