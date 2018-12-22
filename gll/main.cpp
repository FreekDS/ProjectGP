#include <iostream>
#include <memory>
#include <GLL/Clock.h>

using namespace std;
using namespace RoadFighter;


int main(int argc, char* argv[])
{
    Clock cooldown(10000);
    cooldown.startTimer();
    int time = -1;
    while(!cooldown.timerFinished()){
        if(time != cooldown.timeRemainingAsSeconds()){
            time = cooldown.timeRemainingAsSeconds();
            cout << time << endl;
        }
    }
    return 0;
}