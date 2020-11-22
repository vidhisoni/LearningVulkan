#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_vulkan.h>

#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

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
    const uint32_t SCREEN_WIDTH = 800;
    const uint32_t SCREEN_HEIGHT = 600;

    SDL_Window* window = NULL;

    //Main loop flag
    bool quit = false;

    VkInstance instance = VK_NULL_HANDLE;

private:
    void initWindow()
    {
        //The window we'll be rendering to
        window = NULL;

        //The surface contained by the window
        SDL_Surface* screenSurface = NULL;

        uint32_t flags = SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE;
        //Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() <<"\n";
        }
        else
        {
            //Create window
            window = SDL_CreateWindow("Vulkan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
            if (window == NULL)
            {
                std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
            }
        }
    }

    void initVulkan() 
    {
        createInstance();
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
        vkDestroyInstance(instance, nullptr);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void createInstance()
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        uint32_t sdlExtensionCount = 0;
        const char** sdlExtensions = NULL;

        sdlGetRequiredInstanceExtensions(&sdlExtensionCount, &sdlExtensions);

        createInfo.enabledExtensionCount = sdlExtensionCount;
        createInfo.ppEnabledExtensionNames = sdlExtensions;
        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create instance");
        }
    }

    void sdlGetRequiredInstanceExtensions(uint32_t* pExtensionCount, const char*** pExtensionNames)
    {
        if (!SDL_Vulkan_GetInstanceExtensions(NULL, pExtensionCount, NULL))
        {
            std::cout << "SDL could not return all the required extensions. SDL_Error: " << SDL_GetError() << "\n";
        }
        *pExtensionNames = (const char**)malloc(sizeof(const char*) * (*pExtensionCount));
        if (!SDL_Vulkan_GetInstanceExtensions(window, pExtensionCount, *pExtensionNames))
        {
            std::cout << "SDL could not return all the required extensions. SDL_Error: " << SDL_GetError() << "\n";
        }
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