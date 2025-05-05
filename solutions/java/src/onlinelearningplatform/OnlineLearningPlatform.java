package onlinelearningplatform;

import java.util.Date;

public class OnlineLearningPlatform {
    public static void main(String[] args) {
        User user1 = new User("U1", "Alice", "alice@example.com", "password123", "student");
        Course course1 = new Course("C1", "Java Programming", "Programming", "Learn Java from scratch");

        user1.enrollInCourse(course1);

        Payment payment1 = new Payment("P1", user1.getUserId(), 99.99, "Credit Card", new Date());
        user1.makePayment(payment1);

        Quiz quiz1 = new Quiz("Q1", course1.getCourseId(), "Java Basics", "Basic Java quiz", 50);
        course1.addQuiz(quiz1);

        Result result1 = new Result("R1", user1.getUserId(), course1.getCourseId(), quiz1.getQuizId(), 45);
        user1.addResult(result1);

        System.out.println(user1.getName() + " has enrolled in " + course1.getName());
    }
}
