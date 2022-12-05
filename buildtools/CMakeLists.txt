
cmake_minimum_required(VERSION 3.20)

project(TinyBuildTools CXX)

add_library(AppFramework src/appframework/app.h src/appframework/app.cc)
target_include_directories(AppFramework PRIVATE src/appframework/)
set_target_properties(AppFramework PROPERTIES LINKER_LANGUAGE CXX)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works
if(WIN32)
    add_definitions(-DPLATFORM_WIN32=1)
    add_executable(${PROJECT_NAME} WIN32 src/compiler/compiler.cc src/appframework/os/win32.cc)
else()
    add_executable(${PROJECT_NAME} src/appframework/os/main.cc)
endif()


target_link_libraries(TinyBuildTools PRIVATE AppFramework )
target_include_directories(TinyBuildTools PRIVATE src/appframework/)