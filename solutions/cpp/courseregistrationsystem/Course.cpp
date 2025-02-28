#include "Course.hpp"
#include <iostream>
#include <algorithm>

Course::Course(std::string courseId, std::string name, int maxCapacity)
    : courseId(courseId), name(name), maxCapacity(maxCapacity), available(true) {}

std::string Course::getCourseId() const { return courseId; }
std::string Course::getName() const { return name; }
int Course::getMaxCapacity() const { return maxCapacity; }
int Course::getCurrentEnrollment() const { return enrolledStudents.size(); }
bool Course::isAvailable() const { return available; }

bool Course::enrollStudent(Student* student) {
    if (!available || getCurrentEnrollment() >= maxCapacity) return false;
    if (hasStudent(student)) return false;
    
    enrolledStudents.push_back(student);
    return true;
}

bool Course::dropStudent(Student* student) {
    auto it = std::find(enrolledStudents.begin(), enrolledStudents.end(), student);
    if (it == enrolledStudents.end()) return false;
    
    enrolledStudents.erase(it);
    return true;
}

bool Course::hasStudent(Student* student) const {
    return std::find(enrolledStudents.begin(), enrolledStudents.end(), student) 
           != enrolledStudents.end();
}

void Course::displayInfo() const {
    std::cout << "Course: " << name << " (ID: " << courseId << ")" << std::endl;
    std::cout << "Enrollment: " << getCurrentEnrollment() << "/" << maxCapacity << std::endl;
    std::cout << "Status: " << (available ? "Available" : "Closed") << std::endl;
}

void Course::setAvailable(bool status) {
    available = status;
} 