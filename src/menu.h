/**
 * MENU
 * A.D.S. Games
 * 06/05/2017
 **/
#pragma once

#include <asw/asw.h>

#include "options.h"
#include "ui/button.h"
#include "state.h"

// Menu
class menu : public asw::scene::Scene<ProgramStates> {
 public:
  using asw::scene::Scene<ProgramStates>::Scene;

  void init() override;
  void update(float dt) override;
  void draw() override;

 private:
  // Images
  asw::Texture splash;
  asw::Texture loading;
  asw::Font menu_font;
};
