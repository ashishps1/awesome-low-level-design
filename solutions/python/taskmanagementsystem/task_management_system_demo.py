
from task_manager import TaskManager
from task import Task, TaskStatus
from user import User
from datetime import datetime

class TaskManagementSystemDemo:
    @staticmethod
    def run():
        task_manager = TaskManager.get_instance()

        # Create users
        user1 = User("1", "John Doe", "john@example.com")
        user2 = User("2", "Jane Smith", "jane@example.com")

        # Create tasks
        task1 = Task("1", "Task 1", "Description 1", datetime.now(), 1, user1)
        task2 = Task("2", "Task 2", "Description 2", datetime.now(), 2, user2)
        task3 = Task("3", "Task 3", "Description 3", datetime.now(), 1, user1)

        # Add tasks to the task manager
        task_manager.create_task(task1)
        task_manager.create_task(task2)
        task_manager.create_task(task3)

        # Update a task
        task2.set_description("Updated description")
        task_manager.update_task(task2)

        # Search tasks
        search_results = task_manager.search_tasks("Task")
        print("Search Results:")
        for task in search_results:
            print(task.get_title())

        # Filter tasks
        filtered_tasks = task_manager.filter_tasks(TaskStatus.PENDING, datetime(1970, 1, 1), datetime.now(), 1)
        print("Filtered Tasks:")
        for task in filtered_tasks:
            print(task.get_title())

        # Mark a task as completed
        task_manager.mark_task_as_completed("1")

        # Get task history for a user
        task_history = task_manager.get_task_history(user1)
        print("Task History for " + user1.get_name() + ":")
        for task in task_history:
            print(task.get_title())

        # Delete a task
        task_manager.delete_task("3")


if __name__ == "__main__":
    TaskManagementSystemDemo.run()