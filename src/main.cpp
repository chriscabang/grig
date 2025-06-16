#include <iostream>
#include <vector>
#include <filesystem>
#include <string.h>
#include <SDL2/SDL.h>

#include "renderer.h"
#include "input.h"

int main(int argc, char* argv[]) {
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 480;
  const std::string WINDOW_TITLE = "p1";

  Renderer renderer(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
  if (!renderer.status()) {
    std::cerr << "Failed to initialize renderer.\n";
    return 1;
  }

  std::shared_ptr<Input> input = std::make_shared<Keyboard>();

  std::vector<std::string> games = {
    "SNES: Chrono Trigger",
    "NES : Super Mario Bros",
    "GB  : Pokemon Red"
  };

  int count = static_cast<int>(games.size());
  int selected = 0;
  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      // } else if (event.type == SDL_KEYDOWN) {
      //   switch (event.key.keysym.sym) {
      //     case SDLK_DOWN:
      //       selected = (selected + 1) % games.size(); break;
      //     case SDLK_UP:
      //       selected = (selected - 1 + games.size()) % games.size(); break;
      //     case SDLK_RETURN:
      //       std::cout << "Launching: " << games[selected] << "\n"; break;
      //     case SDLK_ESCAPE:
      //       running = false; break;
      //   }
      // }
      } else {
        input->handle(event, selected, count, running);
      }
    }
    renderer.drawMenu(games, selected);
    SDL_Delay(16);
  }

  return 0;
}
