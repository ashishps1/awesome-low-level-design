package taskmanagementsystem

import "time"

type Task struct {
	Id           string
	Title        string
	Description  string
	DueDate      time.Time
	Priority     int
	Status       TaskStatus
	AssignedUser *User
}

func NewTask(id, title, description string, dueDate time.Time, priority int, assignedUser *User) *Task {
	return &Task{
		Id:           id,
		Title:        title,
		Description:  description,
		DueDate:      dueDate,
		Priority:     priority,
		Status:       Pending,
		AssignedUser: assignedUser,
	}
}

func (t *Task) GetId() string {
	return t.Id
}

func (t *Task) GetTitle() string {
	return t.Title
}

func (t *Task) GetDescription() string {
	return t.Description
}

func (t *Task) GetDueDate() time.Time {
	return t.DueDate
}

func (t *Task) GetPriority() int {
	return t.Priority
}

func (t *Task) GetStatus() TaskStatus {
	return t.Status
}

func (t *Task) GetAssignedUser() *User {
	return t.AssignedUser
}

func (t *Task) SetTitle(title string) {
	t.Title = title
}

func (t *Task) SetDescription(description string) {
	t.Description = description
}

func (t *Task) SetDueDate(dueDate time.Time) {
	t.DueDate = dueDate
}

func (t *Task) SetPriority(priority int) {
	t.Priority = priority
}

func (t *Task) SetStatus(status TaskStatus) {
	t.Status = status
}
