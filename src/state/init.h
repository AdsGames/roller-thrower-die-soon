/**
 * INIT
 * Allan Legemaate
 * 09/05/2017
 **/
#pragma once

#include <asw/asw.h>

#include "state.h"

class Init : public asw::scene::Scene<ProgramStates> {
 public:
  using asw::scene::Scene<ProgramStates>::Scene;

  void update(float dt) override;

 private:
  asw::Music _game_music;
};
