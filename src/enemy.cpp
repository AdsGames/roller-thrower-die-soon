#include "enemy.h"

Enemy::Enemy(int x, int y) {
  sprite = asw::assets::load_texture("assets/images/flail.png", "flail");
  font = asw::assets::load_font("assets/font/font.ttf", 32, "font");

  for (int i = 0; i < 8; i++) {
    for (int t = 0; t < 8; t++) {
      const int index = t + (i * 8);

      if (index < 62) {
        spritesheet[index] = asw::assets::create_texture(498, 297);
        asw::display::set_render_target(spritesheet[index]);
        asw::draw::stretch_sprite_blit(
            sprite, asw::Quad<float>(t * 498, i * 297, 498, 297),
            asw::Quad<float>(0, 0, 498, 297));
        asw::display::reset_render_target();
      }
    }
  }

  const int bigx = x * 64;
  const int bigy = y * 64;

  this->x = (bigx - bigy);
  this->y = (bigx + bigy) / 2;
}

void Enemy::applyDamage(int amount) {
  health -= amount;
  health = std::max(health, 0);
}

void Enemy::update() {
  frame = (frame + 1) % 62;
}

void Enemy::draw() const {
  asw::draw::sprite(spritesheet[frame], asw::Vec2<float>(x, y));
  asw::draw::text(font, std::format("HP:{}", health),
                  asw::Vec2<float>(x + 200, y - 50), asw::color::red);
}
