package courseregistrationsystem

import (
	"fmt"
	"strings"
	"sync"
)

type CourseRegistrationSystem struct {
	courses       map[string]*Course
	students      map[int]*Student
	registrations []*Registration
	mu            sync.RWMutex
}

var (
	instance *CourseRegistrationSystem
	once     sync.Once
)

func GetRegistrationSystem() *CourseRegistrationSystem {
	once.Do(func() {
		instance = &CourseRegistrationSystem{
			courses:       make(map[string]*Course),
			students:      make(map[int]*Student),
			registrations: make([]*Registration, 0),
		}
	})
	return instance
}

func (rs *CourseRegistrationSystem) AddCourse(course *Course) {
	rs.mu.Lock()
	defer rs.mu.Unlock()
	rs.courses[course.Code] = course
}

func (rs *CourseRegistrationSystem) AddStudent(student *Student) {
	rs.mu.Lock()
	defer rs.mu.Unlock()
	rs.students[student.ID] = student
}

func (rs *CourseRegistrationSystem) SearchCourses(query string) []*Course {
	rs.mu.RLock()
	defer rs.mu.RUnlock()

	var result []*Course
	query = strings.ToLower(query)

	for _, course := range rs.courses {
		if strings.Contains(strings.ToLower(course.Code), query) ||
			strings.Contains(strings.ToLower(course.Name), query) {
			result = append(result, course)
		}
	}
	return result
}

func (rs *CourseRegistrationSystem) RegisterCourse(student *Student, course *Course) error {
	rs.mu.Lock()
	defer rs.mu.Unlock()

	// Check if course exists
	if _, exists := rs.courses[course.Code]; !exists {
		return fmt.Errorf("course %s does not exist", course.Code)
	}

	// Check if student exists
	if _, exists := rs.students[student.ID]; !exists {
		return fmt.Errorf("student with ID %d does not exist", student.ID)
	}

	// Check capacity
	if course.GetEnrolledStudents() >= course.MaxCapacity {
		return fmt.Errorf("course %s is full", course.Code)
	}

	// Check if student is already registered
	for _, c := range student.RegisteredCourses {
		if c.Code == course.Code {
			return fmt.Errorf("student is already registered for course %s", course.Code)
		}
	}

	// Create registration
	registration := NewRegistration(student, course)
	rs.registrations = append(rs.registrations, registration)

	// Update course and student
	course.IncrementEnrolled()
	student.AddCourse(course)

	rs.notifyObservers(course)
	return nil
}

func (rs *CourseRegistrationSystem) GetRegisteredCourses(student *Student) []*Course {
	rs.mu.RLock()
	defer rs.mu.RUnlock()

	if _, exists := rs.students[student.ID]; !exists {
		return nil
	}

	return student.RegisteredCourses
}

func (rs *CourseRegistrationSystem) notifyObservers(course *Course) {
	// TODO: Implement observer pattern for notifications
	fmt.Printf("Course %s updated: %d/%d students enrolled\n",
		course.Code, course.GetEnrolledStudents(), course.MaxCapacity)
}
