package linkedin.entities;

import java.time.LocalDate;

public class Experience {
    private final String title;
    private final String company;
    private final LocalDate startDate;
    private final LocalDate endDate; // Can be null for current job

    public Experience(String title, String company, LocalDate startDate, LocalDate endDate) {
        this.title = title;
        this.company = company;
        this.startDate = startDate;
        this.endDate = endDate;
    }

    @Override
    public String toString() {
        return String.format("%s at %s (%s to %s)", title, company, startDate, endDate == null ? "Present" : endDate);
    }
}
