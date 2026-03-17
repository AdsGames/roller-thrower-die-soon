#include "particle.h"

#include <cmath>

Particle::Particle(const asw::Vec2<float>& position, ParticleType type)
    : position(position), type(type) {
  switch (type) {
    case ParticleType::Coin:
      sprite = asw::assets::load_texture("assets/images/money.png");
      break;
    case ParticleType::Death:
      sprite = asw::assets::load_texture("assets/images/skull.png");
      break;
    case ParticleType::Rescue:
      sprite = asw::assets::load_texture("assets/images/check.png");
      break;
    case ParticleType::Hit:
      sprite = asw::assets::load_texture("assets/images/hit.png");
      break;
    case ParticleType::EnemyDeath:
      sprite = asw::assets::load_texture("assets/images/skullBig.png");
      break;
  }
}

void Particle::draw() const {
  if (type == ParticleType::EnemyDeath) {
    asw::draw::sprite(sprite, position + asw::Vec2<float>(128, 64));
  } else {
    asw::draw::sprite(sprite, position - asw::Vec2<float>(8, 8));
  }
}

void Particle::update(float dt) {
  lifetime_s += dt;
  position.y -= PIXELS_PER_SECOND * dt;
  position.x += std::sinf(lifetime_s * 10.0F) * 5.0F * dt;

  asw::draw::set_alpha(sprite, 1.0F - (lifetime_s / MAX_LIFE_S));
}
