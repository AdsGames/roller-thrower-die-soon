#include "Guest.h"

#include <array>
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

Guest::Guest(int x, int y) : x(x), y(y) {
  sprite = asw::assets::load_texture("assets/images/walk.png");
  umbrella = asw::assets::load_texture("assets/images/Umbrella.png");

  name = genName();
  inital = genInital();

  for (int i = 0; i < 43; i++) {
    spritesheet[i] = asw::assets::create_texture(17, 36);
    asw::draw::stretch_sprite_blit(sprite, asw::Quad<float>(0, i * 38, 17, 38),
                                   asw::Quad<float>(0, 0, 17, 38));
  }

  sprite = asw::assets::load_texture("assets/images/panic.png");

  for (int i = 0; i < 25; i++) {
    spritesheet_panic[i] = asw::assets::create_texture(17, 36);
    asw::draw::stretch_sprite_blit(sprite, asw::Quad<float>(0, i * 36, 17, 36),
                                   asw::Quad<float>(0, 0, 17, 38));
  }
}

void Guest::update() {
  const float threshold = 1.0F;
  const float decel = 1.2F;

  if (x_velocity > -threshold && x_velocity < threshold) {
    x_velocity = 0;
  }

  if (y_velocity > -threshold && y_velocity < threshold) {
    y_velocity = 0;
  }

  if (y_velocity > 0) {
    y_velocity /= decel;
  }

  if (y_velocity < 0) {
    y_velocity /= decel;
  }

  if (x_velocity > 0) {
    x_velocity /= decel;
  }

  if (x_velocity < 0) {
    x_velocity /= decel;
  }

  if (y_velocity == 0 && x_velocity == 0) {
    if (direction == 0) {
      x += speed;
      y -= 0.5F * speed;
    }

    if (direction == 1) {
      x += speed;
      y += 0.5F * speed;
    }

    if (direction == 2) {
      x -= speed;
      y += 0.5F * speed;
    }

    if (direction == 3) {
      x -= speed;
      y -= 0.5F * speed;
    }
  } else {
    x += x_velocity;
    y += y_velocity;
  }

  frame = (frame + 1) % 42;
  frame_panic = (frame + 1) % 25;
}

void Guest::draw() const {
  if (!captured) {
    asw::draw::sprite(spritesheet[frame], asw::Vec2<float>(x - 8, y - 18));
  } else {
    asw::draw::sprite(spritesheet_panic[frame_panic],
                      asw::Vec2<float>(x - 10, y - 18));
  }

  if (has_umbrella) {
    asw::draw::sprite(umbrella, asw::Vec2<float>(x + 3, y - 20));
  }
}

std::string Guest::getName() const {
  return std::format("{} {}", inital, name);
}
