#ifndef TRAFFIC_SYSTEM_HPP
#define TRAFFIC_SYSTEM_HPP

#include <vector>
#include <string>
#include "Intersection.hpp"

class TrafficSystem {
private:
    std::vector<Intersection*> intersections;
    int intersectionIdCounter;
    int signalIdCounter;

public:
    TrafficSystem();
    ~TrafficSystem();
    
    Intersection* createIntersection();
    void removeIntersection(const std::string& intersectionId);
    Signal* addSignal(const std::string& intersectionId,
                     int greenDuration = 30, int yellowDuration = 5, int redDuration = 30);
    void removeSignal(const std::string& intersectionId, const std::string& signalId);
    void updateSystem(int timeElapsed);
    void setIntersectionStatus(const std::string& intersectionId, bool operational);
    void synchronizeIntersection(const std::string& intersectionId);
    void displaySystemStatus() const;

private:
    Intersection* findIntersection(const std::string& intersectionId) const;
    std::string generateIntersectionId();
    std::string generateSignalId();
};

#endif 