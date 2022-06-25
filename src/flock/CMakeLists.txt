target_include_directories( ABMkit
PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

target_sources( ABMkit
    PUBLIC
    boids.h
    boids.cpp
    flock.h
    flock.cpp
)