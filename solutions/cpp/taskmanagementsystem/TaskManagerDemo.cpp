#include "TaskManager.hpp"
#include <iostream>

int main() {
    TaskManager manager;
    
    // Register users
    User* user1 = manager.registerUser("john_doe", "john@email.com");
    User* user2 = manager.registerUser("alice_smith", "alice@email.com");
    
    std::cout << "Initial users:" << std::endl;
    manager.displayAllUsers();
    
    // Create tasks
    Task* task1 = manager.createTask("Design Database", "Create database schema", TaskPriority::HIGH);
    Task* task2 = manager.createTask("Implement API", "Develop REST API endpoints", TaskPriority::MEDIUM);
    Task* task3 = manager.createTask("Write Tests", "Create unit tests", TaskPriority::MEDIUM);
    
    // Add dependencies
    manager.addTaskDependency(task2->getTaskId(), task1->getTaskId());  // API depends on DB
    manager.addTaskDependency(task3->getTaskId(), task2->getTaskId());  // Tests depend on API
    
    // Assign tasks
    manager.assignTask(task1->getTaskId(), user1->getUserId());
    manager.assignTask(task2->getTaskId(), user2->getUserId());
    manager.assignTask(task3->getTaskId(), user2->getUserId());
    
    // Update task status
    manager.updateTaskStatus(task1->getTaskId(), TaskStatus::IN_PROGRESS);
    manager.addTaskComment(task1->getTaskId(), "Started working on schema design");
    
    // Try to start dependent task (should fail)
    manager.updateTaskStatus(task2->getTaskId(), TaskStatus::IN_PROGRESS);
    
    // Complete first task
    manager.updateTaskStatus(task1->getTaskId(), TaskStatus::COMPLETED);
    manager.addTaskComment(task1->getTaskId(), "Database schema completed");
    
    // Now can start dependent task
    manager.updateTaskStatus(task2->getTaskId(), TaskStatus::IN_PROGRESS);
    
    // Display current state
    std::cout << "\nAll tasks:" << std::endl;
    manager.displayAllTasks();
    
    std::cout << "\nTasks by user:" << std::endl;
    manager.displayUserTasks(user1->getUserId());
    manager.displayUserTasks(user2->getUserId());
    
    // Display tasks by status
    std::cout << "\nIn Progress Tasks:" << std::endl;
    auto inProgressTasks = manager.getTasksByStatus(TaskStatus::IN_PROGRESS);
    for (const auto& task : inProgressTasks) {
        task->displayInfo();
    }
    
    return 0;
} 