#include<iostream>
#include<string>
#include <ctime>  
#include "TaskManager.h"
using namespace std;

int main()
{
    TaskManager taskManager;

    // Create some users
    User user1(1, "Alice", "alice@example.com");
    User user2(2, "Bob", "bob@example.com");
    taskManager.addUser(user1);
    taskManager.addUser(user2);

    // Create some tasks
    Task task1(101, "Fix Bug", "Fix the critical bug in production", "2025-01-15", HIGH, PENDING);
    Task task2(102, "Write Report", "Prepare the quarterly report", "2025-01-20", NORMAL,PENDING);
    taskManager.createTask(task1);
    taskManager.createTask(task2);

    // Assign task
    taskManager.assignTaskToUser(1, 101);

    // Mark task as completed
    taskManager.markTaskComplete(101);

    // Get task history
    vector<Task> history = taskManager.getTaskHistory();
    cout << "Completed Tasks:" << endl;
    for (const auto &task : history)
    {
        cout << "Task ID: " << task.getId() << ", Title: " << task.getTitle() << endl;
    }

    //tasks file save
    taskManager.saveTasksToFile("tasks.txt");

    return 0;
}
