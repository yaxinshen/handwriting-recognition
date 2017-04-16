#ifndef __TOUCHSCREEN_FINGER__
#define __TOUCHSCREEN_FINGER__

#include <cxcore.h>
#include <vector>

class Finger
{
public:
    Finger()
    {
        area = 0.0f;
        w=h=0;
    };
public:
    CvPoint center;
    float area;
    float w;
    float h;
};


class FingerTrack
{
public:
    FingerTrack()
    {
        states=0;
        lostCount =0;
    }
    std::vector<Finger> track;
    int states;
    int lostCount;

};

#endif
