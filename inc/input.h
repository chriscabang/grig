#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <memory>

class Input {
  public:
    virtual ~Input() = default; 
    virtual void handle(const SDL_Event& event, int& index, int count, bool& running);
    void next(std::shared_ptr<Input> handler);

  protected:
    std::shared_ptr<Input> __next = nullptr;
};

class Keyboard : public Input {
  public:
    void handle(const SDL_Event& event, int& index, int count, bool& running) override;
};

#endif//INPUT_H
