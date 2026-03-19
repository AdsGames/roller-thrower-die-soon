/**
 * MENU
 * A.D.S. Games
 * 06/05/2017
 **/
#pragma once

#include <asw/asw.h>

#include "state.h"

// Menu
class Menu : public asw::scene::Scene<ProgramStates> {
 public:
  using asw::scene::Scene<ProgramStates>::Scene;

  void init() override;
  void update(float dt) override;
  void draw() override;

 private:
  asw::ui::Root _ui_root;
};
