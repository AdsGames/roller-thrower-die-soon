#pragma once

#include <asw/asw.h>

#include "tools.h"

class Particle {
 public:
  Particle(int x, int y, int type);

  void update();
  void draw();
  bool is_dead() const { return lifetime > 60; }

 private:
  asw::Texture sprite;
  int x;
  int y;
  int lifetime = 0;
  int type = 1;
};
