// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Signal;
class Intersection;
class TrafficSystem;

// ===== Signal.hpp =====
enum class SignalColor {
    RED,
    YELLOW,
    GREEN
};

class Signal {
private:
    string signalId;
    SignalColor currentColor;
    int greenDuration;
    int yellowDuration;
    int redDuration;
    int timeRemaining;
    bool isWorking;

public:
    Signal(string signalId, int greenDuration = 30, int yellowDuration = 5, int redDuration = 30);
    
    string getSignalId() const;
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

// ===== Intersection.hpp =====
class Intersection {
private:
    string intersectionId;
    vector<Signal*> signals;
    bool isOperational;

public:
    Intersection(string intersectionId);
    ~Intersection();
    
    string getIntersectionId() const;
    bool isWorking() const;
    
    void addSignal(Signal* signal);
    void removeSignal(const string& signalId);
    void updateSignals(int timeElapsed);
    void setOperational(bool status);
    void synchronizeSignals();
    void displayStatus() const;

private:
    Signal* findSignal(const string& signalId) const;
};

// ===== TrafficSystem.hpp =====
class TrafficSystem {
private:
    vector<Intersection*> intersections;
    int intersectionIdCounter;
    int signalIdCounter;

public:
    TrafficSystem();
    ~TrafficSystem();
    
    Intersection* createIntersection();
    void removeIntersection(const string& intersectionId);
    Signal* addSignal(const string& intersectionId,
                     int greenDuration = 30, int yellowDuration = 5, int redDuration = 30);
    void removeSignal(const string& intersectionId, const string& signalId);
    void updateSystem(int timeElapsed);
    void setIntersectionStatus(const string& intersectionId, bool operational);
    void synchronizeIntersection(const string& intersectionId);
    void displaySystemStatus() const;

private:
    Intersection* findIntersection(const string& intersectionId) const;
    string generateIntersectionId();
    string generateSignalId();
};

// ===== Intersection.cpp =====
Intersection::Intersection(string intersectionId)
    : intersectionId(intersectionId), isOperational(true) {}

Intersection::~Intersection() {
    for (auto signal : signals) {
        delete signal;
    }
}

string Intersection::getIntersectionId() const { return intersectionId; }
bool Intersection::isWorking() const { return isOperational; }

void Intersection::addSignal(Signal* signal) {
    signals.push_back(signal);
}

void Intersection::removeSignal(const string& signalId) {
    auto it = find_if(signals.begin(), signals.end(),
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
    cout << "\nIntersection " << intersectionId << " Status:" << endl;
    cout << "Operational: " << (isOperational ? "Yes" : "No") << endl;
    cout << "Signals:" << endl;
    for (const auto& signal : signals) {
        signal->displayStatus();
    }
}

Signal* Intersection::findSignal(const string& signalId) const {
    auto it = find_if(signals.begin(), signals.end(),
        [signalId](Signal* signal) { return signal->getSignalId() == signalId; });
    return it != signals.end() ? *it : nullptr;
} 

// ===== Signal.cpp =====
Signal::Signal(string signalId, int greenDuration, int yellowDuration, int redDuration)
    : signalId(signalId), currentColor(SignalColor::RED),
      greenDuration(greenDuration), yellowDuration(yellowDuration), redDuration(redDuration),
      isWorking(true) {
    reset();
}

string Signal::getSignalId() const { return signalId; }
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
    cout << "Signal " << signalId << ": ";
    cout << "Color = ";
    switch (currentColor) {
        case SignalColor::RED: cout << "RED"; break;
        case SignalColor::YELLOW: cout << "YELLOW"; break;
        case SignalColor::GREEN: cout << "GREEN"; break;
    }
    cout << ", Time Remaining: " << timeRemaining << "s";
    cout << ", Status: " << (isWorking ? "Working" : "Not Working") << endl;
} 

// ===== TrafficSystem.cpp =====
TrafficSystem::TrafficSystem() : intersectionIdCounter(1), signalIdCounter(1) {}

TrafficSystem::~TrafficSystem() {
    for (auto intersection : intersections) {
        delete intersection;
    }
}

Intersection* TrafficSystem::createIntersection() {
    string intersectionId = generateIntersectionId();
    Intersection* intersection = new Intersection(intersectionId);
    intersections.push_back(intersection);
    return intersection;
}

void TrafficSystem::removeIntersection(const string& intersectionId) {
    auto it = find_if(intersections.begin(), intersections.end(),
        [intersectionId](Intersection* intersection) {
            return intersection->getIntersectionId() == intersectionId;
        });
    
    if (it != intersections.end()) {
        delete *it;
        intersections.erase(it);
    }
}

Signal* TrafficSystem::addSignal(const string& intersectionId,
                               int greenDuration, int yellowDuration, int redDuration) {
    Intersection* intersection = findIntersection(intersectionId);
    if (!intersection) return nullptr;
    
    string signalId = generateSignalId();
    Signal* signal = new Signal(signalId, greenDuration, yellowDuration, redDuration);
    intersection->addSignal(signal);
    return signal;
}

void TrafficSystem::removeSignal(const string& intersectionId, const string& signalId) {
    if (Intersection* intersection = findIntersection(intersectionId)) {
        intersection->removeSignal(signalId);
    }
}

void TrafficSystem::updateSystem(int timeElapsed) {
    for (auto intersection : intersections) {
        intersection->updateSignals(timeElapsed);
    }
}

void TrafficSystem::setIntersectionStatus(const string& intersectionId, bool operational) {
    if (Intersection* intersection = findIntersection(intersectionId)) {
        intersection->setOperational(operational);
    }
}

void TrafficSystem::synchronizeIntersection(const string& intersectionId) {
    if (Intersection* intersection = findIntersection(intersectionId)) {
        intersection->synchronizeSignals();
    }
}

void TrafficSystem::displaySystemStatus() const {
    cout << "\nTraffic System Status:" << endl;
    cout << "Number of Intersections: " << intersections.size() << endl;
    for (const auto& intersection : intersections) {
        intersection->displayStatus();
    }
}

Intersection* TrafficSystem::findIntersection(const string& intersectionId) const {
    auto it = find_if(intersections.begin(), intersections.end(),
        [intersectionId](Intersection* intersection) {
            return intersection->getIntersectionId() == intersectionId;
        });
    return it != intersections.end() ? *it : nullptr;
}

string TrafficSystem::generateIntersectionId() {
    return "I" + to_string(intersectionIdCounter++);
}

string TrafficSystem::generateSignalId() {
    return "S" + to_string(signalIdCounter++);
} 

// ===== TrafficSystemDemo.cpp =====
int main() {
    TrafficSystem system;
    
    // Create an intersection
    Intersection* intersection1 = system.createIntersection();
    
    // Add signals to the intersection
    Signal* signal1 = system.addSignal(intersection1->getIntersectionId(), 20, 5, 25);
    Signal* signal2 = system.addSignal(intersection1->getIntersectionId(), 20, 5, 25);
    
    // Display initial status
    system.displaySystemStatus();
    
    // Simulate traffic system for a few cycles
    for (int i = 0; i < 10; i++) {
        cout << "\nTime step " << i + 1 << ":" << endl;
        system.updateSystem(5);  // Update every 5 seconds
        system.displaySystemStatus();
        this_thread::sleep_for(chrono::seconds(1));
    }
    
    // Simulate intersection failure
    cout << "\nSimulating intersection failure..." << endl;
    system.setIntersectionStatus(intersection1->getIntersectionId(), false);
    system.displaySystemStatus();
    
    // Restore intersection
    cout << "\nRestoring intersection..." << endl;
    system.setIntersectionStatus(intersection1->getIntersectionId(), true);
    system.synchronizeIntersection(intersection1->getIntersectionId());
    system.displaySystemStatus();
    
    return 0;
} 

