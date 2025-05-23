from .fitness_data_observer import FitnessDataObserver


class GoalNotifier(FitnessDataObserver):
    """Concrete Observer - notifies when goals are achieved"""
    
    def __init__(self, step_goal: int = 10000, calorie_goal: float = 500.0):
        self._step_goal = step_goal
        self._calorie_goal = calorie_goal
    
    def update(self, fitness_data) -> None:
        if fitness_data.steps >= self._step_goal:
            print(f"GoalNotifier: Congratulations! You've reached your step goal of {self._step_goal} steps!")
        
        if fitness_data.calories_burned >= self._calorie_goal:
            print(f"GoalNotifier: Great job! You've burned {self._calorie_goal} calories!")