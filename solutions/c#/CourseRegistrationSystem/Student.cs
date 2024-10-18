using System.Collections.Generic;

namespace CourseRegistrationSystem
{
    public class Student
    {
        private readonly int id;
        private readonly string name;
        private readonly string email;
        private readonly List<Course> registeredCourses;

        public Student(int id, string name, string email, List<Course> registeredCourses)
        {
            this.id = id;
            this.name = name;
            this.email = email;
            this.registeredCourses = registeredCourses;
        }

        public int GetId() => id;
        public string GetName() => name;
        public string GetEmail() => email;
        public List<Course> GetRegisteredCourses() => registeredCourses;
    }
}