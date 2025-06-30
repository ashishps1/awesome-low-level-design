package taskmanagementsystem.sortingstrategy;

import taskmanagementsystem.Task;

import java.util.Comparator;
import java.util.List;

public class SortByPriority implements TaskSortingStrategy {
    @Override
    public void sort(List<Task> tasks) {
        // Higher priority (lower enum ordinal) comes first
        tasks.sort(Comparator.comparing(Task::getPriority).reversed());
    }
}