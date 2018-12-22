#include <iostream>
#include <memory>
#include "GLL/Random.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Hello world!" << endl;
    shared_ptr<RoadFighter::Random> r = RoadFighter::Random::getInstance();
    cout << r->randInt(10, 1);
    return 0;
}