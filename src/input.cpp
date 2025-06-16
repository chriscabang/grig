#include "input.h"
#include <iostream>

void Input::next(std::shared_ptr<Input> handler) {
  __next = handler;
}

void Input::handle(const SDL_Event& event, int& index, int count, bool& running) {
  if (__next) {
    __next->handle(event, index, count, running);
  }
}

void Keyboard::handle(const SDL_Event& event, int& index, int count, bool& running) {
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_DOWN:
        index = (index + 1) % count; break;
      case SDLK_UP:
        index = (index - 1 + count) % count; break;
      case SDLK_ESCAPE:
        running = false; break;
      default: break;
    }
  } else {
    Input::handle(event, index, count, running);
  }
}
