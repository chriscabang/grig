#include "renderer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

Renderer::Renderer(const std::string& title, int width, int height)
  : renderer(nullptr),
    window(nullptr),
    font(nullptr),
    screenWidth(width),
    screenHeight(height) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
    exit(1);
  }

  if (TTF_Init() != 0) {
    std::cerr << "TTF could not be initialized! SDL_ttf Error: " << TTF_GetError() << std::endl;
    exit(1);
  }

  window = SDL_CreateWindow(title.c_str(),
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            screenWidth, screenHeight,
                            SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    exit(1);
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    exit(1);
  }

  font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 24);
  if (!font) {
    std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    exit(1);
  }
}

Renderer::~Renderer() {
  if (font)     TTF_CloseFont(font);
  if (renderer) SDL_DestroyRenderer(renderer);
  if (window)   SDL_DestroyWindow(window);

  TTF_Quit();
  SDL_Quit();
}

bool Renderer::status() const {
  return (renderer != nullptr);
}

void Renderer::clear() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void Renderer::present() {
  SDL_RenderPresent(renderer);
}

void Renderer::drawText(const std::string& text, int x, int y, bool highlight) {
  SDL_Color color = highlight ? SDL_Color{ 100, 255, 100, 255 } : SDL_Color { 255, 255, 255, 255 };
  SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_Rect rect = { x, y, surface->w, surface->h };
  SDL_RenderCopy(renderer, texture, nullptr, &rect);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void Renderer::drawMenu(const std::vector<std::string>& items, int selected) {
  clear();
  int y = 50;
  for (size_t i = 0; i < items.size(); ++i) {
    drawText(items[i], 40, y, static_cast<int>(i) == selected);
    y += 30;
  }
  present();
}

