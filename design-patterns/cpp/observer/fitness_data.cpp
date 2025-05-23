#include "fitness_data.h"
#include <iostream>

FitnessData::FitnessData() : steps(0), activeMinutes(0), calories(0) {}

void FitnessData::registerObserver(FitnessDataObserver* observer) {
    observers.push_back(observer);
}

void FitnessData::removeObserver(FitnessDataObserver* observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void FitnessData::notifyObservers() {
    for (auto observer : observers) {
        observer->update(*this);
    }
}

void FitnessData::newFitnessDataPushed(int steps, int activeMinutes, int calories) {
    this->steps = steps;
    this->activeMinutes = activeMinutes;
    this->calories = calories;

    std::cout << "\nFitnessData: New data received — Steps: " << steps
              << ", Active Minutes: " << activeMinutes 
              << ", Calories: " << calories << std::endl;
    notifyObservers();
}

void FitnessData::dailyReset() {
    steps = 0;
    activeMinutes = 0;
    calories = 0;
    std::cout << "\nFitnessData: Daily reset performed." << std::endl;
    notifyObservers();
} 