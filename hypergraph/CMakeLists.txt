
cmake_minimum_required(VERSION 3.20)

project(hypergraph CXX)

add_library(AppFramework src/platform/app.h src/platform/app.cc)

target_include_directories(AppFramework PRIVATE src/platform/)
set_target_properties(AppFramework PROPERTIES LINKER_LANGUAGE CXX)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works
if(WIN32)
    add_definitions(-DPLATFORM_WIN32=1)
    add_executable(${PROJECT_NAME} WIN32 src/platform/os/win32.cc)
else()
    add_executable(${PROJECT_NAME} src/main.cc)
endif()


target_link_libraries(${PROJECT_NAME} PRIVATE AppFramework )
# target_include_directories(${PROJECT_NAME} PRIVATE src/appframework/)