package onlinelearningplatform;

import java.util.*;

class User {
    private String userId;
    private String name;
    private String email;
    private String password;
    private String type;
    private List<Course> enrolledCourses = new ArrayList<>();
    private List<Payment> payments = new ArrayList<>();
    private List<Result> results = new ArrayList<>();

    public User(String userId, String name, String email, String password, String type) {
        this.userId = userId;
        this.name = name;
        this.email = email;
        this.password = password;
        this.type = type;
    }

    public void enrollInCourse(Course course) {
        enrolledCourses.add(course);
        course.addStudent(this);
    }

    public void makePayment(Payment payment) {
        payments.add(payment);
    }

    public void addResult(Result result) {
        results.add(result);
    }

    public String getUserId() {
        return userId;
    }

    public String getName() {
        return name;
    }
}