cmake_minimum_required(VERSION 3.0.0)
project(convolution_test VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} src/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# For OpenCV
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
endif()