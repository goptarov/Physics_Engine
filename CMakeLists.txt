cmake_minimum_required(VERSION 3.0)
project(physics_engine)

set(CMAKE_CXX_STANDARD 20)

add_library(sim_core INTERFACE)
target_include_directories(sim_core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(physics_engine Main.cpp)
target_link_libraries(physics_engine PRIVATE sim_core)

target_sources(sim_core
        INTERFACE
        FILE_SET HEADERS
        BASE_DIRS .
        FILES math_tools/Vector2.hpp core/Body.hpp core/Force.hpp Integrators/Integrator.hpp computeNetForce.hpp
)