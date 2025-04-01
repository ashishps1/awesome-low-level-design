#ifndef REQUEST_HPP
#define REQUEST_HPP

class Request {
private:
    int sourceFloor;
    int destinationFloor;
    bool isUp;

public:
    Request(int sourceFloor, int destinationFloor);
    
    int getSourceFloor() const;
    int getDestinationFloor() const;
    bool getIsUp() const;
};

#endif 