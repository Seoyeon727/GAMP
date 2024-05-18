# FindSDL2.cmake
# Try to find SDL2 library
# Once done, this will define
#  SDL2_INCLUDE_DIRS - where to find SDL.h
#  SDL2_LIBRARIES    - List of libraries to link against
#  SDL2_FOUND        - True if SDL2 was found

find_path(SDL2_INCLUDE_DIR SDL.h
    HINTS
    ${CMAKE_PREFIX_PATH}
    PATH_SUFFIXES include/SDL2 include
)

find_library(SDL2_LIBRARY
    NAMES SDL2
    HINTS
    ${CMAKE_PREFIX_PATH}
    PATH_SUFFIXES lib
)

set(SDL2_LIBRARIES ${SDL2_LIBRARY})
set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2 DEFAULT_MSG SDL2_LIBRARY SDL2_INCLUDE_DIR)

mark_as_advanced(SDL2_INCLUDE_DIRS SDL2_LIBRARIES)
