// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Student;
class Course;
class RegistrationSystem;

// ===== Student.hpp =====
class Course;  // Forward declaration

class Student {
private:
    string studentId;
    string name;
    vector<Course*> enrolledCourses;

public:
    Student(string studentId, string name);
    
    string getStudentId() const;
    string getName() const;
    const vector<Course*>& getEnrolledCourses() const;
    
    bool enrollInCourse(Course* course);
    bool dropCourse(Course* course);
    bool isEnrolledIn(Course* course) const;
    void displayInfo() const;
};

// ===== Course.hpp =====
class Course {
private:
    string courseId;
    string name;
    int maxCapacity;
    vector<Student*> enrolledStudents;
    bool available;

public:
    Course(string courseId, string name, int maxCapacity);
    
    string getCourseId() const;
    string getName() const;
    int getMaxCapacity() const;
    int getCurrentEnrollment() const;
    bool isAvailable() const;
    
    bool enrollStudent(Student* student);
    bool dropStudent(Student* student);
    bool hasStudent(Student* student) const;
    void displayInfo() const;
    void setAvailable(bool status);
};

// ===== RegistrationSystem.hpp =====
class RegistrationSystem {
private:
    vector<Course*> courses;
    vector<Student*> students;

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
    
    Course* findCourse(string courseId) const;
    Student* findStudent(string studentId) const;
};

// ===== Course.cpp =====
Course::Course(string courseId, string name, int maxCapacity)
    : courseId(courseId), name(name), maxCapacity(maxCapacity), available(true) {}

string Course::getCourseId() const { return courseId; }
string Course::getName() const { return name; }
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
    auto it = find(enrolledStudents.begin(), enrolledStudents.end(), student);
    if (it == enrolledStudents.end()) return false;
    
    enrolledStudents.erase(it);
    return true;
}

bool Course::hasStudent(Student* student) const {
    return find(enrolledStudents.begin(), enrolledStudents.end(), student) 
           != enrolledStudents.end();
}

void Course::displayInfo() const {
    cout << "Course: " << name << " (ID: " << courseId << ")" << endl;
    cout << "Enrollment: " << getCurrentEnrollment() << "/" << maxCapacity << endl;
    cout << "Status: " << (available ? "Available" : "Closed") << endl;
}

void Course::setAvailable(bool status) {
    available = status;
} 

// ===== RegistrationSystem.cpp =====
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
    cout << "\nAll Courses:" << endl;
    for (const auto& course : courses) {
        course->displayInfo();
        cout << "------------------------" << endl;
    }
}

void RegistrationSystem::displayAllStudents() const {
    cout << "\nAll Students:" << endl;
    for (const auto& student : students) {
        student->displayInfo();
        cout << "------------------------" << endl;
    }
}

void RegistrationSystem::displayCourseEnrollments(Course* course) const {
    if (!course) return;
    
    cout << "\nEnrollments for " << course->getName() << ":" << endl;
    for (const auto& student : students) {
        if (student->isEnrolledIn(course)) {
            cout << "- " << student->getName() << " (ID: " << student->getStudentId() << ")" << endl;
        }
    }
}

void RegistrationSystem::displayStudentEnrollments(Student* student) const {
    if (!student) return;
    student->displayInfo();
}

Course* RegistrationSystem::findCourse(string courseId) const {
    for (auto course : courses) {
        if (course->getCourseId() == courseId) return course;
    }
    return nullptr;
}

Student* RegistrationSystem::findStudent(string studentId) const {
    for (auto student : students) {
        if (student->getStudentId() == studentId) return student;
    }
    return nullptr;
} 

// ===== Student.cpp =====
Student::Student(string studentId, string name)
    : studentId(studentId), name(name) {}

string Student::getStudentId() const { return studentId; }
string Student::getName() const { return name; }
const vector<Course*>& Student::getEnrolledCourses() const { return enrolledCourses; }

bool Student::enrollInCourse(Course* course) {
    if (isEnrolledIn(course)) return false;
    if (!course->enrollStudent(this)) return false;
    
    enrolledCourses.push_back(course);
    return true;
}

bool Student::dropCourse(Course* course) {
    auto it = find(enrolledCourses.begin(), enrolledCourses.end(), course);
    if (it == enrolledCourses.end()) return false;
    
    if (!course->dropStudent(this)) return false;
    enrolledCourses.erase(it);
    return true;
}

bool Student::isEnrolledIn(Course* course) const {
    return find(enrolledCourses.begin(), enrolledCourses.end(), course) 
           != enrolledCourses.end();
}

void Student::displayInfo() const {
    cout << "Student: " << name << " (ID: " << studentId << ")" << endl;
    cout << "Enrolled Courses:" << endl;
    for (const auto& course : enrolledCourses) {
        cout << "- " << course->getName() << " (ID: " << course->getCourseId() << ")" << endl;
    }
} 

// ===== RegistrationSystemDemo.cpp =====
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
        cout << "Enrolled " << student1->getName() << " in " << course1->getName() << endl;
    }
    
    if (system.enrollStudentInCourse(student2, course1)) {
        cout << "Enrolled " << student2->getName() << " in " << course1->getName() << endl;
    }
    
    if (system.enrollStudentInCourse(student1, course2)) {
        cout << "Enrolled " << student1->getName() << " in " << course2->getName() << endl;
    }
    
    // Display enrollments
    system.displayCourseEnrollments(course1);
    system.displayStudentEnrollments(student1);
    
    // Drop a course
    if (system.dropStudentFromCourse(student1, course1)) {
        cout << "\nDropped " << student1->getName() << " from " << course1->getName() << endl;
    }
    
    // Display final state
    system.displayCourseEnrollments(course1);
    system.displayStudentEnrollments(student1);
    
    return 0;
} 

