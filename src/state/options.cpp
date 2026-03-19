#include "options.h"

#include "../level_config_loader.h"

void Options::init() {
  auto font = asw::assets::load_font("assets/font/font.ttf", 36);

  _ui = asw::ui::Root();
  _ui.root.transform.size = asw::Vec2f(1920, 1080);
  _ui.root.bg_image =
      asw::assets::load_texture("assets/images/levelSelecT.png");

  const auto configs = LevelConfigLoader::load_all("assets/levels/levels.json");

  float x = 400.0F;
  for (const auto& cfg : configs) {
    auto& btn = _ui.root.add_child<asw::ui::Button>();
    btn.transform = asw::Quadf(x, 550.0F, 150.0F, 50.0F);
    btn.font = font;
    btn.text = "Level " + std::to_string(cfg.level_number);
    btn.on_click = [this, cfg] {
      Game::level = cfg.level_number;
      manager.set_next_scene(ProgramStates::Game);
    };

    x += 200.0F;
  }
}

void Options::draw() {
  _ui.draw();
}

void Options::update(float dt) {
  if (asw::input::get_key_down(asw::input::Key::Escape)) {
    manager.set_next_scene(ProgramStates::Menu);
  }

  _ui.update();
}
