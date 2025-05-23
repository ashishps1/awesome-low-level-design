#pragma once
#include "request_handler.h"

class BaseHandler : public RequestHandler {
protected:
    RequestHandler* next = nullptr;
public:
    void setNext(RequestHandler* next) override;
    void forward(Request& request);
}; 