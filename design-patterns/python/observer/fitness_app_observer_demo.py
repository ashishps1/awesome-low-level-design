from .fitness_data import FitnessData
from .live_activity_display import LiveActivityDisplay
from .progress_logger import ProgressLogger
from .goal_notifier import GoalNotifier


def fitness_app_observer_demo():
    """Demonstrate Observer pattern with fitness tracking app"""
    print("=== Observer Pattern Demo - Fitness App ===")
    
    # Create subject
    fitness_data = FitnessData()
    
    # Create observers
    live_display = LiveActivityDisplay()
    progress_logger = ProgressLogger()
    goal_notifier = GoalNotifier(step_goal=8000, calorie_goal=300.0)
    
    # Register observers
    fitness_data.register_observer(live_display)
    fitness_data.register_observer(progress_logger)
    fitness_data.register_observer(goal_notifier)
    
    print("\n--- First fitness data update ---")
    fitness_data.set_fitness_data(5000, 250.0, 3.2)
    
    print("\n--- Second fitness data update ---")
    fitness_data.set_fitness_data(8500, 350.0, 5.1)
    
    print("\n--- Removing progress logger ---")
    fitness_data.remove_observer(progress_logger)
    
    print("\n--- Third fitness data update (no progress logger) ---")
    fitness_data.set_fitness_data(12000, 600.0, 7.8)


if __name__ == "__main__":
    fitness_app_observer_demo()