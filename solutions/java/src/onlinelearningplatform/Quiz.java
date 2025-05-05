package onlinelearningplatform;

class Quiz {
    private String quizId;
    private String courseId;
    private String name;
    private String description;
    private int marks;

    public Quiz(String quizId, String courseId, String name, String description, int marks) {
        this.quizId = quizId;
        this.courseId = courseId;
        this.name = name;
        this.description = description;
        this.marks = marks;
    }

    public String getQuizId() {
        return quizId;
    }
}