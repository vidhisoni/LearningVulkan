#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_vulkan.h>

#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>


const uint32_t SCREEN_WIDTH = 800;
const uint32_t SCREEN_HEIGHT = 600;

class HelloTriangleApplication 
{
public:
    void run() 
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    SDL_Window* window = NULL;

    //Main loop flag
    bool quit = false;

private:
    void initWindow()
    {
        //The window we'll be rendering to
        window = NULL;

        //The surface contained by the window
        SDL_Surface* screenSurface = NULL;

        //Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "SDL could not initialize! SDL_Error: %s\n" << SDL_GetError();
        }
        else
        {
            //Create window
            window = SDL_CreateWindow("Vulkan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            if (window == NULL)
            {
                std::cout << "Window could not be created! SDL_Error: %s\n" << SDL_GetError();
            }
        }
    }

    void initVulkan() 
    {

    }

    void mainLoop() 
    {
        //Event handler
        SDL_Event e;
        //While application is running
        while (!quit)
        {//Handle events on queue
            while (SDL_PollEvent(&e) != 0)
            {
                //User requests quit
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
        }
    }

    void cleanup() 
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

int main() 
{
    HelloTriangleApplication app;

    try 
    {
        app.run();
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}