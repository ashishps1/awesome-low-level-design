package courseregistrationsystem.repository;

import courseregistrationsystem.model.Student;

import java.util.Map;
import java.util.Optional;
import java.util.concurrent.ConcurrentHashMap;

public class StudentRepository {
    private static final StudentRepository INSTANCE = new StudentRepository();
    private final Map<String, Student> students = new ConcurrentHashMap<>();

    public static StudentRepository getInstance() { return INSTANCE; }
    public void save(Student s) { students.put(s.getId(), s); }
    public Optional<Student> findById(String id) { return Optional.ofNullable(students.get(id)); }
}
