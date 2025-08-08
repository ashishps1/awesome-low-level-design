package courseregistrationsystem.model;

import java.time.DayOfWeek;
import java.time.LocalTime;

public record TimeSlot(DayOfWeek day, LocalTime startTime, LocalTime endTime) {
    public boolean overlaps(TimeSlot other) {
        return this.day == other.day &&
                this.startTime.isBefore(other.endTime) &&
                this.endTime.isAfter(other.startTime);
    }
}
