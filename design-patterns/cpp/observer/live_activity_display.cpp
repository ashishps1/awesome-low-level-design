#include "live_activity_display.h"
#include "fitness_data.h"
#include <iostream>

void LiveActivityDisplay::update(const FitnessData& data) {
    std::cout << "LiveActivityDisplay: Current Activity — Steps: " << data.getSteps()
              << ", Active Minutes: " << data.getActiveMinutes()
              << ", Calories: " << data.getCalories() << std::endl;
} 