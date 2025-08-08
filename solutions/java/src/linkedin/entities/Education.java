package linkedin.entities;

public class Education {
    private final String school;
    private final String degree;
    private final int startYear;
    private final int endYear;

    public Education(String school, String degree, int startYear, int endYear) {
        this.school = school;
        this.degree = degree;
        this.startYear = startYear;
        this.endYear = endYear;
    }

    @Override
    public String toString() {
        return String.format("%s, %s (%d - %d)", degree, school, startYear, endYear);
    }
}
