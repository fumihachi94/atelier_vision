cmake_minimum_required(VERSION 3.0.0)
project(rgb_world_pjt VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(rgb_world src/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# For OpenCV
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    target_include_directories(rgb_world PUBLIC ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(rgb_world ${OpenCV_LIBS})
endif()