package taskmanagementsystem.sortingstrategy;

import taskmanagementsystem.Task;

import java.util.Comparator;
import java.util.List;

public class SortByDueDate implements TaskSortingStrategy {
    @Override
    public void sort(List<Task> tasks) {
        tasks.sort(Comparator.comparing(Task::getDueDate));
    }
}