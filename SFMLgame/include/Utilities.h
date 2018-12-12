#ifndef ROADFIGHTER_SFML_UTILITIES_H
#define ROADFIGHTER_SFML_UTILITIES_H

#include <GLL/Position.h>
#include <SFML/Graphics.hpp>
#include <utility>

using namespace std;
using namespace RoadFighter;

/**
 * Get the sizes of a box in screen coordinate system taking two points as input
 * @param cartPos1 Upper left point of the box
 * @param cartPos2 Bottom right point of the box
 * @return Sizes (width and height)
 */
pair<float, float> getSFMLSize(const Position& cartPos1, const Position& cartPos2);

/**
 * Scale a sprite by using two corners of the bounds
 * @param sprite Sprite to scale
 * @param point1 Upper left point of sprite
 * @param point2 Bottom right point of sprite
 */
void scaleSprite(sf::Sprite& sprite, Position point1, Position point2);

#endif //ROADFIGHTER_SFML_UTILITIES_H
