#include "guest.h"

#include <array>
#include <cmath>
#include <format>

float Guest::speed = 30.0f;

namespace {
std::array<std::string, 50> NAMES = {
    "Ethel",    "Chung",     "Fe",        "Brooke",    "Nicky",    "Gail",
    "Andrea",   "Sigrid",    "Carmon",    "Marybelle", "Racquel",  "Dottie",
    "Wilson",   "Myra",      "Jackeline", "Vonda",     "Stacey",   "Jacquelynn",
    "Phebe",    "Madeline",  "Miguelina", "Loretta",   "Malissa",  "Kandy",
    "Nancee",   "Petronila", "Madelaine", "Shakira",   "Jamika",   "Quentin",
    "Shanell",  "Adrian",    "Clement",   "Gus",       "Hung",     "Tamie",
    "Elidia",   "Jeneva",    "Shantel",   "Sage",      "Susann",   "Coralie",
    "Alphonso", "Stephanie", "Gena",      "Barbera",   "Jesusita", "Donald",
    "Danno",    "Allan"};

std::array<std::string, 26> INITIALS = {
    "Q.", "W.", "E.", "R.", "T.", "Y.", "U.", "I.", "O.",
    "P.", "A.", "S.", "D.", "F.", "G.", "H.", "J.", "K.",
    "L.", "Z.", "X.", "C.", "V.", "B.", "N.", "M."};

std::array<asw::Texture, 43> spritesheet;
std::array<asw::Texture, 25> spritesheet_panic;
bool spritesheets_loaded = false;

void load_spritesheets() {
  if (spritesheets_loaded) {
    return;
  }

  spritesheets_loaded = true;

  const auto sprite_walk =
      asw::assets::load_texture("assets/images/walk.png", "guest_walk");

  for (int i = 0; i < spritesheet.size(); i++) {
    spritesheet[i] = asw::assets::create_texture(17, 36);
    asw::display::set_render_target(spritesheet[i]);
    asw::draw::stretch_sprite_blit(sprite_walk, asw::Quadf(0, i * 38, 17, 38),
                                   asw::Quadf(0, 0, 17, 38));
    asw::display::reset_render_target();
  }

  const auto sprite_panic =
      asw::assets::load_texture("assets/images/panic.png", "guest_panic");

  for (int i = 0; i < spritesheet_panic.size(); i++) {
    spritesheet_panic[i] = asw::assets::create_texture(17, 36);
    asw::display::set_render_target(spritesheet_panic[i]);
    asw::draw::stretch_sprite_blit(sprite_panic, asw::Quadf(0, i * 36, 17, 36),
                                   asw::Quadf(0, 0, 17, 38));
    asw::display::reset_render_target();
  }
}

}  // namespace

Guest::Guest(const asw::Vec2f& position) : _position(position) {
  _umbrella =
      asw::assets::load_texture("assets/images/Umbrella.png", "guest_umbrella");
  _name = NAMES[asw::random::between(0, NAMES.size())];
  _inital = INITIALS[asw::random::between(0, INITIALS.size())];

  load_spritesheets();
}

void Guest::update(float dt) {
  _frame_counter += dt;

  // Walking logic
  if (_velocity.x == 0 && _velocity.y == 0) {
    if (_direction == Direction::East) {
      _position.x += speed * dt;
      _position.y -= 0.5F * speed * dt;
    }

    if (_direction == Direction::South) {
      _position.x += speed * dt;
      _position.y += 0.5F * speed * dt;
    }

    if (_direction == Direction::West) {
      _position.x -= speed * dt;
      _position.y += 0.5F * speed * dt;
    }

    if (_direction == Direction::North) {
      _position.x -= speed * dt;
      _position.y -= 0.5F * speed * dt;
    }
  } else {
    // Throwing logic
    if (_velocity.x > -MIN_VELOCITY && _velocity.x < MIN_VELOCITY) {
      _velocity.x = 0;
    } else {
      _velocity.x *= std::pow(DECELERATION_FACTOR, dt);
    }

    if (_velocity.y > -MIN_VELOCITY && _velocity.y < MIN_VELOCITY) {
      _velocity.y = 0;
    } else {
      _velocity.y *= std::pow(DECELERATION_FACTOR, dt);
    }

    _position += _velocity;
  }
}

void Guest::draw() const {
  const auto total_frame = static_cast<int>(_frame_counter * FRAMES_PER_S);

  if (!_captured) {
    const auto frame = total_frame % spritesheet.size();
    asw::draw::sprite(spritesheet[frame], _position - asw::Vec2f(8, 18));
  } else {
    const auto frame_panic = total_frame % spritesheet_panic.size();
    asw::draw::sprite(spritesheet_panic[frame_panic],
                      _position - asw::Vec2f(10, 18));
  }

  if (_has_umbrella) {
    asw::draw::sprite(_umbrella, _position + asw::Vec2f(3, -20));
  }

  asw::draw::circle(get_position(), 4, asw::color::red);
}

asw::Vec2f Guest::get_position() const {
  return asw::Vec2f(_position.x, _position.y + 12);
}

void Guest::set_position(const asw::Vec2f& pos) {
  _position = pos;
}

void Guest::set_velocity(const asw::Vec2f& v) {
  _velocity = v;
}

const asw::Vec2f& Guest::get_velocity() const {
  return _velocity;
}

void Guest::set_direction(Direction d) {
  _direction = d;
}

bool Guest::get_is_cart() const {
  return _is_cart;
}

void Guest::set_captured(bool b) {
  _captured = b;
}

void Guest::set_is_dead(bool b) {
  _is_dead = b;
}

bool Guest::get_is_dead() const {
  return _is_dead;
}

bool Guest::give_umbrella() {
  if (!_has_umbrella) {
    _has_umbrella = true;
    return true;
  }

  return false;
}

std::string Guest::get_name() const {
  return std::format("{} {}", _inital, _name);
}
