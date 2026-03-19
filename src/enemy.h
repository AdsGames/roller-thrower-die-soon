#pragma once

#include <asw/asw.h>

class Enemy {
 public:
  Enemy(const asw::Vec2f& pos);

  // Run any logic needed by enemy
  void update(float dt);

  // Draw enemy to screen
  void draw() const;

  // Applys a variable amount of damage to enemy
  void apply_damage(int amount);

  int get_health() const { return _health; }

  const asw::Quadf& get_transform() const { return _transform; }

 private:
  constexpr static float FRAMES_PER_SECOND = 50;

  // Images
  asw::Texture _sprite;
  asw::Texture _spritesheet[62];
  asw::Font _font;

  // Position
  asw::Quadf _transform;

  // Animation
  float _frame_timer = 0;

  // Hit points
  int _health = 1000;
};
