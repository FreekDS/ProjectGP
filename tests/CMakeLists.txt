#GTEST##############################################################
# Copied from gtest github page

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

####################################################################

# Set the SFML ROOT (used on my Windows environment)
SET(SFML_ROOT C:/Libs/SFML-BUILD)
# Make sure we use the dynamic SFML libraries
SET(SFML_STATIC_LIBRARIES FALSE)
# Search for SFML 2.x.x
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics)

set(SRC_PATH ${PROJECT_SOURCE_DIR}/SFMLgame/src)
set(GLL_PATH ${PROJECT_SOURCE_DIR}/gll/src)

set(SRC_TEST
        main.cpp
        src/EntityTests.cpp
        src/RandomTests.cpp
        src/WorldTests.cpp
        src/BoxColliderTests.cpp
        src/ObserverTests.cpp
        src/PassingCarTests.cpp
        src/PlayerTests.cpp
        src/PositionTests.cpp
        src/RacingCarTests.cpp
        src/TransformationTests.cpp
        src/VehicleTests.cpp
        src/BulletTests.cpp include/BulletTests.h)

set(SRC_GAME
        ${SRC_PATH}/Player.cpp
        ${SRC_PATH}/RacingCar.cpp
        ${SRC_PATH}/PassingCar.cpp
        ${SRC_PATH}/World.cpp
        ${SRC_PATH}/Bullet.cpp
        ${SRC_PATH}/Game.cpp
        ${SRC_PATH}/Utilities.cpp
        ${SRC_PATH}/Observer.cpp
        ${SRC_PATH}/EntityFactory.cpp
        ${SRC_PATH}/Scoreboard.cpp
        ${SRC_PATH}/Bullet.cpp
        ${GLL_PATH}/FinishLine.cpp
        )

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/SFMLgame/include)
ADD_EXECUTABLE(TESTS ${SRC_TEST} ${SRC_GAME})

TARGET_INCLUDE_DIRECTORIES(TESTS PUBLIC ${SFML_INCLUDE_DIR} include/)
TARGET_LINK_LIBRARIES(TESTS gtest_main ${SFML_LIBRARIES} GLL)

FILE(COPY ${PROJECT_SOURCE_DIR}/SFMLgame/res DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
