# The first line states the minimum CMake version to use with this project
# and is requires by CMake.
cmake_minimum_required(VERSION 3.0.0)

# Set <PROJNAME> to be your project name. We set C here as the target language.
project(danielCity VERSION 0.1.0 LANGUAGES C)

# If you want to see "under the hood" of CMake, uncomment this:
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Define variables containing compiler flags for gcc
set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")

# Set the flags for gcc
set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})

set(COREPROJ outerCore/core/AmountSet.c outerCore/core/List.h outerCore/core/List.c outerCore/core/set.h outerCore/core/set.c)

set(OUTERCORE outerCore/outerCore.c outerCore/AmountSet.h  outerCore/Date.c outerCore/Date.h outerCore/Product.c ${COREPROJ})
# Add the names of your source files here
set(C_FILES main_test_block.c  Product.h  outerCore.h Rational.c Rational.h ${OUTERCORE} OrderProduct.c OrderProduct.h Person.c Person.h)

add_executable(danielCity ${C_FILES})
# Add the names of your source files here
#add_executable(sims the parody)
