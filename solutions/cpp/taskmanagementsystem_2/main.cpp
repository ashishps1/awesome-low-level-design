// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Task;
class User;
class TaskManager;

// ===== Task.hpp =====
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
    string taskId;
    string title;
    string description;
    string assignedTo;
    TaskStatus status;
    TaskPriority priority;
    time_t dueDate;
    vector<string> dependencies;  // Task IDs
    vector<string> comments;

public:
    Task(string taskId, string title, string description,
         TaskPriority priority = TaskPriority::MEDIUM);
    
    string getTaskId() const;
    string getTitle() const;
    string getDescription() const;
    string getAssignedTo() const;
    TaskStatus getStatus() const;
    TaskPriority getPriority() const;
    time_t getDueDate() const;
    const vector<string>& getDependencies() const;
    const vector<string>& getComments() const;
    
    void setAssignedTo(const string& userId);
    void setStatus(TaskStatus status);
    void setPriority(TaskPriority priority);
    void setDueDate(time_t dueDate);
    void addDependency(const string& taskId);
    void removeDependency(const string& taskId);
    void addComment(const string& comment);
    void displayInfo() const;
};

// ===== User.hpp =====
class User {
private:
    string userId;
    string username;
    string email;
    vector<string> assignedTasks;  // Task IDs
    bool active;

public:
    User(string userId, string username, string email);
    
    string getUserId() const;
    string getUsername() const;
    string getEmail() const;
    const vector<string>& getAssignedTasks() const;
    bool isActive() const;
    
    void addTask(const string& taskId);
    void removeTask(const string& taskId);
    void setActive(bool status);
    void displayInfo() const;
};

// ===== TaskManager.hpp =====
class TaskManager {
private:
    vector<Task*> tasks;
    vector<User*> users;
    int taskIdCounter;
    int userIdCounter;

public:
    TaskManager();
    ~TaskManager();
    
    // User management
    User* registerUser(const string& username, const string& email);
    void removeUser(const string& userId);
    
    // Task management
    Task* createTask(const string& title, const string& description,
                    TaskPriority priority = TaskPriority::MEDIUM);
    void removeTask(const string& taskId);
    bool assignTask(const string& taskId, const string& userId);
    bool updateTaskStatus(const string& taskId, TaskStatus status);
    bool addTaskDependency(const string& taskId, const string& dependencyId);
    bool addTaskComment(const string& taskId, const string& comment);
    
    // Display functions
    void displayUserTasks(const string& userId) const;
    void displayAllTasks() const;
    void displayAllUsers() const;
    vector<Task*> getTasksByStatus(TaskStatus status) const;
    vector<Task*> getTasksByPriority(TaskPriority priority) const;

private:
    User* findUser(const string& userId) const;
    Task* findTask(const string& taskId) const;
    bool checkDependenciesMet(const Task* task) const;
    string generateTaskId();
    string generateUserId();
};

// ===== Task.cpp =====
Task::Task(string taskId, string title, string description,
           TaskPriority priority)
    : taskId(taskId), title(title), description(description),
      status(TaskStatus::TODO), priority(priority) {
    dueDate = 0;  // No due date set
}

string Task::getTaskId() const { return taskId; }
string Task::getTitle() const { return title; }
string Task::getDescription() const { return description; }
string Task::getAssignedTo() const { return assignedTo; }
TaskStatus Task::getStatus() const { return status; }
TaskPriority Task::getPriority() const { return priority; }
time_t Task::getDueDate() const { return dueDate; }
const vector<string>& Task::getDependencies() const { return dependencies; }
const vector<string>& Task::getComments() const { return comments; }

void Task::setAssignedTo(const string& userId) {
    assignedTo = userId;
}

void Task::setStatus(TaskStatus status) {
    this->status = status;
}

void Task::setPriority(TaskPriority priority) {
    this->priority = priority;
}

void Task::setDueDate(time_t dueDate) {
    this->dueDate = dueDate;
}

void Task::addDependency(const string& taskId) {
    if (find(dependencies.begin(), dependencies.end(), taskId) == dependencies.end()) {
        dependencies.push_back(taskId);
    }
}

void Task::removeDependency(const string& taskId) {
    auto it = find(dependencies.begin(), dependencies.end(), taskId);
    if (it != dependencies.end()) {
        dependencies.erase(it);
    }
}

void Task::addComment(const string& comment) {
    comments.push_back(comment);
}

void Task::displayInfo() const {
    cout << "\nTask: " << title << " (ID: " << taskId << ")" << endl;
    cout << "Description: " << description << endl;
    cout << "Assigned to: " << (assignedTo.empty() ? "Unassigned" : assignedTo) << endl;
    
    cout << "Status: ";
    switch (status) {
        case TaskStatus::TODO: cout << "To Do"; break;
        case TaskStatus::IN_PROGRESS: cout << "In Progress"; break;
        case TaskStatus::COMPLETED: cout << "Completed"; break;
        case TaskStatus::BLOCKED: cout << "Blocked"; break;
    }
    cout << endl;
    
    cout << "Priority: ";
    switch (priority) {
        case TaskPriority::LOW: cout << "Low"; break;
        case TaskPriority::MEDIUM: cout << "Medium"; break;
        case TaskPriority::HIGH: cout << "High"; break;
        case TaskPriority::URGENT: cout << "Urgent"; break;
    }
    cout << endl;
    
    if (dueDate != 0) {
        cout << "Due Date: " << ctime(&dueDate);
    }
    
    if (!dependencies.empty()) {
        cout << "Dependencies: ";
        for (const auto& dep : dependencies) {
            cout << dep << " ";
        }
        cout << endl;
    }
    
    if (!comments.empty()) {
        cout << "Comments:" << endl;
        for (const auto& comment : comments) {
            cout << "- " << comment << endl;
        }
    }
} 

// ===== TaskManager.cpp =====
TaskManager::TaskManager() : taskIdCounter(1), userIdCounter(1) {}

TaskManager::~TaskManager() {
    for (auto user : users) delete user;
    for (auto task : tasks) delete task;
}

User* TaskManager::registerUser(const string& username, const string& email) {
    string userId = generateUserId();
    User* user = new User(userId, username, email);
    users.push_back(user);
    return user;
}

void TaskManager::removeUser(const string& userId) {
    auto it = find_if(users.begin(), users.end(),
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

Task* TaskManager::createTask(const string& title, const string& description,
                            TaskPriority priority) {
    string taskId = generateTaskId();
    Task* task = new Task(taskId, title, description, priority);
    tasks.push_back(task);
    return task;
}

void TaskManager::removeTask(const string& taskId) {
    auto it = find_if(tasks.begin(), tasks.end(),
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

bool TaskManager::assignTask(const string& taskId, const string& userId) {
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

bool TaskManager::updateTaskStatus(const string& taskId, TaskStatus status) {
    Task* task = findTask(taskId);
    if (!task) return false;
    
    if (status == TaskStatus::IN_PROGRESS && !checkDependenciesMet(task)) {
        cout << "Cannot start task: dependencies not met" << endl;
        return false;
    }
    
    task->setStatus(status);
    return true;
}

bool TaskManager::addTaskDependency(const string& taskId, const string& dependencyId) {
    Task* task = findTask(taskId);
    Task* dependency = findTask(dependencyId);
    
    if (!task || !dependency || taskId == dependencyId) return false;
    
    task->addDependency(dependencyId);
    return true;
}

bool TaskManager::addTaskComment(const string& taskId, const string& comment) {
    Task* task = findTask(taskId);
    if (!task) return false;
    
    task->addComment(comment);
    return true;
}

void TaskManager::displayUserTasks(const string& userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    cout << "\nTasks assigned to " << user->getUsername() << ":" << endl;
    for (const auto& taskId : user->getAssignedTasks()) {
        if (Task* task = findTask(taskId)) {
            task->displayInfo();
        }
    }
}

void TaskManager::displayAllTasks() const {
    cout << "\nAll Tasks:" << endl;
    for (const auto& task : tasks) {
        task->displayInfo();
        cout << "------------------------" << endl;
    }
}

void TaskManager::displayAllUsers() const {
    cout << "\nAll Users:" << endl;
    for (const auto& user : users) {
        user->displayInfo();
        cout << "------------------------" << endl;
    }
}

vector<Task*> TaskManager::getTasksByStatus(TaskStatus status) const {
    vector<Task*> result;
    copy_if(tasks.begin(), tasks.end(), back_inserter(result),
        [status](Task* task) { return task->getStatus() == status; });
    return result;
}

vector<Task*> TaskManager::getTasksByPriority(TaskPriority priority) const {
    vector<Task*> result;
    copy_if(tasks.begin(), tasks.end(), back_inserter(result),
        [priority](Task* task) { return task->getPriority() == priority; });
    return result;
}

User* TaskManager::findUser(const string& userId) const {
    auto it = find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Task* TaskManager::findTask(const string& taskId) const {
    auto it = find_if(tasks.begin(), tasks.end(),
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

string TaskManager::generateTaskId() {
    return "T" + to_string(taskIdCounter++);
}

string TaskManager::generateUserId() {
    return "U" + to_string(userIdCounter++);
} 

// ===== User.cpp =====
User::User(string userId, string username, string email)
    : userId(userId), username(username), email(email), active(true) {}

string User::getUserId() const { return userId; }
string User::getUsername() const { return username; }
string User::getEmail() const { return email; }
const vector<string>& User::getAssignedTasks() const { return assignedTasks; }
bool User::isActive() const { return active; }

void User::addTask(const string& taskId) {
    if (find(assignedTasks.begin(), assignedTasks.end(), taskId) == assignedTasks.end()) {
        assignedTasks.push_back(taskId);
    }
}

void User::removeTask(const string& taskId) {
    auto it = find(assignedTasks.begin(), assignedTasks.end(), taskId);
    if (it != assignedTasks.end()) {
        assignedTasks.erase(it);
    }
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    cout << "User: " << username << " (ID: " << userId << ")" << endl;
    cout << "Email: " << email << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    cout << "Assigned Tasks: " << assignedTasks.size() << endl;
} 

// ===== TaskManagerDemo.cpp =====
int main() {
    TaskManager manager;
    
    // Register users
    User* user1 = manager.registerUser("john_doe", "john@email.com");
    User* user2 = manager.registerUser("alice_smith", "alice@email.com");
    
    cout << "Initial users:" << endl;
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
    cout << "\nAll tasks:" << endl;
    manager.displayAllTasks();
    
    cout << "\nTasks by user:" << endl;
    manager.displayUserTasks(user1->getUserId());
    manager.displayUserTasks(user2->getUserId());
    
    // Display tasks by status
    cout << "\nIn Progress Tasks:" << endl;
    auto inProgressTasks = manager.getTasksByStatus(TaskStatus::IN_PROGRESS);
    for (const auto& task : inProgressTasks) {
        task->displayInfo();
    }
    
    return 0;
} 

