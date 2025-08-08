package taskmanagementsystem.strategy;

import taskmanagementsystem.models.Task;

import java.util.Comparator;
import java.util.List;

public class SortByPriority implements TaskSortStrategy {
    @Override
    public void sort(List<Task> tasks) {
        // Higher priority (lower enum ordinal) comes first
        tasks.sort(Comparator.comparing(Task::getPriority).reversed());
    }
}