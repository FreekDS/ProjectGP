# Set sources for the graphics game
SET(SRC_GAME
        main.cpp
        src/Player.cpp src/RacingCar.cpp include/RacingCar.h src/PassingCar.cpp include/PassingCar.h src/World.cpp include/World.h)

SET(SFML_ROOT C:/Libs/SFML-BUILD)
SET(SFML_STATIC_LIBRARIES FALSE)

FIND_PACKAGE(SFML 2 COMPONENTS system window graphics)

# Create an executable
ADD_EXECUTABLE(RoadFighter ${SRC_GAME})

TARGET_INCLUDE_DIRECTORIES(RoadFighter PUBLIC ${SFML_INCLUDE_DIR} include)

# Link with GLL and SFML library
TARGET_LINK_LIBRARIES(RoadFighter LINK_PUBLIC GLL ${SFML_LIBRARIES})


