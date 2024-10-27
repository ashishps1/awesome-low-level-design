package courseregistrationsystem

import "sync"

type Course struct {
	Code             string
	Name             string
	Instructor       string
	MaxCapacity      int
	enrolledStudents int
	mu               sync.Mutex
}

func NewCourse(code, name, instructor string, maxCapacity int) *Course {
	return &Course{
		Code:        code,
		Name:        name,
		Instructor:  instructor,
		MaxCapacity: maxCapacity,
	}
}

func (c *Course) GetEnrolledStudents() int {
	c.mu.Lock()
	defer c.mu.Unlock()
	return c.enrolledStudents
}

func (c *Course) IncrementEnrolled() {
	c.mu.Lock()
	defer c.mu.Unlock()
	c.enrolledStudents++
}
