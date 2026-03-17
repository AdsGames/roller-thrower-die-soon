/*
 * Main
 * This is the main for Jumping Jimothy
 * Calls state machine update and draw functions
 * 09/05/2017
 */
#include <asw/asw.h>

#include "LevelFinish.h"
#include "game.h"
#include "init.h"
#include "menu.h"
#include "state.h"

#include "Options.h"

// Start here
int main(int argc, char** argv) {
  // Basic init
  asw::core::init(1920, 1080, 1);

  // Starts Game
  auto app = asw::scene::SceneManager<ProgramStates>();
  app.register_scene<Init>(ProgramStates::Init, app);
  app.register_scene<game>(ProgramStates::Game, app);
  app.register_scene<menu>(ProgramStates::Menu, app);
  app.register_scene<Options>(ProgramStates::Options, app);
  app.register_scene<LevelFinish>(ProgramStates::LevelFinish, app);
  app.set_next_scene(ProgramStates::Init);
  app.start();

  return 0;
}
