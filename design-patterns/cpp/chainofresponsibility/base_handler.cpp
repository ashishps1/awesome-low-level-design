#include "base_handler.h"

void BaseHandler::setNext(RequestHandler* nextHandler) {
    next = nextHandler;
}

void BaseHandler::forward(Request& request) {
    if (next) {
        next->handle(request);
    }
} 