package courseregistrationsystem

import "sync"

type Student struct {
	ID                int
	Name              string
	Email             string
	RegisteredCourses []*Course
	mu                sync.Mutex
}

func NewStudent(id int, name, email string) *Student {
	return &Student{
		ID:                id,
		Name:              name,
		Email:             email,
		RegisteredCourses: make([]*Course, 0),
	}
}

func (s *Student) AddCourse(course *Course) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.RegisteredCourses = append(s.RegisteredCourses, course)
}
