#ifndef REGISTRATION_SYSTEM_HPP
#define REGISTRATION_SYSTEM_HPP

#include <vector>
#include <string>
#include "Course.hpp"
#include "Student.hpp"

class RegistrationSystem {
private:
    std::vector<Course*> courses;
    std::vector<Student*> students;

public:
    RegistrationSystem();
    ~RegistrationSystem();
    
    void addCourse(Course* course);
    void addStudent(Student* student);
    bool enrollStudentInCourse(Student* student, Course* course);
    bool dropStudentFromCourse(Student* student, Course* course);
    
    void displayAllCourses() const;
    void displayAllStudents() const;
    void displayCourseEnrollments(Course* course) const;
    void displayStudentEnrollments(Student* student) const;
    
    Course* findCourse(std::string courseId) const;
    Student* findStudent(std::string studentId) const;
};

#endif 