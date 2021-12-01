# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("project-box")

# Include sub-projects.
set(EXECUTABLE_CUSTOM_NAME "project-box")
add_subdirectory ("project-box")
