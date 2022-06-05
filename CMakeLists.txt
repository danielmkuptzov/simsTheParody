# The first line states the minimum CMake version to use with this project
# and is requires by CMake.
cmake_minimum_required(VERSION 3.0.0)

# Set <PROJNAME> to be your project name. We set C here as the target language. for future expansion to add c++
project(danielCity VERSION 0.1.0 LANGUAGES C CXX)

# If you want to see "under the hood" of CMake, uncomment this:
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Define variables containing compiler flags for gcc
set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")

# Set the flags for gcc
set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})

set(COREPROJ Kernel/outerCore/core/AmountSet.c
             Kernel/outerCore/core/List.h
             Kernel/outerCore/core/List.c
             Kernel/outerCore/core/set.h
             Kernel/outerCore/core/set.c)

set(OUTERCORE Kernel/outerCore/outerCore.c
              Kernel/outerCore/AmountSet.h
              Kernel/outerCore/Date.c
              Kernel/outerCore/Date.h
              Kernel/outerCore/Product.c
              ${COREPROJ})

set(KERNEL Kernel/Product.h
           Kernel/outerCore.h
           Kernel/Rational.c
           Kernel/Rational.h
           Kernel/OrderProduct.c
           Kernel/OrderProduct.h
           Kernel/Person.c
           Kernel/Kernel.c
           ${OUTERCORE})

# Add the names of your source files here
set(C_FILES main_test_block.c   Person.h  Kernel.h ${KERNEL} Apartment.c Apartment.h consrtants.h)

add_executable(danielCity ${C_FILES})
# Add the names of your source files here
#add_executable(sims the parody)
