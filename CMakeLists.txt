cmake_minimum_required (VERSION 3.5.1)
project (aqs-service)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(libs)

list(APPEND mySOURCES
    "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/Timer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/AirSensor.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/WebClient.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/PMS.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/Stream.cpp"
)

## --- MY EXECUTABLE ---
add_executable(aqs-service ${mySOURCES})

target_link_libraries(aqs-service
    -pthread
    -lcurl
    -lb64
    -lboost_system)
