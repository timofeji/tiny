
cmake_minimum_required(VERSION 3.20)

project(hypergraph CXX)


# Option to enable/disable rendering support
option(WITH_RENDERER "Build with rendering support" ON)

# Options to enable/disable specific render backends (only applicable if WITH_RENDERER is ON)
option(WITH_OPENGL "Build with OpenGL backend" ON)
option(WITH_VULKAN "Build with Vulkan backend" OFF)
option(WITH_METAL "Build with Metal backend" OFF)
option(WITH_DIRECTX "Build with DirectX backend" OFF)
option(WITH_WEBGPU "Build with WebGPU backend" OFF)

# Include render backend directories conditionally
if(WITH_RENDERER)

    add_library(Renderer STATIC src/renderer/renderer.h src/renderer/renderer.cc )
    target_include_directories( Renderer PRIVATE src/renderer/)
    set_target_properties(Renderer PROPERTIES LINKER_LANGUAGE CXX)

    if(WITH_OPENGL)
        add_definitions(-DWITH_OPENGL)
        target_sources(Renderer PRIVATE 
        src/renderer/backend/opengl.h)
    endif()

    if(WITH_VULKAN)
        add_definitions(-DWITH_VULKAN)
        target_sources(Renderer PRIVATE 
        src/renderer/backend/vulkan.h)
    endif()

    if(WITH_METAL)
        add_definitions(-DWITH_METAL)
        target_sources(Renderer PRIVATE 
        src/renderer/backend/metal.h)
    endif()

    if(WITH_DIRECTX)
        add_definitions(-DWITH_DIRECTX)
        target_sources(Renderer PRIVATE 
        src/renderer/backend/directx.h)
    endif()

endif()

file(GLOB OSFramework_SRC
     "src/platform/*.h"
     "src/platform/*.cc"
)

add_library(OSFramework SHARED ${OSFramework_SRC})
target_include_directories(OSFramework PRIVATE src/platform/os)
target_include_directories(OSFramework PRIVATE src/platform/)
set_target_properties(OSFramework PROPERTIES LINKER_LANGUAGE CXX)




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

target_link_libraries(${PROJECT_NAME} PRIVATE  OSFramework Compiler Renderer )