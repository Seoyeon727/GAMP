cmake_minimum_required(VERSION 3.10)
project(santa15)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 패키지 검색 모듈 포함
include(FindPkgConfig)

# SDL2 및 관련 라이브러리 검색
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

# 컴파일 옵션 설정
add_compile_options(-Wall -Wempty-body -Werror -Wmaybe-uninitialized -Warray-bounds -g)

# 포함 디렉토리 설정
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    C:/msys64/mingw64/include/SDL2
)

# 소스 파일 설정
file(GLOB SOURCES src/*.c src/*.h src/*/*.c src/*/*.h)

# 실행 파일 출력 디렉토리 설정
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES})

# 라이브러리 경로 설정
link_directories(C:/msys64/mingw64/lib)

# 라이브러리 링크 설정
target_link_libraries(${PROJECT_NAME}
    SDL2
    SDL2main
    SDL2_mixer
    SDL2_image
    SDL2_ttf
)

