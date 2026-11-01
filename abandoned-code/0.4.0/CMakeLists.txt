cmake_minimum_required(VERSION 3.10)

# Define project name and language
project(SPYDERFLY C)

# Set the C standard (C11 is standard, adjust if needed)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Automatically collect all .c files in the core directory
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS "src/*.c")

# Create the executable from the collected core sources
add_executable(spyderfly ${CORE_SOURCES})
target_include_directories(spyderfly PRIVATE include)

# Find OpenSSL package on the system
find_package(OpenSSL REQUIRED)

# Include OpenSSL header directories if needed
include_directories(${OPENSSL_INCLUDE_DIR})

# Make sure your spyderfly executable links against OpenSSL and pthread
target_link_libraries(spyderfly 
    OpenSSL::SSL 
    OpenSSL::Crypto
)