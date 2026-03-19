#pragma once

#include <asw/asw.h>

enum class ParticleType {
  Coin = 0,
  Death = 1,
  Rescue = 2,
  Hit = 3,
  EnemyDeath = 4,
};

class Particle {
 public:
  Particle(const asw::Vec2f& position, ParticleType type);

  void update(float dt);
  void draw() const;
  bool is_dead() const { return lifetime_s > MAX_LIFE_S; }

 private:
  constexpr static float MAX_LIFE_S = 2.0F;
  constexpr static float PIXELS_PER_SECOND = 50.0F;

  asw::Texture sprite;
  asw::Vec2f position;
  ParticleType type;
  float lifetime_s{0};
};
