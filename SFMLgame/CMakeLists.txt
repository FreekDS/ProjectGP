# Set sources for the graphics game
SET(SRC_GAME
        main.cpp
        src/Player.cpp
        src/RacingCar.cpp
        src/PassingCar.cpp
        src/World.cpp
        src/Bullet.cpp
        src/Game.cpp
        src/Utilities.cpp
        src/Observer.cpp
        src/EntityFactory.cpp
        src/FinishLine.cpp
        )

# Set the SFML ROOT (used on my Windows environment)
SET(SFML_ROOT C:/Libs/SFML-BUILD)

# Make sure we use the dynamic SFML libraries
SET(SFML_STATIC_LIBRARIES FALSE)

# Search for SFML 2.x.x
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics)

# Create an executable
ADD_EXECUTABLE(RoadFighter ${SRC_GAME})

# Include the include directories in executable 'RoadFighter'
TARGET_INCLUDE_DIRECTORIES(RoadFighter PUBLIC ${SFML_INCLUDE_DIR} include/)

# Link with GLL and SFML library
TARGET_LINK_LIBRARIES(RoadFighter LINK_PUBLIC GLL ${SFML_LIBRARIES})

# Copy resource files to binary dir
FILE(COPY ./res/ DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/res")
