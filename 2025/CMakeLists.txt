cmake_minimum_required(VERSION 4.1)
project(
        advent_of_code_2025
        VERSION 0.1.0
        LANGUAGES CXX
)

# Compiler Flags

add_library(compiler_flags INTERFACE)
target_compile_options(compiler_flags INTERFACE
        # Debug compiler flags
        $<$<CONFIG:Debug>:
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -Wshadow>
        $<$<CXX_COMPILER_ID:ARMClang,AppleClang,Clang>:-Wall -Wextra -Wpedantic -Wshadow-all>
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        >
        # Release compiler flags
        $<$<CONFIG:Release>:
        $<$<CXX_COMPILER_ID:GNU>:-O2 -DNDEBUG -g0 -fstack-protector-strong -fPIC -fPIE -flto -ffunction-sections -fdata-sections -fomit-frame-pointer>
        $<$<CXX_COMPILER_ID:ARMClang,AppleClang,Clang>:-O2 -DNDEBUG -g0 -fstack-protector-strong -fPIC -fPIE -flto -ffunction-sections -fdata-sections -fomit-frame-pointer>
        $<$<CXX_COMPILER_ID:MSVC>:/O2 /DNDEBUG /GL /Gy /Oi /Ot /Ob2 /GS /link /LTCG /OPT:REF /OPT:ICF>
        >
)

# Executables

add_executable(day1 day1/main.cpp
        day1/day1.cpp
        day1/day1.h)
target_compile_features(day1 PRIVATE cxx_std_23)
target_link_libraries(day1 PRIVATE compiler_flags)
