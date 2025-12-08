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

add_executable(day2 day2/main.cpp
        day2/day2.cpp
        day2/day2.h)
target_compile_features(day2 PRIVATE cxx_std_23)
target_link_libraries(day2 PRIVATE compiler_flags)

add_executable(day3 day3/main.cpp
        day3/day3.h
        day3/day3.cpp)
target_compile_features(day3 PRIVATE cxx_std_23)
target_link_libraries(day3 PRIVATE compiler_flags)

add_executable(day4 day4/main.cpp
        day4/day4.h
        day4/day4.cpp)
target_compile_features(day4 PRIVATE cxx_std_23)
target_link_libraries(day4 PRIVATE compiler_flags)

add_executable(day5 day5/main.cpp
        day5/day5.h
        day5/day5.cpp)
target_compile_features(day5 PRIVATE cxx_std_23)
target_link_libraries(day5 PRIVATE compiler_flags)
