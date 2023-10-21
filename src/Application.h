#ifndef APPLICATION_H
#define APPLICATION_H

#include "./Graphics.h"
#include "./Physics/Particle.h"
#include "Mouse.h"
#include "Cloth.h"
#include <vector>

class Application
{
private:
    Mouse *mouse = nullptr;
    Cloth *cloth = nullptr;
    bool running = false;

public:
    Application() = default;
    ~Application() = default;
    bool IsRunning();
    void Setup();
    void Input();
    void Update();
    void Render();
    void Destroy();
};

#endif
