#pragma once

#include <string>
#include <vector>

#include "../level_config.h"
#include "game.h"
#include "state.h"

class Options : public asw::scene::Scene<ProgramStates> {
 public:
  using asw::scene::Scene<ProgramStates>::Scene;

  void init() override;
  void draw() override;
  void update(float dt) override;

 private:
  asw::ui::Root _ui;
};
