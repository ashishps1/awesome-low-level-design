#ifndef TASK_H
#define TASK_H

#include <string>
using namespace std;

enum TaskStatus
{
    PENDING,
    IN_PROGRESS,
    COMPLETED
};

enum TaskPriority
{
    LOW,
    NORMAL,
    HIGH,
    ONHOLD
};

class Task
{
private:
    int id;
    string title;
    string description;
    string dueDate;
    TaskPriority priority;
    TaskStatus status;
    int assignedUserId;

public:
    Task(int taskId, const string &taskTitle, const string &taskDescription,
         const string &taskDueDate, const TaskPriority &taskPriority, const TaskStatus &taskStatus, int userId = -1);

    // Getters
    int getId() const;
    string getTitle() const;
    string getDescription() const;
    string getDueDate() const;
    TaskPriority getPriority() const;
    TaskStatus getStatus() const;
    int getAssignedUser() const;

    // Setters
    void setTitle(const string &newTitle);
    void setDescription(const string &newDescription);
    void setDueDate(const string &newDueDate);
    void setPriority(const TaskPriority &newPriority);
    void setStatus(const TaskStatus &newStatus);
    void setAssignedUserId(int userId);
};

#endif
