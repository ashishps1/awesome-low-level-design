#include "eager_singleton.h"

// Define the static instance
EagerSingleton EagerSingleton::instance;

EagerSingleton& EagerSingleton::getInstance() {
    return instance;
} 