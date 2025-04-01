#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <string>

enum class SignalColor {
    RED,
    YELLOW,
    GREEN
};

class Signal {
private:
    std::string signalId;
    SignalColor currentColor;
    int greenDuration;
    int yellowDuration;
    int redDuration;
    int timeRemaining;
    bool isWorking;

public:
    Signal(std::string signalId, int greenDuration = 30, int yellowDuration = 5, int redDuration = 30);
    
    std::string getSignalId() const;
    SignalColor getCurrentColor() const;
    int getTimeRemaining() const;
    bool isOperational() const;
    
    void setDurations(int green, int yellow, int red);
    void updateSignal(int timeElapsed);
    void switchColor();
    void setWorking(bool status);
    void reset();
    void displayStatus() const;
};

#endif 