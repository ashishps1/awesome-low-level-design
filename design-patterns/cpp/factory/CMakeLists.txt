cmake_minimum_required(VERSION 3.10)
project(factory)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(factory
    main.cpp
    email_notification.cpp
    sms_notification.cpp
    push_notification.cpp
    notification_factory.cpp
) 