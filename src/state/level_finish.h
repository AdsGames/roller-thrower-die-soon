#pragma once

#include <asw/asw.h>

#include "../level_config.h"

#include "game.h"
#include "state.h"

class LevelFinish : public asw::scene::Scene<ProgramStates> {
 public:
  using asw::scene::Scene<ProgramStates>::Scene;

  void init() override;
  void draw() override;
  void update(float dt) override;

 private:
  asw::ui::Root _ui;
  LevelConfig _config;

  asw::Font _font;
  asw::Font _font_big;
  asw::Font _font_extra_thicc;
};
