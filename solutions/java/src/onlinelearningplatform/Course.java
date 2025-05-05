package onlinelearningplatform;

import java.util.*;

class Course {
    private String courseId;
    private String name;
    private String type;
    private String description;
    private List<User> students = new ArrayList<>();
    private List<CourseContent> courseContents = new ArrayList<>();
    private List<Quiz> quizzes = new ArrayList<>();

    public Course(String courseId, String name, String type, String description) {
        this.courseId = courseId;
        this.name = name;
        this.type = type;
        this.description = description;
    }

    public void addStudent(User user) {
        students.add(user);
    }

    public void addContent(CourseContent content) {
        courseContents.add(content);
    }

    public void addQuiz(Quiz quiz) {
        quizzes.add(quiz);
    }

    public String getCourseId() {
        return courseId;
    }

    public String getName() {
        return name;
    }
}
