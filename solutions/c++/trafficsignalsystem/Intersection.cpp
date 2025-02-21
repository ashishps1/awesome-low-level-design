#include "Intersection.hpp"
#include <iostream>
#include <algorithm>

Intersection::Intersection(std::string intersectionId)
    : intersectionId(intersectionId), isOperational(true) {}

Intersection::~Intersection() {
    for (auto signal : signals) {
        delete signal;
    }
}

std::string Intersection::getIntersectionId() const { return intersectionId; }
bool Intersection::isWorking() const { return isOperational; }

void Intersection::addSignal(Signal* signal) {
    signals.push_back(signal);
}

void Intersection::removeSignal(const std::string& signalId) {
    auto it = std::find_if(signals.begin(), signals.end(),
        [signalId](Signal* signal) { return signal->getSignalId() == signalId; });
    
    if (it != signals.end()) {
        delete *it;
        signals.erase(it);
    }
}

void Intersection::updateSignals(int timeElapsed) {
    if (!isOperational) return;
    
    for (auto signal : signals) {
        signal->updateSignal(timeElapsed);
    }
}

void Intersection::setOperational(bool status) {
    isOperational = status;
    for (auto signal : signals) {
        signal->setWorking(status);
    }
}

void Intersection::synchronizeSignals() {
    for (auto signal : signals) {
        signal->reset();
    }
}

void Intersection::displayStatus() const {
    std::cout << "\nIntersection " << intersectionId << " Status:" << std::endl;
    std::cout << "Operational: " << (isOperational ? "Yes" : "No") << std::endl;
    std::cout << "Signals:" << std::endl;
    for (const auto& signal : signals) {
        signal->displayStatus();
    }
}

Signal* Intersection::findSignal(const std::string& signalId) const {
    auto it = std::find_if(signals.begin(), signals.end(),
        [signalId](Signal* signal) { return signal->getSignalId() == signalId; });
    return it != signals.end() ? *it : nullptr;
} 