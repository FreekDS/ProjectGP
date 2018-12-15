#include <Utilities.h>
#include <GLL/Transformation.h>
#include <cmath>

/**
 * Get the sizes of a box in screen coordinate system taking two points as input
 * @param cartPos1 Upper left point of the box
 * @param cartPos2 Bottom right point of the box
 * @return Sizes (width and height)
 */
pair<float, float> getSFMLSize(const Position& cartPos1, const Position& cartPos2)
{
    auto trans = Transformation::getInstance();
    Position screenPos1 = trans->getScreenCoordinate(cartPos1);
    Position screenPos2 = trans->getScreenCoordinate(cartPos2);
    auto width = static_cast<float>(fabs(screenPos2.x - screenPos1.x));
    auto height = static_cast<float>(fabs(screenPos2.y - screenPos1.y));
    return {width, height};
}

/**
 * Scale a sprite by using two corners of the bounds
 * @param sprite Sprite to scale
 * @param point1 Upper left point of sprite
 * @param point2 Bottom right point of sprite
 */
void scaleSprite(sf::Sprite& sprite,  Position point1,  Position point2)
{
    auto trans = Transformation::getInstance();
    Position p1 = trans->getScreenCoordinate(point1);
    Position p2 = trans->getScreenCoordinate(point2);
    auto texture = sprite.getTexture();
    double width = fabs(p2.x - p1.x);
    double height = fabs(p2.y - p1.y);
    float scaleX = static_cast<float>(width/texture->getSize().x);
    float scaleY = static_cast<float>(height/texture->getSize().y);
    sprite.scale(scaleX, scaleY);
}

/**
 * Parses the program arguments and puts them in the given parameters
 * @param argc Argument count
 * @param argv Array of arguments
 * @param fullscreen Storage for fullscreen bool
 * @param debug Storage for debug bool
 */
void parseProgramArgs(int argc, char* argv[], bool& fullscreen, bool& debug)
{
    if(argc < 2)
        return;
    for(int i = 0; i<argc; i++){
        string currentArg = argv[i];
        if(currentArg == "-debug")
            debug = true;
        else if(currentArg == "-windowed")
            fullscreen = false;
    }
}
