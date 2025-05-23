from .fitness_data_observer import FitnessDataObserver


class LiveActivityDisplay(FitnessDataObserver):
    """Concrete Observer - displays live fitness data"""
    
    def update(self, fitness_data) -> None:
        print(f"LiveActivityDisplay: Steps: {fitness_data.steps}, "
              f"Calories: {fitness_data.calories_burned:.1f}, "
              f"Distance: {fitness_data.distance_covered:.2f} km")