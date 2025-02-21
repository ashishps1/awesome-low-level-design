#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <vector>

class Course;  // Forward declaration

class Student {
private:
    std::string studentId;
    std::string name;
    std::vector<Course*> enrolledCourses;

public:
    Student(std::string studentId, std::string name);
    
    std::string getStudentId() const;
    std::string getName() const;
    const std::vector<Course*>& getEnrolledCourses() const;
    
    bool enrollInCourse(Course* course);
    bool dropCourse(Course* course);
    bool isEnrolledIn(Course* course) const;
    void displayInfo() const;
};

#endif 