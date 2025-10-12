from task_management_system import TaskManagementSystem
from task_priority import TaskPriority
from task_status import TaskStatus
from datetime import date
from task_sort_strategy import SortByDueDate

class TaskManagementSystemDemo:
    @staticmethod
    def main():
        task_management_system = TaskManagementSystem.get_instance()
        
        # Create users
        user1 = task_management_system.create_user("John Doe", "john@example.com")
        user2 = task_management_system.create_user("Jane Smith", "jane@example.com")
        
        # Create task lists
        task_list1 = task_management_system.create_task_list("Enhancements")
        task_list2 = task_management_system.create_task_list("Bug Fix")
        
        # Create tasks
        task1 = task_management_system.create_task(
            "Enhancement Task", "Launch New Feature",
            date.today().replace(day=date.today().day + 2), 
            TaskPriority.LOW, user1.id
        )
        subtask1 = task_management_system.create_task(
            "Enhancement sub task", "Design UI/UX",
            date.today().replace(day=date.today().day + 1), 
            TaskPriority.MEDIUM, user1.id
        )
        task2 = task_management_system.create_task(
            "Bug Fix Task", "Fix API Bug",
            date.today().replace(day=date.today().day + 3), 
            TaskPriority.HIGH, user2.id
        )
        
        task1.add_subtask(subtask1)
        
        task_list1.add_task(task1)
        task_list2.add_task(task2)
        
        task_list1.display()
        
        # Update task status
        subtask1.start_progress()
        
        # Assign task
        subtask1.set_assignee(user2)
        
        task_list1.display()
        
        # Search tasks
        search_results = task_management_system.search_tasks("Task", SortByDueDate())
        print("\nTasks with keyword Task:")
        for task in search_results:
            print(task.get_title())
        
        # Filter tasks by status
        filtered_tasks = task_management_system.list_tasks_by_status(TaskStatus.TODO)
        print("\nTODO Tasks:")
        for task in filtered_tasks:
            print(task.get_title())
        
        # Mark a task as done
        subtask1.complete_task()
        
        # Get tasks assigned to a user
        user_task_list = task_management_system.list_tasks_by_user(user2.id)
        print(f"\nTask for {user2.name}:")
        for task in user_task_list:
            print(task.get_title())
        
        task_list1.display()
        
        # Delete a task
        task_management_system.delete_task(task2.get_id())

if __name__ == "__main__":
    TaskManagementSystemDemo.main()