#include "window.h"

Window::Window(const char *title, int w, int h) : _title(title), _width(w), _height(h)
{
    _isClosed = !init();
}

Window::~Window()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
}

SDL_Renderer *Window::renderer = nullptr;

void Window::handleEvents(SDL_Event &event)
{

    switch (event.type)
    {
    case SDL_QUIT:
        _isClosed = true;
        break;
    default:
        break;
    }
}

void Window::clear()
{
    SDL_SetRenderDrawColor(renderer, 157, 153, 255, 255);
    SDL_RenderClear(renderer);
    // SDL_RenderPresent(renderer);
}

bool Window::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "failed to initialize SDL";
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) != 2)
    {
        std::cerr << "failed to initialize PNG IMG";
        return false;
    }
    if (TTF_Init() == -1)
    {
        std::cerr << "failed to initialize font";
        return false;
    }

    _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(_window, -1, 0);
    if (!_window)
    {
        std::cerr << "failed to create window";
        return false;
    }

    if (!renderer)
    {
        std::cerr << "failed to create renderer";
        return false;
    }
    return true;
}
