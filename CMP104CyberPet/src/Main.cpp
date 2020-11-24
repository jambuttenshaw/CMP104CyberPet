#include "Rendering/Renderer.h"
#include "Input/Input.h"
#include "Input/Events.h"
#include "GUI/GUIManager.h"
#include "CyberPet.h"

#include <chrono>
#include <iostream>

void KeyboardCallback(KEY_EVENT_RECORD e)
{

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
    // create an input handling object
    Input* input = new Input;

    // set the event callback functions
    input->SetKeyEventCallback(KeyboardCallback);
    input->SetWindowResizeCallback(WindowResizeCallback);

    // create a guimanager
    GUIManager* guiManager = new GUIManager;
    guiManager->Init();
    Sprite* button = guiManager->GetSprites()[0];

    // create a new cyber pet object
    CyberPet* cyberPet = new CyberPet;

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
        input->HandleEvents();
        
        // update
        cyberPet->Update();
        
        // clear everything from the screen
        Renderer::Clear();
        
        // add our pet to the render queue
        // Renderer::Queue(cyberPet);
        Renderer::Queue(button);

        // draw everything in the queue
        Renderer::DrawAll();
        

        Sleep(30);
    }

    // program shutdown
    delete cyberPet;

    delete guiManager;

    Renderer::Shutdown();
    delete input;

	return 0;
}