# Add source files for ABMkit core
target_include_directories( ABMkit
PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

target_sources( ABMkit
    PRIVATE
    agents.h
    model.h
)