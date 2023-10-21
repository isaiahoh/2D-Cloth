#include "Application.h"
#include "./Physics/Constants.h"
#include "./Physics/Force.h"

bool Application::IsRunning()
{
    return running;
}

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup()
{
    mouse = new Mouse();
    running = Graphics::OpenWindow();

    int clothWidth = 100;
    int clothHeight = 50;
    int clothSpacing = 10;

    int startX = Graphics::Width() * 0.5f - clothWidth * clothSpacing * 0.5f;
    int startY = Graphics::Height() * 0.1f;

    cloth = new Cloth(clothWidth, clothHeight, clothSpacing, startX, startY);
}

///////////////////////////////////////////////////////////////////////////////
// Input processing
///////////////////////////////////////////////////////////////////////////////
void Application::Input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            break;
        case SDL_KEYUP:
            break;
        case SDL_MOUSEMOTION:
        {
            int x = event.motion.x;
            int y = event.motion.y;
            mouse->UpdatePosition(x, y);
        }
        break;
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            mouse->UpdatePosition(x, y);

            if (!mouse->GetLeftButtonDown() && event.button.button == SDL_BUTTON_LEFT)
            {
                mouse->SetLeftMouseButton(true);
            }
            if (!mouse->GetRightMouseButton() && event.button.button == SDL_BUTTON_RIGHT)
            {
                mouse->SetRightMouseButton(true);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (mouse->GetLeftButtonDown() && event.button.button == SDL_BUTTON_LEFT)
            {
                mouse->SetLeftMouseButton(false);
            }
            if (mouse->GetRightMouseButton() && event.button.button == SDL_BUTTON_RIGHT)
            {
                mouse->SetRightMouseButton(false);
            }
            break;
        case SDL_MOUSEWHEEL:
            if (event.wheel.y > 0)
            {
                mouse->IncreaseCursorSize(10);
            }
            else if (event.wheel.y < 0)
            {
                mouse->IncreaseCursorSize(-10);
            }
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Update function (called several times per second to update objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Update()
{
    // Wait some time until the reach the target frame time in milliseconds
    static int timePreviousFrame;
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
    if (timeToWait > 0)
        SDL_Delay(timeToWait);

    // Calculate the deltatime in seconds
    float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.0f;
    if (deltaTime > 0.016)
        deltaTime = 0.016;

    // Update Cloth
    cloth->Update(mouse, deltaTime);

    // Set the time of the current frame to be used in the next one
    timePreviousFrame = SDL_GetTicks();
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render()
{
    Graphics::ClearScreen(0xFF000816);
    cloth->Draw();
    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy()
{
    Graphics::CloseWindow();
    delete cloth;
}
