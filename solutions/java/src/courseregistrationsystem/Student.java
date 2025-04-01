package courseregistrationsystem;

import java.util.List;

public class Student {
    private final int id;
    private final String name;
    private final String email;
    private final List<Course> registeredCourses;

    public Student(int id, String name, String email, List<Course> registeredCourses) {
        this.id = id;
        this.name = name;
        this.email = email;
        this.registeredCourses = registeredCourses;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getEmail() {
        return email;
    }

    public List<Course> getRegisteredCourses() {
        return registeredCourses;
    }
}
