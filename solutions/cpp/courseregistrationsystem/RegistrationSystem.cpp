#include "RegistrationSystem.hpp"
#include <iostream>

RegistrationSystem::RegistrationSystem() {}

RegistrationSystem::~RegistrationSystem() {
    for (auto course : courses) delete course;
    for (auto student : students) delete student;
}

void RegistrationSystem::addCourse(Course* course) {
    courses.push_back(course);
}

void RegistrationSystem::addStudent(Student* student) {
    students.push_back(student);
}

bool RegistrationSystem::enrollStudentInCourse(Student* student, Course* course) {
    if (!student || !course) return false;
    return student->enrollInCourse(course);
}

bool RegistrationSystem::dropStudentFromCourse(Student* student, Course* course) {
    if (!student || !course) return false;
    return student->dropCourse(course);
}

void RegistrationSystem::displayAllCourses() const {
    std::cout << "\nAll Courses:" << std::endl;
    for (const auto& course : courses) {
        course->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void RegistrationSystem::displayAllStudents() const {
    std::cout << "\nAll Students:" << std::endl;
    for (const auto& student : students) {
        student->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void RegistrationSystem::displayCourseEnrollments(Course* course) const {
    if (!course) return;
    
    std::cout << "\nEnrollments for " << course->getName() << ":" << std::endl;
    for (const auto& student : students) {
        if (student->isEnrolledIn(course)) {
            std::cout << "- " << student->getName() << " (ID: " << student->getStudentId() << ")" << std::endl;
        }
    }
}

void RegistrationSystem::displayStudentEnrollments(Student* student) const {
    if (!student) return;
    student->displayInfo();
}

Course* RegistrationSystem::findCourse(std::string courseId) const {
    for (auto course : courses) {
        if (course->getCourseId() == courseId) return course;
    }
    return nullptr;
}

Student* RegistrationSystem::findStudent(std::string studentId) const {
    for (auto student : students) {
        if (student->getStudentId() == studentId) return student;
    }
    return nullptr;
} 