
#ifndef ROSTYPES_H
#define ROSTYPES_H

class Point32{
    public:
        float x;
        float y;
        float z;
        float distance;
};

class RobotPosition{
    public:
        Point32 pos;
        float ori;
};


#endif