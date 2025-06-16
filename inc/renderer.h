#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

class Renderer {
  public:
    Renderer(const std::string& title, int width, int height);
    ~Renderer();

    bool status() const;
    void clear();
    void present();
    void drawText(const std::string& text, int x, int y, bool highlight = false);
    // :FIXME: drawMenu should not be here. Put in main instead?
    void drawMenu(const std::vector<std::string>& items, int selected);
    // :TODO: add the following methods
    // void drawBackground
    // void drawLine
    // void drawRectangle
    // void drawOblique

  private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    TTF_Font * font;

    int screenWidth, screenHeight;
};

#endif//RENDERER_H
