#include <memory>

#include "spdlog/spdlog.h"

#include "Game.h"
#include "config.h"

WindowSize windowSize = { 800, 800 };

int main(int argc, char *args[]) {
  (void)argc;
  (void)args;

#ifdef DEBUG
  // set the log level to debug if compiling in Debug mode
  spdlog::set_level(spdlog::level::debug);
#endif // DEBUG

  // create a game instance
  std::unique_ptr<Game> game(new Game());

  // initialise game
  if (!game->Init(PROJECT_NAME, windowSize)) {
    return EXIT_FAILURE;
  }

  // run the game loop
  game->Start();

  return EXIT_SUCCESS;
}

