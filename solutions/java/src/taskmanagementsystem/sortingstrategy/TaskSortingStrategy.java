package taskmanagementsystem.sortingstrategy;

import taskmanagementsystem.Task;

import java.util.List;

public interface TaskSortingStrategy {
    void sort(List<Task> tasks);
}
