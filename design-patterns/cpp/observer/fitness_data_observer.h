#pragma once

// Forward declaration
class FitnessData;

class FitnessDataObserver {
public:
    virtual ~FitnessDataObserver() = default;
    virtual void update(const FitnessData& data) = 0;
}; 