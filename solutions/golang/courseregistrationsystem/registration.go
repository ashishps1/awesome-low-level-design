package courseregistrationsystem

import "time"

type Registration struct {
	Student          *Student
	Course           *Course
	RegistrationTime time.Time
}

func NewRegistration(student *Student, course *Course) *Registration {
	return &Registration{
		Student:          student,
		Course:           course,
		RegistrationTime: time.Now(),
	}
}
