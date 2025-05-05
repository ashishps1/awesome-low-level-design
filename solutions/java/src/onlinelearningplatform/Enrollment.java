package onlinelearningplatform;

import java.util.*;

class Enrollment {
    private String enrollmentId;
    private String userId;
    private String courseId;
    private Date enrollmentDate;
    private String completionStatus;

    public Enrollment(String enrollmentId, String userId, String courseId, Date enrollmentDate, String completionStatus) {
        this.enrollmentId = enrollmentId;
        this.userId = userId;
        this.courseId = courseId;
        this.enrollmentDate = enrollmentDate;
        this.completionStatus = completionStatus;
    }
}
