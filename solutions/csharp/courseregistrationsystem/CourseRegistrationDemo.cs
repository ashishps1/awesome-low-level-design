using System;
using System.Collections.Generic;

namespace CourseRegistrationSystem
{
    public class CourseRegistrationDemo
    {
        public static void Run()
        {
            CourseRegistrationSystem registrationSystem = CourseRegistrationSystem.GetInstance();

            // Create courses
            Course course1 = new Course("CS101", "Introduction to Programming", "John Doe", 50, 0);
            Course course2 = new Course("CS201", "Data Structures and Algorithms", "Jane Smith", 30, 0);
            registrationSystem.AddCourse(course1);
            registrationSystem.AddCourse(course2);

            // Create students
            Student student1 = new Student(1, "Alice", "alice@example.com", new List<Course>());
            Student student2 = new Student(2, "Bob", "bob@example.com", new List<Course>());
            registrationSystem.AddStudent(student1);
            registrationSystem.AddStudent(student2);

            // Search for courses
            List<Course> searchResults = registrationSystem.SearchCourses("CS");
            Console.WriteLine("Search Results:");
            foreach (Course course in searchResults)
            {
                Console.WriteLine(course.GetCode() + " - " + course.GetName());
            }

            // Register courses for students
            bool registered1 = registrationSystem.RegisterCourse(student1, course1);
            bool registered2 = registrationSystem.RegisterCourse(student2, course1);
            bool registered3 = registrationSystem.RegisterCourse(student1, course2);

            Console.WriteLine("Registration Results:");
            Console.WriteLine("Student 1 - Course 1: " + registered1);
            Console.WriteLine("Student 2 - Course 1: " + registered2);
            Console.WriteLine("Student 1 - Course 2: " + registered3);

            // Get registered courses for a student
            List<Course> registeredCourses = registrationSystem.GetRegisteredCourses(student1);
            Console.WriteLine("Registered Courses for Student 1:");
            foreach (Course course in registeredCourses)
            {
                Console.WriteLine(course.GetCode() + " - " + course.GetName());
            }
        }
    }
}