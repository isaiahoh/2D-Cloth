#ifndef STICK_H
#define STICK_H

#include "Point.h"

class Stick
{
private:
    Point &p0;
    Point &p1;
    float length;

    bool isActive = true;
    bool isSelected = false;

    int color = 0xFF0048E3;
    int colorWhenSelected = 0xFFCC0000;

public:
    Stick(Point &p0, Point &p1, float length);
    ~Stick() = default;

    void SetIsSelected(bool value);

    void Update(Mouse *mouse);
    void Draw() const;
    void Break();
};

#endif