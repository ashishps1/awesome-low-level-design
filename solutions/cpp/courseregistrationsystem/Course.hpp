#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>
#include <vector>
#include "Student.hpp"

class Course {
private:
    std::string courseId;
    std::string name;
    int maxCapacity;
    std::vector<Student*> enrolledStudents;
    bool available;

public:
    Course(std::string courseId, std::string name, int maxCapacity);
    
    std::string getCourseId() const;
    std::string getName() const;
    int getMaxCapacity() const;
    int getCurrentEnrollment() const;
    bool isAvailable() const;
    
    bool enrollStudent(Student* student);
    bool dropStudent(Student* student);
    bool hasStudent(Student* student) const;
    void displayInfo() const;
    void setAvailable(bool status);
};

#endif 