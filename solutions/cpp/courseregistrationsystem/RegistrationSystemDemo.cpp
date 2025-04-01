#include "RegistrationSystem.hpp"
#include <iostream>

int main() {
    RegistrationSystem system;
    
    // Create courses
    Course* course1 = new Course("CS101", "Introduction to Programming", 3);
    Course* course2 = new Course("CS102", "Data Structures", 2);
    Course* course3 = new Course("CS103", "Algorithms", 2);
    
    system.addCourse(course1);
    system.addCourse(course2);
    system.addCourse(course3);
    
    // Create students
    Student* student1 = new Student("S001", "John Doe");
    Student* student2 = new Student("S002", "Jane Smith");
    Student* student3 = new Student("S003", "Bob Johnson");
    
    system.addStudent(student1);
    system.addStudent(student2);
    system.addStudent(student3);
    
    // Display initial state
    system.displayAllCourses();
    system.displayAllStudents();
    
    // Enroll students in courses
    if (system.enrollStudentInCourse(student1, course1)) {
        std::cout << "Enrolled " << student1->getName() << " in " << course1->getName() << std::endl;
    }
    
    if (system.enrollStudentInCourse(student2, course1)) {
        std::cout << "Enrolled " << student2->getName() << " in " << course1->getName() << std::endl;
    }
    
    if (system.enrollStudentInCourse(student1, course2)) {
        std::cout << "Enrolled " << student1->getName() << " in " << course2->getName() << std::endl;
    }
    
    // Display enrollments
    system.displayCourseEnrollments(course1);
    system.displayStudentEnrollments(student1);
    
    // Drop a course
    if (system.dropStudentFromCourse(student1, course1)) {
        std::cout << "\nDropped " << student1->getName() << " from " << course1->getName() << std::endl;
    }
    
    // Display final state
    system.displayCourseEnrollments(course1);
    system.displayStudentEnrollments(student1);
    
    return 0;
} 