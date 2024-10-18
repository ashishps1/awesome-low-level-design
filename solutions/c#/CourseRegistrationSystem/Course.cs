namespace CourseRegistrationSystem
{
    public class Course
    {
        private readonly string code;
        private readonly string name;
        private readonly string instructor;
        private readonly int maxCapacity;
        private int enrolledStudents;

        public Course(string code, string name, string instructor, int maxCapacity, int enrolledStudents)
        {
            this.code = code;
            this.name = name;
            this.instructor = instructor;
            this.maxCapacity = maxCapacity;
            this.enrolledStudents = enrolledStudents;
        }

        public string GetCode() => code;
        public string GetName() => name;
        public string GetInstructor() => instructor;
        public int GetMaxCapacity() => maxCapacity;
        public int GetEnrolledStudents() => enrolledStudents;

        public void SetEnrolledStudents(int enrolledStudents) => this.enrolledStudents = enrolledStudents;
    }
}