# Set Source files for GLL (= game logic library)
SET(SRC_GLL
        src/Random.cpp
        src/Entity.cpp
        src/Vehicle.cpp
        src/Player.cpp
        src/RacingCar.cpp
        src/PassingCar.cpp
        src/World.cpp
        src/Position.cpp
        src/Bullet.cpp
        src/Transformation.cpp
        src/EntityFactory.cpp
        src/Game.cpp
        src/BoxCollider.cpp
        src/Clock.cpp
        )

# Temporary for testing purpose
ADD_EXECUTABLE(GLL_DEBUG ${SRC_GLL} main.cpp)

# Add include directory to debug executable
TARGET_INCLUDE_DIRECTORIES(GLL_DEBUG PUBLIC include)

# Create static GLL library
ADD_LIBRARY(GLL ${SRC_GLL})
# Link header files with GLL library
TARGET_INCLUDE_DIRECTORIES(GLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)