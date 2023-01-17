#include "config.h"
#include "Game.h"

Game::Game(): m_logger{ spdlog::stdout_color_st("Game") }, m_window(nullptr), m_renderer(nullptr), m_isRunning(false), m_event() {}

bool Game::Init(const char *title, WindowSize windowSize)
{
  m_logger->info("VERSION {0:d}.{1:d}.{2:d}", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

  // Initialise the SDL Video Subsystem
  if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
  {
    m_logger->error("SDL couldn't be initialised!");
    m_logger->error("SDL Error: {}", SDL_GetError());
    return false;
  }

  m_logger->debug("Video Subsystem initialised!");

  // Create window
  Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
  m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSize.width, windowSize.height, windowFlags);

  // Check if the window initialised properly
  if (!m_window) {
    m_logger->error("Window couldn't be created!");
    m_logger->error("SDL Error: {}", SDL_GetError());
    return false;
  }

  m_logger->debug("SDL Window created!");

  // Create a renderer context
  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

  // Check if the renderer initialised properly
  if (!m_renderer) {
    m_logger->error("Failed to create renderer context!");
    m_logger->error("SDL Error: {}", SDL_GetError());
    return false;
  }

  m_logger->debug("SDL render context created!");

  return true;
}

void Game::Start() {
  // set the isRunning to true
  m_isRunning = true;
  m_logger->debug("Starting the game loop!");

  // wait for sdl events
  while (m_isRunning && SDL_WaitEvent(&m_event)) {
    switch (m_event.type) {
      case SDL_QUIT:
        Stop();
        break;

      default:
        break;
    }
  }
}

void Game::Stop() {
  m_logger->debug("Stopping the game loop!");
  m_isRunning = false;
}

Game::~Game() {
  m_isRunning = false;

 if (m_renderer) {
    SDL_DestroyRenderer(m_renderer);
    m_logger->debug("SDL render context destroyed!");
  }

  if (m_window) {
    SDL_DestroyWindow(m_window);
    m_logger->debug("SDL window instance destroyed!");
  }

  // Quit SDL
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
  SDL_Quit();

  m_logger->debug("Shutdown SDL. Cleaned up all game resources!");
}

