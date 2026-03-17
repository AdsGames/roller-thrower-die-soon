#include "menu.h"

void menu::init() {
  menu_font = asw::assets::load_font("assets/font/font.ttf", 18);
  splash = asw::assets::load_texture("assets/images/splash.png");
  loading = asw::assets::load_texture("assets/images/loading.png");
}

// Draw images to screen
void menu::draw() {
  asw::draw::sprite(splash, asw::Vec2<float>(0, 0));
}

void menu::update(float dt) {
  if (asw::input::get_key_down(asw::input::Key::Escape)) {
    asw::core::exit = true;
  }

  if (asw::input::keyboard.any_pressed) {
    manager.set_next_scene(ProgramStates::Options);
  }
}
