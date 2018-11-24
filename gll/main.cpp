#include <iostream>
#include <memory>
#include "Random.h"

using namespace std;

int main(int argc, char* argv[]){
	cout << "Hello world!" << endl;
	shared_ptr<RoadFighter::Random> r = RoadFighter::Random::getInstance();
	cout << r->randNum(10, 1);
	return 0;
}