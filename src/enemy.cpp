#include "enemy.h"

Enemy::Enemy(int x, int y) {
  _sprite = asw::assets::load_texture("assets/images/flail.png", "flail");
  _font = asw::assets::load_font("assets/font/font.ttf", 32, "font");

  for (int i = 0; i < 8; i++) {
    for (int t = 0; t < 8; t++) {
      const int index = t + (i * 8);

      if (index < 62) {
        _spritesheet[index] = asw::assets::create_texture(498, 297);
        asw::display::set_render_target(_spritesheet[index]);
        asw::draw::stretch_sprite_blit(_sprite,
                                       asw::Quadf(t * 498, i * 297, 498, 297),
                                       asw::Quadf(0, 0, 498, 297));
        asw::display::reset_render_target();
      }
    }
  }

  const int bigx = x * 64;
  const int bigy = y * 64;

  _x = (bigx - bigy);
  _y = (bigx + bigy) / 2;
}

void Enemy::apply_damage(int amount) {
  _health -= amount;
  _health = std::max(_health, 0);
}

void Enemy::update() {
  _frame = (_frame + 1) % 62;
}

void Enemy::draw() const {
  asw::draw::sprite(_spritesheet[_frame], asw::Vec2f(_x, _y));
  asw::draw::text(_font, std::format("HP:{}", _health),
                  asw::Vec2f(_x + 200, _y - 50), asw::color::red);
}
