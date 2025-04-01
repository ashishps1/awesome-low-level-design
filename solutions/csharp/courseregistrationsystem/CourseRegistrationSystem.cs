using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;

namespace CourseRegistrationSystem
{
    public class CourseRegistrationSystem
    {
        private static CourseRegistrationSystem instance;
        private readonly ConcurrentDictionary<string, Course> courses;
        private readonly ConcurrentDictionary<int, Student> students;
        private readonly List<Registration> registrations;

        private CourseRegistrationSystem()
        {
            courses = new ConcurrentDictionary<string, Course>();
            students = new ConcurrentDictionary<int, Student>();
            registrations = new List<Registration>();
        }

        public static CourseRegistrationSystem GetInstance()
        {
            if (instance == null)
            {
                instance = new CourseRegistrationSystem();
            }
            return instance;
        }

        public void AddCourse(Course course) => courses[course.GetCode()] = course;

        public void AddStudent(Student student) => students[student.GetId()] = student;

        public List<Course> SearchCourses(string query)
        {
            return courses.Values
                          .Where(course => course.GetCode().Contains(query) || course.GetName().Contains(query))
                          .ToList();
        }

        public bool RegisterCourse(Student student, Course course)
        {
            if (course.GetEnrolledStudents() < course.GetMaxCapacity())
            {
                Registration registration = new Registration(student, course, DateTime.Now);
                registrations.Add(registration);
                student.GetRegisteredCourses().Add(course);
                course.SetEnrolledStudents(course.GetEnrolledStudents() + 1);
                NotifyObservers(course);
                return true;
            }
            return false;
        }

        public List<Course> GetRegisteredCourses(Student student) => student.GetRegisteredCourses();

        private void NotifyObservers(Course course)
        {
            // Notify observers (e.g., UI) about the updated course enrollment
        }
    }
}