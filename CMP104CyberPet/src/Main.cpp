#include "Rendering/Renderer.h"
#include "Input/Input.h"
#include "GameManager.h"

// used for keeping track of time passing
#include <chrono>

// when the console window gets resized we want to update the renderer
// to store the new dimensions of the console
void WindowResizeCallback(WINDOW_BUFFER_SIZE_RECORD* e)
{
    // send the new console dimensions to the renderer
    Renderer::UpdateConsoleDimensions(e->dwSize.X, e->dwSize.Y);
}

// the main function
int main()
{
    // initialize the renderer
    Renderer::Init();
    // initialize the input system
    Input::Init();

    // set the event callback for window resize events
    Input::SetEventCallback(WindowResizeCallback);


    // create a game manager
    // most of the game setup is then handled within the game manager
    GameManager* gameManager = new GameManager;


    // used to calculate the difference in time between this frame and the previous one: the delta time
    // this is used to make sure that everything that happens in-game is frame-rate independent
    // initialize it with the current time
    std::chrono::high_resolution_clock::time_point lastFrameTime = std::chrono::high_resolution_clock::now();

    // main loop
    // bool to keep track of when to exit
    bool exitLoop = false;
    while (!exitLoop)
    {
        // get the time elapsed between this frame and the previous one
        // referenced from https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
        std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
        // we want the precision of the time measurement to be in milliseconds, but we want to represent it in seconds
        // thus why we multiply by 0.001 to convert to seconds, but still have that millisecond precision
        float deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(t - lastFrameTime).count() * 0.001f;
        // update the last frame time to the time of this frame
        lastFrameTime = t;

        // send the events in the event queue to their callback functions
        Input::HandleEvents();

        // update everything in the game
        gameManager->Update(deltaTime);

        
        // clear everything from the screen
        Renderer::Clear();

        // game manager draw to display
        // sends everything that needs drawn into the queue
        gameManager->Draw();

        // draw everything in the queue
        Renderer::DrawAll();
        

        // check to see if we need to quit the game
        exitLoop = gameManager->TestQuitGame();

        // slow the program down a bit, to stop the screen from flashing so much
        // which is an annoying side effect of using the console for realtime graphics
        Sleep(30);
    }

    // clear the screen one last time before quitting
    Renderer::Clear();

    // delete the game manager
    // this will all the game objects from memory
    delete gameManager;


    // shutdown the renderer and input systems
    Renderer::Shutdown();
    Input::Shutdown();

    // and finally leave the program
	return 0;
}