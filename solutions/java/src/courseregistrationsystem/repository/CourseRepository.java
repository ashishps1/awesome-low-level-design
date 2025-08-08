package courseregistrationsystem.repository;

import courseregistrationsystem.model.Course;
import courseregistrationsystem.model.CourseOffering;

import java.util.Map;
import java.util.Optional;
import java.util.concurrent.ConcurrentHashMap;

public class CourseRepository {
    private static final CourseRepository INSTANCE = new CourseRepository();
    private final Map<String, Course> courses = new ConcurrentHashMap<>();
    private final Map<String, CourseOffering> offerings = new ConcurrentHashMap<>();

    public static CourseRepository getInstance() { return INSTANCE; }
    public void saveCourse(Course c) { courses.put(c.getCourseCode(), c); }
    public void saveOffering(CourseOffering o) { offerings.put(o.getId(), o); }
    public Optional<CourseOffering> findOfferingById(String id) { return Optional.ofNullable(offerings.get(id)); }
}
