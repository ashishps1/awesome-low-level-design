#pragma once
#include "fitness_data_observer.h"

class ProgressLogger : public FitnessDataObserver {
public:
    void update(const FitnessData& data) override;
}; 