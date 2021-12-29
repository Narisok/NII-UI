cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(Main)

find_package(SFML 2.5 REQUIRED graphics window system)
set(SFML_LIBRARIES sfml-graphics sfml-window sfml-system)

#set(SOURCES ${SOURCES})

add_subdirectory("${PROJECT_SOURCE_DIR}/API/Sources")
add_subdirectory("${PROJECT_SOURCE_DIR}/API/Includes")

add_executable(Main ${SOURCES} main.cpp)

add_executable(Example ${SOURCES} example.cpp)


set(HEADERS ${HEADERS} Vendor/Json/includes)
set(VENDOR_LIBRARIES ${VENDOR_LIBRARIES} json)

target_include_directories(Main PUBLIC ${HEADERS})
target_link_libraries(Main PUBLIC ${SFML_LIBRARIES} ${VENDOR_LIBRARIES})
target_link_directories(Main PUBLIC ./Vendor/Json)

target_include_directories(Example PUBLIC ${HEADERS})
target_link_libraries(Example PUBLIC ${SFML_LIBRARIES} ${VENDOR_LIBRARIES})
target_link_directories(Example PUBLIC ./Vendor/Json)