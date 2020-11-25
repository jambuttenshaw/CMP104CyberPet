#include "Rendering/Renderer.h"
#include "Input/Input.h"
#include "Input/Events.h"
#include "GameManager.h"

#include <chrono>
#include <iostream>

// game manager needs to be global scope so we can create wrapper functions for event handling
GameManager* gameManager;


void KeyEventCallback(KEY_EVENT_RECORD e)
{
    gameManager->OnKeyEvent(e);
}

// when the console window gets resized we want to update the renderer
// to store the new dimensions of the console
void WindowResizeCallback(WINDOW_BUFFER_SIZE_RECORD e)
{
    Renderer::UpdateConsoleDimensions(e.dwSize.X, e.dwSize.Y);
}


int main()
{
    // initialize the renderer
    Renderer::Init();
    // initialize the input handler
    Input::Init();

    // create a guimanager
    GameManager* gameManager = new GameManager;

    // set the event callback functions
    Input::SetKeyEventCallback(KeyEventCallback);
    Input::SetWindowResizeCallback(WindowResizeCallback);


    // used to calculate the difference in time between this frame and the previous one: the delta time
    // this is used to make sure that everything that happens in-game is frame-rate independent
    std::chrono::high_resolution_clock::time_point lastFrameTime = std::chrono::high_resolution_clock::now();

    // main loop
    bool exitLoop = false;
    while (!exitLoop)
    {
        // get the time elapsed between this frame and the previous one
        std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(t - lastFrameTime).count() * 0.001;
        lastFrameTime = t;

        // send the events in the event queue to their callback functions
        Input::HandleEvents();
        /*
        // clear everything from the screen
        Renderer::Clear();
        
        // add our pet to the render queue
        for (Sprite* s : gameManager->GetSprites())
        {
            Renderer::Queue(s);
        }

        // draw everything in the queue
        Renderer::DrawAll();
        
        */

        Sleep(30);
    }

    delete gameManager;

    Renderer::Shutdown();
    Input::Shutdown();

	return 0;
}