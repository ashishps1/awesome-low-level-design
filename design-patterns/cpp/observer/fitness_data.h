#pragma once
#include "fitness_data_subject.h"
#include <vector>
#include <memory>

class FitnessData : public FitnessDataSubject {
public:
    FitnessData();

    // Subject interface implementation
    void registerObserver(FitnessDataObserver* observer) override;
    void removeObserver(FitnessDataObserver* observer) override;
    void notifyObservers() override;

    // Fitness data methods
    void newFitnessDataPushed(int steps, int activeMinutes, int calories);
    void dailyReset();

    // Getters
    int getSteps() const { return steps; }
    int getActiveMinutes() const { return activeMinutes; }
    int getCalories() const { return calories; }

private:
    int steps;
    int activeMinutes;
    int calories;
    std::vector<FitnessDataObserver*> observers;
}; 