aDaeroJourney/
式式 src/
   戍式式 main.cpp
   戍式式 Game.cpp
   戍式式 Game.h
   戍式式 ChiSam.cpp
   戍式式 ChiSam.h
   戍式式 Path.cpp
   戍式式 Path.h
   戍式式 Item.cpp
   戍式式 Item.h
   戍式式 Event.cpp
   戍式式 Event.h
   戍式式 Stats.cpp
   戍式式 Stats.h
   戍式式 Renderer.cpp
   戍式式 Renderer.h
   戍式式 SoundManager.cpp
   戍式式 SoundManager.h
式式 img/
   戍式式 chihsami.png
   戍式式 items/
   戍式式 paths/
式式 sounds/
   戍式式 background_music.mp3
   戍式式 effects/
式式 CMakeLists.txt
式式 README.md
式式 requirements.txt
``

## Implementation

### CMakeLists.txt

``diff
cmake_minimum_required(VERSION 3.10)
project(GaDaeroJourney)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")

add_executable(GaDaeroJourney ${SOURCES})

target_link_libraries(GaDaeroJourney ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES})

install(TARGETS GaDaeroJourney DESTINATION bin)
install(DIRECTORY img/ DESTINATION bin/img)
install(DIRECTORY sounds/ DESTINATION bin/sounds)