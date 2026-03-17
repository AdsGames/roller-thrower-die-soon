#pragma once

#include <string>

#include "UI/UIElement.h"
#include "UI/UIHandler.h"
#include "UI/button.h"
#include "state.h"

#include "game.h"

class Options : public asw::scene::Scene<ProgramStates> {
 public:
  using asw::scene::Scene<ProgramStates>::Scene;

  void init() override;
  void draw() override;
  void update(float dt) override;

 private:
  asw::Font font;
  asw::Font font_big;

  UIHandler OptionsUI;

  asw::Texture cursor;
  asw::Texture background;
  asw::Texture load;
};
