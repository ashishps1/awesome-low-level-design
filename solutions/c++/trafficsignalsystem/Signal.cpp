#include "Signal.hpp"
#include <iostream>

Signal::Signal(std::string signalId, int greenDuration, int yellowDuration, int redDuration)
    : signalId(signalId), currentColor(SignalColor::RED),
      greenDuration(greenDuration), yellowDuration(yellowDuration), redDuration(redDuration),
      isWorking(true) {
    reset();
}

std::string Signal::getSignalId() const { return signalId; }
SignalColor Signal::getCurrentColor() const { return currentColor; }
int Signal::getTimeRemaining() const { return timeRemaining; }
bool Signal::isOperational() const { return isWorking; }

void Signal::setDurations(int green, int yellow, int red) {
    greenDuration = green;
    yellowDuration = yellow;
    redDuration = red;
    reset();
}

void Signal::updateSignal(int timeElapsed) {
    if (!isWorking) return;
    
    timeRemaining -= timeElapsed;
    if (timeRemaining <= 0) {
        switchColor();
    }
}

void Signal::switchColor() {
    switch (currentColor) {
        case SignalColor::RED:
            currentColor = SignalColor::GREEN;
            timeRemaining = greenDuration;
            break;
        case SignalColor::GREEN:
            currentColor = SignalColor::YELLOW;
            timeRemaining = yellowDuration;
            break;
        case SignalColor::YELLOW:
            currentColor = SignalColor::RED;
            timeRemaining = redDuration;
            break;
    }
}

void Signal::setWorking(bool status) {
    isWorking = status;
}

void Signal::reset() {
    currentColor = SignalColor::RED;
    timeRemaining = redDuration;
}

void Signal::displayStatus() const {
    std::cout << "Signal " << signalId << ": ";
    std::cout << "Color = ";
    switch (currentColor) {
        case SignalColor::RED: std::cout << "RED"; break;
        case SignalColor::YELLOW: std::cout << "YELLOW"; break;
        case SignalColor::GREEN: std::cout << "GREEN"; break;
    }
    std::cout << ", Time Remaining: " << timeRemaining << "s";
    std::cout << ", Status: " << (isWorking ? "Working" : "Not Working") << std::endl;
} 