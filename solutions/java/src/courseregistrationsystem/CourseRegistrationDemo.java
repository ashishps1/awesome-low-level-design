package courseregistrationsystem;

import courseregistrationsystem.model.*;
import courseregistrationsystem.observer.WaitlistManager;
import courseregistrationsystem.repository.CourseRepository;
import courseregistrationsystem.repository.StudentRepository;

import java.time.DayOfWeek;
import java.time.LocalTime;

public class CourseRegistrationDemo {
    public static void main(String[] args) {
        // 1. Setup the system
        CourseRegistrationSystemFacade system = new CourseRegistrationSystemFacade();
        StudentRepository studentRepo = StudentRepository.getInstance();
        CourseRepository courseRepo = CourseRepository.getInstance();
        WaitlistManager waitlistManager = WaitlistManager.getInstance();

        // 2. Setup courses and professors
        Course cs101 = new Course("CS101", "Intro to Programming");
        Course cs201 = new Course("CS201", "Data Structures");
        cs201.addPrerequisite(cs101);
        courseRepo.saveCourse(cs101); courseRepo.saveCourse(cs201);

        Professor profA = new Professor("P1", "Dr. Smith");

        // 3. Setup course offerings using the Builder
        CourseOffering cs101Offering = new CourseOffering.Builder("CS101-F23", cs101)
                .withProfessor(profA).at(new TimeSlot(DayOfWeek.MONDAY, LocalTime.of(10, 0), LocalTime.of(11, 30)))
                .withCapacity(1).build();

        CourseOffering cs201Offering = new CourseOffering.Builder("CS201-F23", cs201)
                .withProfessor(profA).at(new TimeSlot(DayOfWeek.WEDNESDAY, LocalTime.of(14, 0), LocalTime.of(15, 30)))
                .withCapacity(2).build();

        // Register the WaitlistManager as an observer for the course offering
        cs101Offering.addObserver(waitlistManager);

        courseRepo.saveOffering(cs101Offering); courseRepo.saveOffering(cs201Offering);

        // 4. Setup students
        Student alice = new Student("S1", "Alice");
        Student bob = new Student("S2", "Bob");
        Student charlie = new Student("S3", "Charlie");
        alice.addCompletedCourse(cs101); // Alice has the prerequisite for CS201
        studentRepo.save(alice); studentRepo.save(bob); studentRepo.save(charlie);

        // 5. Run Registration Scenarios
        System.out.println("----------- SCENARIO 1: Successful Registration -----------");
        system.registerStudentForCourse(alice.getId(), cs201Offering.getId());

        System.out.println("\n----------- SCENARIO 2: Prerequisite Failure -----------");
        system.registerStudentForCourse(bob.getId(), cs201Offering.getId());

        System.out.println("\n----------- SCENARIO 3: Course Capacity and Waitlist -----------");
        system.registerStudentForCourse(bob.getId(), cs101Offering.getId()); // Bob gets the last spot
        system.registerStudentForCourse(charlie.getId(), cs101Offering.getId()); // Charlie gets waitlisted

        System.out.println("\n----------- SCENARIO 4: Dropping a course and Observer pattern triggering waitlist promotion -----------");
        system.dropStudentFromCourse(bob.getId(), cs101Offering.getId());
    }
}
