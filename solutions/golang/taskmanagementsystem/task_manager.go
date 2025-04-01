package taskmanagementsystem

import (
	"sync"
	"time"
)

type TaskManager struct {
	tasks     map[string]*Task
	userTasks map[string][]*Task
	mu        sync.Mutex
}

var instance *TaskManager
var once sync.Once

func GetTaskManager() *TaskManager {
	once.Do(func() {
		instance = &TaskManager{
			tasks:     make(map[string]*Task),
			userTasks: make(map[string][]*Task),
		}
	})
	return instance
}

func (tm *TaskManager) CreateTask(task *Task) {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	tm.tasks[task.GetId()] = task
	tm.assignTaskToUser(task.GetAssignedUser(), task)
}

func (tm *TaskManager) UpdateTask(updatedTask *Task) {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	if existingTask, exists := tm.tasks[updatedTask.GetId()]; exists {
		existingTask.SetTitle(updatedTask.GetTitle())
		existingTask.SetDescription(updatedTask.GetDescription())
		existingTask.SetDueDate(updatedTask.GetDueDate())
		existingTask.SetPriority(updatedTask.GetPriority())
		existingTask.SetStatus(updatedTask.GetStatus())

		if existingTask.GetAssignedUser() != updatedTask.GetAssignedUser() {
			tm.unassignTaskFromUser(existingTask.GetAssignedUser(), existingTask)
			tm.assignTaskToUser(updatedTask.GetAssignedUser(), existingTask)
		}
	}
}

func (tm *TaskManager) DeleteTask(taskId string) {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	if task, exists := tm.tasks[taskId]; exists {
		delete(tm.tasks, taskId)
		tm.unassignTaskFromUser(task.GetAssignedUser(), task)
	}
}

func (tm *TaskManager) SearchTasks(keyword string) []*Task {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	var matchingTasks []*Task
	for _, task := range tm.tasks {
		if contains(task.GetTitle(), keyword) || contains(task.GetDescription(), keyword) {
			matchingTasks = append(matchingTasks, task)
		}
	}
	return matchingTasks
}

func (tm *TaskManager) FilterTasks(status TaskStatus, startDate, endDate time.Time, priority int) []*Task {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	var filteredTasks []*Task
	for _, task := range tm.tasks {
		if task.GetStatus() == status &&
			task.GetDueDate().After(startDate) &&
			task.GetDueDate().Before(endDate) &&
			task.GetPriority() == priority {
			filteredTasks = append(filteredTasks, task)
		}
	}
	return filteredTasks
}

func (tm *TaskManager) MarkTaskAsCompleted(taskId string) {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	if task, exists := tm.tasks[taskId]; exists {
		task.SetStatus(Completed)
	}
}

func (tm *TaskManager) GetTaskHistory(user *User) []*Task {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	return tm.userTasks[user.GetId()]
}

func (tm *TaskManager) assignTaskToUser(user *User, task *Task) {
	tm.userTasks[user.GetId()] = append(tm.userTasks[user.GetId()], task)
}

func (tm *TaskManager) unassignTaskFromUser(user *User, task *Task) {
	tasks := tm.userTasks[user.GetId()]
	for i, t := range tasks {
		if t == task {
			tm.userTasks[user.GetId()] = append(tasks[:i], tasks[i+1:]...)
			break
		}
	}
}

func contains(text, substr string) bool {
	return len(text) >= len(substr) && text[:len(substr)] == substr
}
