#include "guest.h"

#include <array>
#include <cmath>
#include <format>

float Guest::speed = 0.0f;

namespace {
std::string genName() {
  const auto nameInt = asw::random::between(0, 49);

  std::array<std::string, 50> names = {
      "Ethel",     "Chung",     "Fe",         "Brooke",    "Nicky",
      "Gail",      "Andrea",    "Sigrid",     "Carmon",    "Marybelle",
      "Racquel",   "Dottie",    "Wilson",     "Myra",      "Jackeline",
      "Vonda",     "Stacey",    "Jacquelynn", "Phebe",     "Madeline",
      "Miguelina", "Loretta",   "Malissa",    "Kandy",     "Nancee",
      "Petronila", "Madelaine", "Shakira",    "Jamika",    "Quentin",
      "Shanell",   "Adrian",    "Clement",    "Gus",       "Hung",
      "Tamie",     "Elidia",    "Jeneva",     "Shantel",   "Sage",
      "Susann",    "Coralie",   "Alphonso",   "Stephanie", "Gena",
      "Barbera",   "Jesusita",  "Donald",     "Danno",     "Allan"};
  return names[nameInt];
}

std::string genInital() {
  const auto initalInt = asw::random::between(0, 25);

  std::array<std::string, 26> initals = {
      "Q.", "W.", "E.", "R.", "T.", "Y.", "U.", "I.", "O.",
      "P.", "A.", "S.", "D.", "F.", "G.", "H.", "J.", "K.",
      "L.", "Z.", "X.", "C.", "V.", "B.", "N.", "M."};

  return initals[initalInt];
}
}  // namespace

Guest::Guest(const asw::Vec2<float>& position) : position(position) {
  sprite = asw::assets::load_texture("assets/images/walk.png");
  umbrella = asw::assets::load_texture("assets/images/Umbrella.png");

  name = genName();
  inital = genInital();

  for (int i = 0; i < 43; i++) {
    spritesheet[i] = asw::assets::create_texture(17, 36);
    asw::display::set_render_target(spritesheet[i]);
    asw::draw::stretch_sprite_blit(sprite, asw::Quad<float>(0, i * 38, 17, 38),
                                   asw::Quad<float>(0, 0, 17, 38));
    asw::display::reset_render_target();
  }

  sprite = asw::assets::load_texture("assets/images/panic.png");

  for (int i = 0; i < 25; i++) {
    spritesheet_panic[i] = asw::assets::create_texture(17, 36);
    asw::display::set_render_target(spritesheet_panic[i]);
    asw::draw::stretch_sprite_blit(sprite, asw::Quad<float>(0, i * 36, 17, 36),
                                   asw::Quad<float>(0, 0, 17, 38));
    asw::display::reset_render_target();
  }
}

void Guest::update(float dt) {
  frame_counter += dt;

  // Walking logic
  if (velocity.x == 0 && velocity.y == 0) {
    if (direction == Direction::East) {
      position.x += PIXELS_PER_S * dt;
      position.y -= 0.5F * PIXELS_PER_S * dt;
    }

    if (direction == Direction::South) {
      position.x += PIXELS_PER_S * dt;
      position.y += 0.5F * PIXELS_PER_S * dt;
    }

    if (direction == Direction::West) {
      position.x -= PIXELS_PER_S * dt;
      position.y += 0.5F * PIXELS_PER_S * dt;
    }

    if (direction == Direction::North) {
      position.x -= PIXELS_PER_S * dt;
      position.y -= 0.5F * PIXELS_PER_S * dt;
    }
  } else {
    // Throwing logic
    if (velocity.x > -MIN_VELOCITY && velocity.x < MIN_VELOCITY) {
      velocity.x = 0;
    } else {
      velocity.x *= std::pow(DECELERATION_FACTOR, dt);
    }

    if (velocity.y > -MIN_VELOCITY && velocity.y < MIN_VELOCITY) {
      velocity.y = 0;
    } else {
      velocity.y *= std::pow(DECELERATION_FACTOR, dt);
    }

    position += velocity;
  }
}

void Guest::draw() const {
  const auto total_frame = static_cast<int>(frame_counter * FRAMES_PER_S);

  if (!captured) {
    const auto frame = total_frame % spritesheet.size();
    asw::draw::sprite(spritesheet[frame], position - asw::Vec2<float>(8, 18));
  } else {
    const auto frame_panic = total_frame % spritesheet_panic.size();
    asw::draw::sprite(spritesheet_panic[frame_panic],
                      position - asw::Vec2<float>(10, 18));
  }

  if (has_umbrella) {
    asw::draw::sprite(umbrella, position + asw::Vec2<float>(3, -20));
  }

  asw::draw::circle(getPosition(), 4, asw::color::red);
}

std::string Guest::getName() const {
  return std::format("{} {}", inital, name);
}
