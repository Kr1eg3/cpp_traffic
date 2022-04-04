cmake_minimum_required(VERSION 3.0.0)
project(CityTraffic VERSION 0.0.1)

# exe
add_executable(CityTraffic main.cpp src/Car.cpp src/SNFS.cpp src/Road.cpp)

# Target
target_compile_features(CityTraffic PRIVATE cxx_std_20)
target_include_directories(CityTraffic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
