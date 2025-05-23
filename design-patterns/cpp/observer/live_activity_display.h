#pragma once
#include "fitness_data_observer.h"

class LiveActivityDisplay : public FitnessDataObserver {
public:
    void update(const FitnessData& data) override;
}; 