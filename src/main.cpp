/*
 * Main
 * This is the main for Roller Thrower Die Soon, it initializes the game and
 * starts the main loop. Calls state machine update and draw functions
 * 09/05/2017
 */
#include <asw/asw.h>

#include "state/game.h"
#include "state/init.h"
#include "state/level_finish.h"
#include "state/menu.h"
#include "state/options.h"
#include "state/state.h"

// Start here
int main(int argc, char** argv) {
  // Basic init
  asw::core::init(1920, 1080, 1);

  // Starts Game
  auto app = asw::scene::SceneManager<ProgramStates>();
  app.register_scene<Init>(ProgramStates::Init, app);
  app.register_scene<Menu>(ProgramStates::Menu, app);
  app.register_scene<Options>(ProgramStates::Options, app);
  app.register_scene<Game>(ProgramStates::Game, app);
  app.register_scene<LevelFinish>(ProgramStates::LevelFinish, app);
  app.set_next_scene(ProgramStates::Init);
  app.start();

  return 0;
}
