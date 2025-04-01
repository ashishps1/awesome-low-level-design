package courseregistrationsystem

import (
	"fmt"
)

func Run() {
	registrationSystem := GetRegistrationSystem()

	// Create courses
	course1 := NewCourse("CS101", "Introduction to Programming", "John Doe", 50)
	course2 := NewCourse("CS201", "Data Structures and Algorithms", "Jane Smith", 30)

	registrationSystem.AddCourse(course1)
	registrationSystem.AddCourse(course2)

	// Create students
	student1 := NewStudent(1, "Alice", "alice@example.com")
	student2 := NewStudent(2, "Bob", "bob@example.com")

	registrationSystem.AddStudent(student1)
	registrationSystem.AddStudent(student2)

	// Search for courses
	searchResults := registrationSystem.SearchCourses("CS")
	fmt.Println("Search Results:")
	for _, course := range searchResults {
		fmt.Printf("%s - %s\n", course.Code, course.Name)
	}

	// Register courses for students
	fmt.Println("\nRegistration Results:")

	err := registrationSystem.RegisterCourse(student1, course1)
	fmt.Printf("Student 1 - Course 1: %v\n", err == nil)

	err = registrationSystem.RegisterCourse(student2, course1)
	fmt.Printf("Student 2 - Course 1: %v\n", err == nil)

	err = registrationSystem.RegisterCourse(student1, course2)
	fmt.Printf("Student 1 - Course 2: %v\n", err == nil)

	// Get registered courses for a student
	registeredCourses := registrationSystem.GetRegisteredCourses(student1)
	fmt.Println("\nRegistered Courses for Student 1:")
	for _, course := range registeredCourses {
		fmt.Printf("%s - %s\n", course.Code, course.Name)
	}
}
