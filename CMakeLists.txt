### MAIN PARAMETERS ###

# Define minimum required version of cmake
cmake_minimum_required(VERSION 3.10)

# Define project properties
project(
    "Intent recognizer"
    VERSION 0.1
    LANGUAGES CXX
    DESCRIPTION "This application extracts an intent from a user-given string"
)

# Set the required c++-standard to at least c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


### MAIN PROGRAM SETUP ###

# Add intent object as library
add_library(intent src/intent.cpp src/intent.hpp)

# Add data handler as library
add_library(handle_data src/handle_data.cpp src/handle_data.hpp)

# Add the main executable
add_executable(recognize src/main.cpp)

# Link intent object to main executable
target_link_libraries(recognize
    PRIVATE intent
    PRIVATE handle_data
)


### UNIT TEST SETUP ###

# Add the unit-test library "Catch 2" to the project
add_library(Catch INTERFACE)

# Add the tests source as an executable
add_executable(tests tests/tests.cpp)
target_include_directories(tests
    PRIVATE src)

message(${VARIAB})

# Link the "Catch-2"-library to the tests target
target_link_libraries(tests
    Catch
    intent
)