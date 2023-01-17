#pragma once

#include <memory>

#include "SDL.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

struct WindowSize {
  int width, height;
};

class Game {
public:
  // Game constructor and destructor
  Game();
  ~Game();

  // Game Initialization function
  bool Init(const char *title, WindowSize windowSize);

  // Start the game
  void Start();

  // Stop the game loop
  void Stop();

private:
  std::shared_ptr<spdlog::logger> m_logger;

  bool m_isRunning;
  SDL_Event m_event;

  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
};

