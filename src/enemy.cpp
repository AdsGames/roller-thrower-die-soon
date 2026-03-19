#include "enemy.h"

Enemy::Enemy(const asw::Vec2f& pos) {
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

  const int bigx = pos.x * 64;
  const int bigy = pos.y * 64;

  _transform.position.x = (bigx - bigy);
  _transform.position.y = (bigx + bigy) / 2;
  _transform.size.x = 498;
  _transform.size.y = 297;
}

void Enemy::apply_damage(int amount) {
  _health -= amount;
  _health = std::max(_health, 0);
}

void Enemy::update(float dt) {
  _frame_timer += dt;
}

void Enemy::draw() const {
  const int frame = static_cast<int>(_frame_timer * FRAMES_PER_SECOND) % 62;

  asw::draw::sprite(_spritesheet[frame], _transform.position);
  asw::draw::text(_font, std::format("HP:{}", _health),
                  _transform.position + asw::Vec2f(200, -50), asw::color::red);
}
