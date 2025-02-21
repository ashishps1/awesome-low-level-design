#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <vector>
#include <ctime>

enum class TaskStatus {
    TODO,
    IN_PROGRESS,
    COMPLETED,
    BLOCKED
};

enum class TaskPriority {
    LOW,
    MEDIUM,
    HIGH,
    URGENT
};

class Task {
private:
    std::string taskId;
    std::string title;
    std::string description;
    std::string assignedTo;
    TaskStatus status;
    TaskPriority priority;
    std::time_t dueDate;
    std::vector<std::string> dependencies;  // Task IDs
    std::vector<std::string> comments;

public:
    Task(std::string taskId, std::string title, std::string description,
         TaskPriority priority = TaskPriority::MEDIUM);
    
    std::string getTaskId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    std::string getAssignedTo() const;
    TaskStatus getStatus() const;
    TaskPriority getPriority() const;
    std::time_t getDueDate() const;
    const std::vector<std::string>& getDependencies() const;
    const std::vector<std::string>& getComments() const;
    
    void setAssignedTo(const std::string& userId);
    void setStatus(TaskStatus status);
    void setPriority(TaskPriority priority);
    void setDueDate(std::time_t dueDate);
    void addDependency(const std::string& taskId);
    void removeDependency(const std::string& taskId);
    void addComment(const std::string& comment);
    void displayInfo() const;
};

#endif 