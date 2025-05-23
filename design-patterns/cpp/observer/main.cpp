#include "fitness_data.h"
#include "live_activity_display.h"
#include "progress_logger.h"
#include "goal_notifier.h"
#include <iostream>

int main() {
    // Create the subject
    FitnessData fitnessData;

    // Create observers
    LiveActivityDisplay liveDisplay;
    ProgressLogger logger;
    GoalNotifier notifier;

    // Register observers
    fitnessData.registerObserver(&liveDisplay);
    fitnessData.registerObserver(&logger);
    fitnessData.registerObserver(&notifier);

    // Simulate fitness data updates
    std::cout << "=== Fitness App Observer Demo ===\n" << std::endl;

    // First update
    std::cout << "Update 1:" << std::endl;
    fitnessData.newFitnessDataPushed(5000, 15, 1000);

    // Second update
    std::cout << "\nUpdate 2:" << std::endl;
    fitnessData.newFitnessDataPushed(12000, 45, 2500);

    // Daily reset
    std::cout << "\nDaily Reset:" << std::endl;
    fitnessData.dailyReset();

    return 0;
} 