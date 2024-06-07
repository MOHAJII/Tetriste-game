#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
class Window
{

public:
    static SDL_Renderer *renderer;

    Window(const char *title, int w, int h);
    ~Window();
    inline bool isClosed() const { return _isClosed; };
    void handleEvents(SDL_Event &);
    void clear();

private:
    std::string _title;
    int _width, _height;
    bool _isClosed;
    SDL_Window *_window;
    SDL_Event event;
    bool init();
};
