#pragma once
#include "request.h"

class RequestHandler {
public:
    virtual ~RequestHandler() = default;
    virtual void setNext(RequestHandler* next) = 0;
    virtual void handle(Request& request) = 0;
}; 