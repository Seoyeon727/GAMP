cmake_minimum_required(VERSION 3.15...3.21)
project(santa15)

# vcpkg toolchain 설정
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

find_package(SDL2 CONFIG REQUIRED)

# 컴파일러에 따른 플래그 설정
if (MSVC)
    # MSVC용 플래그 설정 (경고를 오류로 처리하지 않음)
    add_compile_options(/W4 /WX-)
else()
    # GCC/Clang용 플래그 설정
    add_compile_options(-Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=maybe-uninitialized -Warray-bounds -g)
endif()

include_directories(
    ${SDL2_INCLUDE_DIRS}
)

file(GLOB SOURCES src/defs.h src/structs.h src/*.c src/*.h src/*/*.c src/*/*.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(
    ${PROJECT_NAME}
    SDL2::SDL2
    SDL2::SDL2main
    m
)

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/vcpkg/installed/x64-windows")



