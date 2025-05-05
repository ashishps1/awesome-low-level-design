package onlinelearningplatform;

class Result {
    private String resultId;
    private String userId;
    private String courseId;
    private String quizId;
    private int score;

    public Result(String resultId, String userId, String courseId, String quizId, int score) {
        this.resultId = resultId;
        this.userId = userId;
        this.courseId = courseId;
        this.quizId = quizId;
        this.score = score;
    }
}
