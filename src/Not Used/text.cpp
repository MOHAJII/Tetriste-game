#include "text.h"

Text::Text(SDL_Renderer *renderer, const std::string &fontPath, int fontSize, const std::string message, SDL_Color color)
{
    _txtTexture = loadFont(renderer, fontPath, fontSize, message, color);
    SDL_QueryTexture(_txtTexture, nullptr, nullptr, &_txtRect.w, &_txtRect.h);
}
Text::~Text()
{
    SDL_DestroyTexture(_txtTexture);
}
void Text::display(int x, int y, SDL_Renderer *renderer) const
{
    _txtRect.x = x - (_txtRect.w / 25);
    _txtRect.y = y - (_txtRect.h / 4);
    SDL_RenderCopy(renderer, _txtTexture, nullptr, &_txtRect);
}
SDL_Texture *Text::loadFont(SDL_Renderer *renderer, const std::string &fontPath, int fontSize, const std::string message, SDL_Color color)
{

    TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font)
    {
        std::cerr << "error loading fonts\n"
                  << TTF_GetError() << "\n";
    }

    auto txtSurface = TTF_RenderText_Solid(font, message.c_str(), color);

    if (!txtSurface)
    {
        std::cerr << "failed loading text surface\n";
    }
    auto tmpTexture = SDL_CreateTextureFromSurface(renderer, txtSurface);
    if (!tmpTexture)
    {
        std::cerr << "failed loading text texture\n";
    }

    SDL_FreeSurface(txtSurface);
    TTF_CloseFont(font);
    return tmpTexture;
}

int Text::getWidth() const
{
    return _txtRect.w;
}

int Text::getHeight() const
{
    return _txtRect.h;
}
