from course_registration_system import CourseRegistrationSystem
from course import Course
from student import Student

class CourseRegistrationDemo:
    @staticmethod
    def run():
        registration_system = CourseRegistrationSystem.get_instance()

        # Create courses
        course1 = Course("CS101", "Introduction to Programming", "John Doe", 50, 0)
        course2 = Course("CS201", "Data Structures and Algorithms", "Jane Smith", 30, 0)
        registration_system.add_course(course1)
        registration_system.add_course(course2)

        # Create students
        student1 = Student(1, "Alice", "alice@example.com", [])
        student2 = Student(2, "Bob", "bob@example.com", [])
        registration_system.add_student(student1)
        registration_system.add_student(student2)

        # Search for courses
        search_results = registration_system.search_courses("CS")
        print("Search Results:")
        for course in search_results:
            print(f"{course.get_code()} - {course.get_name()}")

        # Register courses for students
        registered1 = registration_system.register_course(student1, course1)
        registered2 = registration_system.register_course(student2, course1)
        registered3 = registration_system.register_course(student1, course2)

        print("Registration Results:")
        print(f"Student 1 - Course 1: {registered1}")
        print(f"Student 2 - Course 1: {registered2}")
        print(f"Student 1 - Course 2: {registered3}")

        # Get registered courses for a student
        registered_courses = registration_system.get_registered_courses(student1)
        print("Registered Courses for Student 1:")
        for course in registered_courses:
            print(f"{course.get_code()} - {course.get_name()}")

if __name__ == "__main__":
    CourseRegistrationDemo.run()