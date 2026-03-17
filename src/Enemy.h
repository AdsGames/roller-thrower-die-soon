#pragma once

#include <asw/asw.h>

#include "tools.h"

class Enemy {
 public:
  Enemy(int x, int y);

  // Run any logic needed by enemy
  void update();

  // Draw enemy to screen
  void draw() const;

  // Applys a variable amount of damage
  // to enemy
  void applyDamage(int amount);

  // Getters for position
  int getX() const { return x; }
  int getY() const { return y; }
  int getHealth() const { return health; }

 private:
  // Images
  asw::Texture sprite;
  asw::Texture spritesheet[62];
  asw::Font font;

  // Position
  int x;
  int y;

  // Animation
  int frame = 0;

  // Hit points
  int health = 1000;
};
