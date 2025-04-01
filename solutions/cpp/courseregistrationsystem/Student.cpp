#include "Student.hpp"
#include "Course.hpp"
#include <iostream>
#include <algorithm>

Student::Student(std::string studentId, std::string name)
    : studentId(studentId), name(name) {}

std::string Student::getStudentId() const { return studentId; }
std::string Student::getName() const { return name; }
const std::vector<Course*>& Student::getEnrolledCourses() const { return enrolledCourses; }

bool Student::enrollInCourse(Course* course) {
    if (isEnrolledIn(course)) return false;
    if (!course->enrollStudent(this)) return false;
    
    enrolledCourses.push_back(course);
    return true;
}

bool Student::dropCourse(Course* course) {
    auto it = std::find(enrolledCourses.begin(), enrolledCourses.end(), course);
    if (it == enrolledCourses.end()) return false;
    
    if (!course->dropStudent(this)) return false;
    enrolledCourses.erase(it);
    return true;
}

bool Student::isEnrolledIn(Course* course) const {
    return std::find(enrolledCourses.begin(), enrolledCourses.end(), course) 
           != enrolledCourses.end();
}

void Student::displayInfo() const {
    std::cout << "Student: " << name << " (ID: " << studentId << ")" << std::endl;
    std::cout << "Enrolled Courses:" << std::endl;
    for (const auto& course : enrolledCourses) {
        std::cout << "- " << course->getName() << " (ID: " << course->getCourseId() << ")" << std::endl;
    }
} 