#include "Task.h"

Task::Task(int taskId, const string &taskTitle, const string &taskDescription,
           const string &taskDueDate, const TaskPriority &taskPriority, const TaskStatus &taskStatus, int userId)
    : id(taskId), title(taskTitle), description(taskDescription), dueDate(taskDueDate),
      priority(taskPriority), status(taskStatus), assignedUserId(userId) {}

int Task::getId() const { return id; }
string Task::getTitle() const { return title; }
string Task::getDescription() const { return description; }
string Task::getDueDate() const { return dueDate; }
TaskPriority Task::getPriority() const { return priority; }
TaskStatus Task::getStatus() const { return status; }
int Task::getAssignedUser() const { return assignedUserId; }


void Task::setTitle(const string &newTitle) { title = newTitle; }
void Task::setDescription(const string &newDescription) { description = newDescription; }
void Task::setDueDate(const string &newDueDate) { dueDate = newDueDate; }
void Task::setPriority(const TaskPriority &newPriority) { priority = newPriority; }
void Task::setStatus(const TaskStatus &newStatus) { status = newStatus; }
void Task::setAssignedUserId(int userId) { assignedUserId = userId; }
