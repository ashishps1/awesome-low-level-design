from .fitness_data_observer import FitnessDataObserver


class ProgressLogger(FitnessDataObserver):
    """Concrete Observer - logs fitness progress"""
    
    def update(self, fitness_data) -> None:
        print(f"ProgressLogger: Logging fitness data - "
              f"Steps: {fitness_data.steps}, "
              f"Calories: {fitness_data.calories_burned:.1f}, "
              f"Distance: {fitness_data.distance_covered:.2f} km")