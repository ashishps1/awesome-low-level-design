#include "TaskManager.hpp"
#include <iostream>
#include <algorithm>

TaskManager::TaskManager() : taskIdCounter(1), userIdCounter(1) {}

TaskManager::~TaskManager() {
    for (auto user : users) delete user;
    for (auto task : tasks) delete task;
}

User* TaskManager::registerUser(const std::string& username, const std::string& email) {
    std::string userId = generateUserId();
    User* user = new User(userId, username, email);
    users.push_back(user);
    return user;
}

void TaskManager::removeUser(const std::string& userId) {
    auto it = std::find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    
    if (it != users.end()) {
        // Unassign all tasks from this user
        for (auto task : tasks) {
            if (task->getAssignedTo() == userId) {
                task->setAssignedTo("");
            }
        }
        delete *it;
        users.erase(it);
    }
}

Task* TaskManager::createTask(const std::string& title, const std::string& description,
                            TaskPriority priority) {
    std::string taskId = generateTaskId();
    Task* task = new Task(taskId, title, description, priority);
    tasks.push_back(task);
    return task;
}

void TaskManager::removeTask(const std::string& taskId) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [taskId](Task* task) { return task->getTaskId() == taskId; });
    
    if (it != tasks.end()) {
        // Remove task from user's assigned tasks
        if (!(*it)->getAssignedTo().empty()) {
            if (User* user = findUser((*it)->getAssignedTo())) {
                user->removeTask(taskId);
            }
        }
        
        // Remove task from dependencies
        for (auto task : tasks) {
            task->removeDependency(taskId);
        }
        
        delete *it;
        tasks.erase(it);
    }
}

bool TaskManager::assignTask(const std::string& taskId, const std::string& userId) {
    Task* task = findTask(taskId);
    User* user = findUser(userId);
    
    if (!task || !user) return false;
    
    // Remove task from previous assignee
    if (!task->getAssignedTo().empty()) {
        if (User* prevUser = findUser(task->getAssignedTo())) {
            prevUser->removeTask(taskId);
        }
    }
    
    task->setAssignedTo(userId);
    user->addTask(taskId);
    return true;
}

bool TaskManager::updateTaskStatus(const std::string& taskId, TaskStatus status) {
    Task* task = findTask(taskId);
    if (!task) return false;
    
    if (status == TaskStatus::IN_PROGRESS && !checkDependenciesMet(task)) {
        std::cout << "Cannot start task: dependencies not met" << std::endl;
        return false;
    }
    
    task->setStatus(status);
    return true;
}

bool TaskManager::addTaskDependency(const std::string& taskId, const std::string& dependencyId) {
    Task* task = findTask(taskId);
    Task* dependency = findTask(dependencyId);
    
    if (!task || !dependency || taskId == dependencyId) return false;
    
    task->addDependency(dependencyId);
    return true;
}

bool TaskManager::addTaskComment(const std::string& taskId, const std::string& comment) {
    Task* task = findTask(taskId);
    if (!task) return false;
    
    task->addComment(comment);
    return true;
}

void TaskManager::displayUserTasks(const std::string& userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    std::cout << "\nTasks assigned to " << user->getUsername() << ":" << std::endl;
    for (const auto& taskId : user->getAssignedTasks()) {
        if (Task* task = findTask(taskId)) {
            task->displayInfo();
        }
    }
}

void TaskManager::displayAllTasks() const {
    std::cout << "\nAll Tasks:" << std::endl;
    for (const auto& task : tasks) {
        task->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void TaskManager::displayAllUsers() const {
    std::cout << "\nAll Users:" << std::endl;
    for (const auto& user : users) {
        user->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

std::vector<Task*> TaskManager::getTasksByStatus(TaskStatus status) const {
    std::vector<Task*> result;
    std::copy_if(tasks.begin(), tasks.end(), std::back_inserter(result),
        [status](Task* task) { return task->getStatus() == status; });
    return result;
}

std::vector<Task*> TaskManager::getTasksByPriority(TaskPriority priority) const {
    std::vector<Task*> result;
    std::copy_if(tasks.begin(), tasks.end(), std::back_inserter(result),
        [priority](Task* task) { return task->getPriority() == priority; });
    return result;
}

User* TaskManager::findUser(const std::string& userId) const {
    auto it = std::find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Task* TaskManager::findTask(const std::string& taskId) const {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [taskId](Task* task) { return task->getTaskId() == taskId; });
    return it != tasks.end() ? *it : nullptr;
}

bool TaskManager::checkDependenciesMet(const Task* task) const {
    for (const auto& depId : task->getDependencies()) {
        Task* dependency = findTask(depId);
        if (!dependency || dependency->getStatus() != TaskStatus::COMPLETED) {
            return false;
        }
    }
    return true;
}

std::string TaskManager::generateTaskId() {
    return "T" + std::to_string(taskIdCounter++);
}

std::string TaskManager::generateUserId() {
    return "U" + std::to_string(userIdCounter++);
} 