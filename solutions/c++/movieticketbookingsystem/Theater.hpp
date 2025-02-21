#ifndef THEATER_HPP
#define THEATER_HPP

#include <string>
#include <vector>
#include "Show.hpp"

class Theater {
private:
    std::string theaterId;
    std::string name;
    std::string location;
    int totalSeats;
    std::vector<Show*> shows;
    bool active;

public:
    Theater(std::string theaterId, std::string name, std::string location,
           int totalSeats);
    ~Theater();
    
    std::string getTheaterId() const;
    std::string getName() const;
    std::string getLocation() const;
    int getTotalSeats() const;
    bool isActive() const;
    const std::vector<Show*>& getShows() const;
    
    void addShow(Show* show);
    void removeShow(Show* show);
    void setActive(bool status);
    void displayInfo() const;
};

#endif 