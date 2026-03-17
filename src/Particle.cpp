#include "Particle.h"

Particle::Particle(int nx, int ny, int ntype) {
  if (ntype == 0) {
    sprite = asw::assets::load_texture("assets/images/money.png");
  }

  if (ntype == 1) {
    sprite = asw::assets::load_texture("assets/images/skull.png");
  }

  if (ntype == 2) {
    sprite = asw::assets::load_texture("assets/images/check.png");
  }

  if (ntype == 3) {
    sprite = asw::assets::load_texture("assets/images/hit.png");
  }

  if (ntype == 4) {
    sprite = asw::assets::load_texture("assets/images/skullBig.png");
  }

  x = nx;
  y = ny;
  type = ntype;
}

void Particle::draw() {
  if (type == 4) {
    asw::draw::sprite(sprite, asw::Vec2<float>(x + 128, y + 64));
  } else {
    asw::draw::sprite(sprite, asw::Vec2<float>(x - 8, y - 8));
  }
}

void Particle::update() {
  y -= 5;
  lifetime++;
}
