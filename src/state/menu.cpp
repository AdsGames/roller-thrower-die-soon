#include "menu.h"

void Menu::init() {
  _ui_root = asw::ui::Root();
  auto& splash = _ui_root.root.add_child<asw::ui::Panel>();
  splash.bg_image = asw::assets::load_texture("assets/images/splash.png");
  splash.transform.size = asw::Vec2f(1920, 1080);
}

void Menu::update(float dt) {
  Scene::update(dt);

  if (asw::input::keyboard.any_pressed) {
    manager.set_next_scene(ProgramStates::Options);
  }

  if (asw::input::get_key_down(asw::input::Key::Escape)) {
    asw::core::exit();
    return;
  }
}

void Menu::draw() {
  Scene::draw();
  _ui_root.draw();
}