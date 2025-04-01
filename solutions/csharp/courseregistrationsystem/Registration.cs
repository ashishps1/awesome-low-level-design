using System;

namespace CourseRegistrationSystem
{
    public class Registration
    {
        private readonly Student student;
        private readonly Course course;
        private readonly DateTime registrationTime;

        public Registration(Student student, Course course, DateTime registrationTime)
        {
            this.student = student;
            this.course = course;
            this.registrationTime = registrationTime;
        }
    }
}