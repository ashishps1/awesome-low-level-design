#pragma once
#include "fitness_data_observer.h"

class FitnessDataSubject {
public:
    virtual ~FitnessDataSubject() = default;
    virtual void registerObserver(FitnessDataObserver* observer) = 0;
    virtual void removeObserver(FitnessDataObserver* observer) = 0;
    virtual void notifyObservers() = 0;
}; 