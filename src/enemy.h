#pragma once

#include <asw/asw.h>

class Enemy {
 public:
  Enemy(int x, int y);

  // Run any logic needed by enemy
  void update();

  // Draw enemy to screen
  void draw() const;

  // Applys a variable amount of damage
  // to enemy
  void apply_damage(int amount);

  // Getters for position
  float get_x() const { return _x; }
  float get_y() const { return _y; }
  asw::Vec2f get_position() const { return asw::Vec2f(_x, _y); }
  int get_health() const { return _health; }

 private:
  // Images
  asw::Texture _sprite;
  asw::Texture _spritesheet[62];
  asw::Font _font;

  // Position
  int _x;
  int _y;

  // Animation
  int _frame = 0;

  // Hit points
  int _health = 1000;
};
