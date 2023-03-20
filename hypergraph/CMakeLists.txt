
cmake_minimum_required(VERSION 3.20)

project(hypergraph CXX)

file(GLOB OSFramework_SRC
     "src/platform/framework/*.h"
     "src/platform/framework/*.cc"
)

add_library(OSFramework SHARED ${OSFramework_SRC})
target_include_directories(OSFramework PRIVATE src/platform/)
target_include_directories(OSFramework PRIVATE src/platform/framework)
set_target_properties(OSFramework PROPERTIES LINKER_LANGUAGE CXX)



add_library(Compiler src/compiler/compiler.h src/compiler/compiler.cc )
target_include_directories(Compiler PRIVATE src/compiler/)
set_target_properties(Compiler PROPERTIES LINKER_LANGUAGE CXX)



# set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works
if(WIN32)
    add_definitions(-DPLATFORM_WIN32=1)
    add_executable(${PROJECT_NAME} WIN32 
    src/platform/app.h
    src/platform/app.cc

    src/platform/os/win32.h
    src/platform/os/win32.cc
    )
else()
    add_executable(${PROJECT_NAME} src/main.cc)
endif()


if(TEST)
   message(STATUS "Warning: Compiler testing is ON")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE  OSFramework Compiler )