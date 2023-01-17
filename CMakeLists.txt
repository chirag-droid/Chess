cmake_minimum_required(VERSION 3.6)

# project name
project(Chess VERSION 0.0.1)

# set c++ 20 standard
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_STANDARD 20)

# Set BUILD_TYPE to debug if not set
if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type not specified. Defaulting to Debug")
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Consumed by config.h.in to define conditional code
list(APPEND DEBUG_CONFIG Debug RelWithDebInfo)
if(CMAKE_BUILD_TYPE IN_LIST DEBUG_CONFIG)
  set(DEBUG true)
else()
  set(RELEASE true)
endif()

# add all source files recursively
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp include/*.h)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# include directories where are headers are stored
target_include_directories(${CMAKE_PROJECT_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}
)

# enable VisualStudio Hot Reload feature
if (MSVC)
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:/ZI>)
  target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:/INCREMENTAL>)
endif()

# don't show console window if on release mode
if (MSVC)
  target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<IF:$<BOOL:${DEBUG}>,/SUBSYSTEM:CONSOLE,/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup>)
else()
  target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<BOOL:${RELEASE}>:-mwindows>)
endif()

# set executable project as startup project in VisualStudio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})

## vendor/3rd party libs

# SDL generate static libs
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED ON CACHE BOOL "" FORCE)
add_subdirectory(vendor/SDL2 EXCLUDE_FROM_ALL)

# statically link sdl2 library
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2-static)

# spdlog fast logging lib
add_subdirectory(vendor/spdlog EXCLUDE_FROM_ALL)

# link the spdlog lib
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE spdlog::spdlog)

# tell cmake to generate a config file
# this is done at end to include the final cmake vars
configure_file(
  include/config.h.in
  config.h
)
