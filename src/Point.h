#ifndef POINT_H
#define POINT_H

#include "Mouse.h"
#include "./Physics/Vec2.h"

class Point
{
private:
    Vec2 pos;
    Vec2 prevPos;
    Vec2 initPos;
    bool isPinned = false;

    bool isSelected = false;

    void KeepInsideView(int width, int height);

public:
    Point() = default;
    Point(float x, float y);
    ~Point() = default;

    const Vec2 &GetPosition() const { return pos; }
    void SetPosition(float x, float y);
    bool checkIfSelected();
    void Pin();

    void Update(float deltaTime, float drag, const Vec2 &acceleration, float elasticity, Mouse *mouse, int windowWidth, int windowHeight);
};

#endif