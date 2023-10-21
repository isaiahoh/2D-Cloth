#include <math.h>
#include "Stick.h"
#include "Point.h"
#include "./Physics/Vec2.h"
#include "Graphics.h"

Stick::Stick(Point &p0, Point &p1, float length) : p0(p0), p1(p1), length(length) {}

void Stick::Update(Mouse *mouse)
{
    if (!isActive)
    {
        return;
    }

    Vec2 p0Pos = p0.GetPosition();
    Vec2 p1Pos = p1.GetPosition();

    this->SetIsSelected(p0.checkIfSelected() || p1.checkIfSelected());

    if (mouse->GetRightMouseButton() && isSelected)
    {
        this->Break();
    }

    Vec2 diff = p0Pos - p1Pos;
    float dist = sqrtf(diff.x * diff.x + diff.y * diff.y);
    float diffFactor = (length - dist) / dist;
    Vec2 offset = diff * diffFactor * 0.5f;

    p0.SetPosition(p0Pos.x + offset.x, p0Pos.y + offset.y);
    p1.SetPosition(p1Pos.x - offset.x, p1Pos.y - offset.y);
}

void Stick::Draw() const
{
    if (!isActive)
    {
        return;
    }

    Vec2 p0Pos = p0.GetPosition();
    Vec2 p1Pos = p1.GetPosition();

    Graphics::DrawLine(p0Pos.x, p0Pos.y, p1Pos.x, p1Pos.y, isSelected ? colorWhenSelected : color);
}

void Stick::Break()
{
    isActive = false;
}

void Stick::SetIsSelected(bool value)
{
    isSelected = value;
}