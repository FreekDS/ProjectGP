CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(RoadFighter)

# Basic setup
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# Without this setting, the cmake gives a warning involving policy CMP0074
CMAKE_POLICY(SET CMP0074 OLD)

# Game logic library
ADD_SUBDIRECTORY(gll)

# SFML graphical implementation
ADD_SUBDIRECTORY(SFMLgame)