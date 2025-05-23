cmake_minimum_required(VERSION 3.10)
project(proxy_pattern)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable for version 1
add_executable(image_gallery_v1
    image_gallery_app_v1.cpp
    high_resolution_image.cpp
)

# Add executable for version 2
add_executable(image_gallery_v2
    image_gallery_app_v2.cpp
    high_resolution_image.cpp
    image_proxy.cpp
) 