#ifndef MOUSE_H
#define MOUSE_H

#include "./Physics/Vec2.h"

class Mouse
{
private:
    Vec2 pos;
    Vec2 prevPos;

    float cursorSize = 20;
    float maxCursorSize = 100;
    float minCursorSize = 20;

    bool leftButtonDown = false;
    bool rightButtonDown = false;

public:
    Mouse() = default;
    ~Mouse() = default;

    void UpdatePosition(int x, int y);
    const Vec2 &GetPosition() const { return pos; }
    const Vec2 &GetPreviousPosition() const { return prevPos; }

    bool GetLeftButtonDown() const { return leftButtonDown; }
    void SetLeftMouseButton(bool state) { this->leftButtonDown = state; }

    bool GetRightMouseButton() const { return rightButtonDown; }
    void SetRightMouseButton(bool state) { this->rightButtonDown = state; }

    void IncreaseCursorSize(float increment);
    float GetCursorSize() const { return cursorSize; }
};

#endif