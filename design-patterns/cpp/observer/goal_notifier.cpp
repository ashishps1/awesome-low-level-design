#include "goal_notifier.h"
#include "fitness_data.h"
#include <iostream>

void GoalNotifier::update(const FitnessData& data) {
    if (data.getSteps() >= 10000) {
        std::cout << "GoalNotifier: Congratulations! You've reached your daily step goal!" << std::endl;
    }
    if (data.getActiveMinutes() >= 30) {
        std::cout << "GoalNotifier: Great job! You've met your active minutes goal!" << std::endl;
    }
    if (data.getCalories() >= 2000) {
        std::cout << "GoalNotifier: Amazing! You've burned your target calories!" << std::endl;
    }
} 