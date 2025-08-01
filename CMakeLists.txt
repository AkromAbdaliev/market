cmake_minimum_required(VERSION 3.16)
project(market CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Coroutine flags for different compilers
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines -stdlib=libc++")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")
endif()

# Source files
file(GLOB_RECURSE SOURCES
    "controllers/*.cc"
    "plugins/*.cc"
    "models/*.cc"
)

file(GLOB_RECURSE HEADERS
    "controllers/*.h"
    "models/*.h"
    "plugins/*.h"
)

add_executable(${PROJECT_NAME} main.cc ${SOURCES} ${HEADERS})

find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

# Additional required libraries for coroutines
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)
    if(CMAKE_SYSTEM_NAME MATCHES "Linux")
        target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
    endif()
endif()

# Verify C++ standard
if (CMAKE_CXX_STANDARD LESS 20)
    message(FATAL_ERROR "C++20 is required for coroutine support")
else()
    message(STATUS "Using C++20 with coroutine support")
endif()

# Source directories
aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)

# Views configuration
drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
                    ${CMAKE_CURRENT_BINARY_DIR})

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/models
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers
    ${CMAKE_CURRENT_SOURCE_DIR}/plugins
)

# Add sources
target_sources(${PROJECT_NAME}
    PRIVATE
    ${CTL_SRC}
    ${FILTER_SRC}
    ${PLUGIN_SRC}
    ${MODEL_SRC}
)


# Tests
add_subdirectory(test)
