# Add ABMkit library target
add_library(ABMkit)
set_target_properties(ABMkit PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(ABMkit PRIVATE -Werror)
target_include_directories(ABMkit PUBLIC ./)

#
# Make all headers as PUBLIC HEADERS so that they get installed
#
# get_target_property(ABMkit_SOURCES ABMkit SOURCES)
# set(ABMkit_PUBLIC_HEADERS ${ABMkit_SOURCES})
# list(FILTER ABMkit_PUBLIC_HEADERS INCLUDE REGEX "\\.H")
# set_target_properties( ABMkit PROPERTIES PUBLIC_HEADER "${ABMkit_PUBLIC_HEADERS}")

# ABMtoolkit core components
add_subdirectory( core )

# Flocking 
add_subdirectory( flock )