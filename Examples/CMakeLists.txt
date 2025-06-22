set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

add_executable(Example01 "Example01.cpp")
target_link_libraries(Example01 PRIVATE InterAsync)