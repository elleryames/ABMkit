# Add demo target and link against ABMkit
add_executable( flock src/main.cpp )
target_link_libraries( flock ABMkit )