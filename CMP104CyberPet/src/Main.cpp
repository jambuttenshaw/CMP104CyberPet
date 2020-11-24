#include "Rendering/Renderer.h"
#include "Input/Input.h"
#include "Input/Events.h"
#include "CyberPet.h"

#include <windows.h>
#include <iostream>
#include <vector>
#include <chrono>

void KeyboardCallback(KEY_EVENT_RECORD e)
{
    
}


int main()
{
    // initialize the renderer
    Renderer::Init();
    // create an input handling object
    Input* input = new Input;

    // set the event callback functions
    input->SetKeyEventCallback(KeyboardCallback);

    // create a new cyber pet object
    CyberPet* cyberPet = new CyberPet;

    std::chrono::high_resolution_clock::time_point lastFrameTime = std::chrono::high_resolution_clock::now();

    // main loop
    bool exitLoop = false;
    while (!exitLoop)
    {
        // get the time elapsed between this frame and the previous one
        std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration_cast<std::chrono::seconds>(t - lastFrameTime).count();
        lastFrameTime = t;

        // send the events in the event queue to their callback functions
        input->HandleEvents();
        
        // update
        cyberPet->Update();
        
        // clear everything from the screen
        Renderer::Clear();
        
        // add our pet to the render queue
        Renderer::Queue(cyberPet);

        // draw everything in the queue
        Renderer::DrawAll();
        

        Sleep(30);
    }

    // program shutdown
    delete cyberPet;

    Renderer::Shutdown();
    delete input;

	return 0;
}