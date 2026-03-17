#pragma once

#include <asw/asw.h>

#include "UI/UIElement.h"
#include "UI/UIHandler.h"
#include "UI/button.h"

#include "game.h"
#include "state.h"

class LevelFinish : public asw::scene::Scene<ProgramStates> {
 public:
  using asw::scene::Scene<ProgramStates>::Scene;

  void init() override;
  void draw() override;
  void update(float dt) override;

 private:
  UIHandler LevelFinishUI;

  asw::Font font;
  asw::Font font_big;
  asw::Font font_extra_thicc;
};
